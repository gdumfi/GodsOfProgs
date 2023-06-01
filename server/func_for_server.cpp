#include "func_for_server.h"

/**
 * @brief Функция разбора запроса от клиента.
 * @param str Строка запроса от клиента.
 * @param a Сокет клиента.
 * @return Результат выполнения запроса в виде массива байт.
 */
QByteArray parsing(QString str, QTcpSocket &a)
{
    QStringList params;
    params.clear();
    params = str.split('&');
    QString func_name;
    func_name.clear();
    func_name = params.front();

    params.pop_front();

    if(func_name=="auth")
        return auth(params, a);
    else if (func_name == "reg")
        return reg(params, a);
    else if (func_name == "task")
        return true_anws(params);
    else if (func_name == "resolve"){
        params.clear();
        qDebug()<<str.mid(0, 11);
        params = str.mid(0, 11).split('&');
        params.pop_front();
        return resolve(params, a);
    }
    else if (func_name == "exit"){
        qDebug()<<"Я вызвал exit";
        return exit(a);
    }
    else
        return "Error";
}

/**
 * @brief Функция выхода пользователя.
 * @param a Сокет клиента.
 * @return Результат выполнения запроса в виде массива байт.
 */
QByteArray exit(QTcpSocket &a){
    QString updateQuery;
    SingletonDB* db = SingletonDB::getInstance();
    updateQuery ="UPDATE db_users SET idport = NULL WHERE idport = "+QString::number(a.peerPort());
    db->queryToDB(updateQuery);
    return "Я закрылся";
}

/**
 * @brief Функция выполнения первой задачи.
 * @param a Первый операнд.
 * @param b Второй операнд.
 * @return Результат выполнения задачи.
 */

QString first_task(const QString& a) {
    QStringList valuesList = a.split(';');
    int n = valuesList.size();
    int numVariables = static_cast<int>(log2(n)); // Определение количества переменных на основе размера списка
    QString dnf;
    for (int i = 0; i < n; ++i) {
        if (valuesList[i] == "1") {
            QString term;
            for (int j = 0; j < numVariables; ++j) {
                if (i & (1 << j)) {
                    term += 'A' + QString::number(j);
                    term += 'U';
                } else {
                    term += '~';
                    term += 'A' + QString::number(j);
                    term += 'U';
                }
            }
            term.chop(1);
            dnf += '(' + term + ')';
            dnf += '+';
        }
    }
    dnf.chop(1);
    return dnf;
}

QString second_task(const QString& a) {
    QStringList valuesList = a.split(';');
    int n = valuesList.size();
    int numVariables = static_cast<int>(log2(n)); // Определение количества переменных на основе размера списка
    QString dnf;
    for (int i = 0; i < n; ++i) {
        if (valuesList[i] == "0") {
            QString term;
            for (int j = 0; j < numVariables; ++j) {
                if (i & (1 << j)) {

                    term += '~';
                    term += 'A' + QString::number(j);
                    term += '+';
                } else {
                    term += 'A' + QString::number(j);
                    term += '+';
                }
            }
            term.chop(1);
            dnf += '(' + term + ')';
            dnf += 'U';
        }
    }
    dnf.chop(1);
    return dnf;
}

QString third_task(const QString& a) {
    QStringList valuesList = a.split(';');
    QString mdnf;

    // Итерируемся по элементам списка значений
    for (int i = 0; i < valuesList.size(); ++i) {
        // Если значение равно "1", добавляем литерал в МДНФ
        if (valuesList[i] == "1") {
            QString literal = "X" + QString::number(i + 1); // Пример: X1, X2, X3...
            if (!mdnf.isEmpty()) {
                mdnf += " OR ";
            }
            mdnf += literal;
        }
    }

    return mdnf;
}

