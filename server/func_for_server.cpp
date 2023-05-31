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



QString fourth_task(const QString& a)
{
    QStringList values = a.split(';'); // Разделяем строку на значения
    int numVariables = static_cast<int>(log2(values.size())); // Определяем количество переменных
    int numMinterms = values.size(); // Определяем количество мономов

    QStringList minterms;

    // Проходимся по всем значениям и добавляем их в список мономов
    for (int i = 0; i < numMinterms; i++) {
        int value = values[i].toInt();
        if (value == 1) {
            QString minterm = "";
            QString binary = QString::number(i, 2);
            while (binary.length() < numVariables) {
                binary = "0" + binary;
            }
            for (int j = 0; j < numVariables; j++) {
                if (binary[j] == '0') {
                    minterm += QString("x%1'").arg(j + 1); // Добавляем переменную со знаком отрицания
                } else {
                    minterm += QString("x%1").arg(j + 1); // Добавляем переменную
                }
            }
            minterms.append(minterm);
        }
    }

    QString mknf = minterms.join(" + "); // Объединяем мономы с помощью логической операции ИЛИ

    return mknf;
}


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