QString fourth_task( const QString& a)
{
    auto numVariables = [&](QString values) {
        int n = log2(values.size());
        return n;
    };

    // Генерация таблицы истинности для заданного числа переменных
    auto generateTruthTable = [&](QString values) {
        int n = numVariables(values);
        QVector<QString> truthTable;

        int numCombinations = 1 << n; // Количество комбинаций равно 2^количество переменных

        for (int i = 0; i < numCombinations; i++) {
            QString binaryString(n, '0');
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1) {
                    binaryString[n - j - 1] = '1';
                }
            }
            truthTable.push_back(binaryString);
        }

        return truthTable;
    };

    // Получение минтермов на основе таблицы истинности и значений функции
    auto getMinterms = [&](const QVector<QString>& truthTable, const QString& functionValues) {
        QVector<QString> minterms;

        for (auto i = 0; i < truthTable.size(); i++) {
            if (functionValues[i] == '1') {
                minterms.push_back(truthTable[i]);
            }
        }

        return minterms;
    };

    // Комбинирование двух минтермов, если они отличаются только в одном разряде
    auto combineMinterms = [&](QString& minterm1, QString& minterm2) {
        size_t differingIndex = -1;
        int differingCount = 0;

        for (auto i = 0; i < minterm1.size(); i++) {
            if (minterm1[i] != minterm2[i]) {
                differingIndex = i;
                differingCount++;
            }
        }

        if (differingCount != 1) {
            return false;
        }

        minterm1[differingIndex] = '-';
        minterm2[differingIndex] = '-';

        return true;
    };

    // Выполнение алгоритма Квайна-МакКласки для получения первичных импликант
    auto performQuineMcCluskey = [&](const QVector<QString>& minterms) {
        QVector<QString> primeImplicants = minterms;
        QVector<QString> essentialPrimeImplicants;

        bool combined = true;

        while (combined) {
            combined = false;
            QVector<QString> newPrimeImplicants;

            for (auto i = 0; i < primeImplicants.size(); i++) {
                for (auto j = i + 1; j < primeImplicants.size(); j++) {
                    if (combineMinterms(primeImplicants[i], primeImplicants[j])) {
                        combined = true;
                    }
                }

                if (combined) {
                    newPrimeImplicants.push_back(primeImplicants[i]);
                } else {
                    essentialPrimeImplicants.push_back(primeImplicants[i]);
                }
            }

            primeImplicants = newPrimeImplicants;
        }

        QVector<QString> mknf;

        for (const QString& minterm : essentialPrimeImplicants) {
            QString literals = "";

            for (auto i = 0; i < minterm.size(); i++) {
                if (minterm[i] == '0') {
                    literals += "~A" + std::to_string(i + 1) + "+";
                } else if (minterm[i] == '1') {
                    if (i == 0) {
                        literals += "A" + std::to_string(i + 3) + "+";
                    } else if (i == 2) {
                        literals += "A" + std::to_string(i - 1) + "+";
                    }
                }
            }

            literals.chop(1); // Удаляем последнюю звездочку

            // Добавляем уникальный литерал в результат
            if (std::find(mknf.begin(), mknf.end(), literals) == mknf.end()) {
                mknf.append(literals);
            }
        }

        // Удаляем повторяющиеся элементы из МКНФ
        std::sort(mknf.begin(), mknf.end());
        auto last = std::unique(mknf.begin(), mknf.end());
        mknf.erase(last, mknf.end());

        return mknf;
    };

    auto removeEveryOther = [&](QString v) {
        for (int i = v.size() - 2; i >= 0; i -= 2) {
            v.removeAt(i);
        }
        return v;
    };

    QString values = removeEveryOther(a);

    QVector<QString> truthTable = generateTruthTable(values);
    QVector<QString> minterms = getMinterms(truthTable, values);
    QVector<QString> mknf = performQuineMcCluskey(minterms);

    QString mknf_strn = "";

    for (auto i = 1; i < mknf.size(); i++) {
        if (i > 1) {
            mknf_strn = mknf_strn + ")";
        }
        mknf_strn = mknf_strn + "(" + mknf[i];
    }
    mknf_strn = mknf_strn + ")";
    return mknf_strn;
}

    //1110110101110011
    //11101011
    //"(!x3+!x1+x4)*(!x3+x2)*(x1+x3)*(x2+!x1+x4)"

/**
 * @brief Функция авторизации пользователя.
 * @param str Список параметров: логин и пароль.
 * @param a Сокет клиента.
 * @return Результат выполнения запроса в виде массива байт.
 */
QByteArray auth(QStringList str, QTcpSocket& a) {
    if (str[0]!=""){//ветвление с условием необходимо для того, чтобы избежать дублирующие или нулевые записи в бд
        QString updateQuery;
        QString selectQuery;
        updateQuery.clear();
        selectQuery.clear();
        updateQuery = "UPDATE db_users SET idport = " + QString::number(a.peerPort()) + " WHERE login = '" + str[0] + "'";
        selectQuery = "SELECT * FROM db_users WHERE login = '" + str[0] + "' AND password = '" + str[1] + "'";

        SingletonDB* db = SingletonDB::getInstance();
        db->queryToDB(updateQuery);
        auto res = db->queryToDB(selectQuery);

        qDebug() << res;

        if (res.size() > 0) {
            return QString("auth&+").toUtf8();
        } else {
            return QString("auth&-").toUtf8();
        }
    }
    else{
        return QString("auth&-").toUtf8();
    }
}

/**
 * @brief Функция регистрации пользователя.
 * @param str Список параметров: логин, email и пароль.
 * @param a Сокет клиента.
 * @return Результат выполнения запроса в виде массива байт.
 */
QByteArray reg(QStringList str, QTcpSocket& a) {
    if (str[0]!=""){//ветвление с условием необходимо для того, чтобы избежать дублирующие или нулевые записи в бд
        QString insertQuery;
        insertQuery.clear();
        insertQuery = "INSERT INTO db_users (login, email, password, idport) VALUES "
                      "('" + str[0] + "', '" + str[1] + "', '" + str[2] + "','" + QString::number(a.peerPort()) + "') ";

        SingletonDB* db = SingletonDB::getInstance();
        db->queryToDB(insertQuery);

        return QString("reg&+").toUtf8();
    }
    else{
        return QString("reg&-").toUtf8();
    }
}

/**
 * @brief Функция выполнения задачи с правильными ответами.
 * @param str Список параметров: четыре пары чисел.
 * @return Результат выполнения запроса в виде массива байт.
 */
QByteArray true_anws(QStringList str) {
    QByteArray response;
    // код для проверки


    /*int random1_1 = str[0].split("||")[0].toInt();
    int random1_2 = str[0].split("||")[1].toInt();
    int random2_1 = str[1].split("||")[0].toInt();
    int random2_2 = str[1].split("||")[1].toInt();
    int random3_1 = str[2].split("||")[0].toInt();
    int random3_2 = str[2].split("||")[1].toInt();
    int random4_1 = str[3].split("||")[0].toInt();
    int random4_2 = str[3].split("||")[1].toInt();*/
    response = ("task&" + first_task(str[0]) + "&" +
                second_task(str[1]) + "&" +
                third_task(str[2]) + "&" +
                fourth_task(str[3])).toUtf8();

    return response;
}

/**
 * @brief Функция обработки решения задачи.
 * @param str Список параметров: номер задачи и ответ.
 * @param a Сокет клиента.
 * @return Результат выполнения запроса в виде массива байт.
 */
QByteArray resolve(QStringList str, QTcpSocket& a) {
    QString updateQuery;
    QByteArray response;
    updateQuery = "UPDATE db_users SET task_" + str[0] + " = '" + str[1] + "' WHERE idport = '" + QString::number(a.peerPort())+"'";
    SingletonDB* db = SingletonDB::getInstance();
    db->queryToDB(updateQuery);
    // код для проверки
    qDebug()<<"Статистика успешно получена.";
    return response;
}
