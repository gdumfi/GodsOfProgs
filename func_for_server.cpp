#include "func_for_server.h"

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
QByteArray exit(QTcpSocket &a){
    QString updateQuery;
    SingletonDB* db = SingletonDB::getInstance();
    updateQuery ="UPDATE db_users SET idport = NULL WHERE idport = "+QString::number(a.peerPort());
    db->queryToDB(updateQuery);
    return "Я закрылся";
}

int first_task(int a, int b){
    int answ1 = a + b;
    return answ1;
}

int second_task(int a, int b){
    int answ2 = a + b;
    return answ2;
}

int third_task(int a, int b){
    int answ3 = a + b;
    return answ3;
}

int fourth_task(int a, int b){
    int answ4 = a + b;
    return answ4;
}


QByteArray auth(QStringList str, QTcpSocket& a) {
    if (str[0]!=""){//ветвление с условием необходимо для того, чтобы избежать дублирующие или нулевые записи в бд
        QString updateQuery;

        QString selectQuery ;

        updateQuery.clear();
        selectQuery.clear();
        updateQuery = "UPDATE db_users SET idport = " + QString::number(a.peerPort()) + " WHERE login = '" + str[0] + "'";//по какой-то причине не срабатывает запрос
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

QByteArray reg(QStringList str, QTcpSocket& a) {
    if (str[0]!=""){//ветвление с условием необходимо для того, чтобы избежать дублирующие или нулевые записи в бд
    QString insertQuery;
    insertQuery.clear();
    insertQuery = "INSERT INTO db_users (login, email, password, idport) VALUES "
                          "('" + str[0] + "', '" + str[1] + "', '" + str[2] + "','" + QString::number(a.peerPort()) + "') ";
    //QString insertQuery = "INSERT INTO db_users (idport) VALUES (" + QString::number(a.peerPort()) + ")";
    //QString selectQuery = "SELECT * FROM db_users WHERE login = '" + str[0] + "' AND password = '" + str[1] + "'";

    SingletonDB* db = SingletonDB::getInstance();
    db->queryToDB(insertQuery);
    //auto res = db->queryToDB(selectQuery);

    return QString("reg&+").toUtf8();}
    else{
    return QString("reg&-").toUtf8();
    }
}

QByteArray true_anws(QStringList str) {
    QByteArray response;
    // код для проверки
    int random1_1 = str[0].split("||")[0].toInt();
    int random1_2 = str[0].split("||")[1].toInt();
    int random2_1 = str[1].split("||")[0].toInt();
    int random2_2 = str[1].split("||")[1].toInt();
    int random3_1 = str[2].split("||")[0].toInt();
    int random3_2 = str[2].split("||")[1].toInt();
    int random4_1 = str[3].split("||")[0].toInt();
    int random4_2 = str[3].split("||")[1].toInt();
    response = ("task&" + QString::number(first_task(random1_1, random1_2)) + "&" +
                       QString::number(second_task(random2_1, random2_2)) + "&" +
                       QString::number(third_task(random3_1, random3_2)) + "&" +
                QString::number(fourth_task(random4_1, random4_2))).toUtf8();

    return response;
}

QByteArray resolve(QStringList str, QTcpSocket& a) {
    QString updateQuery;
    QByteArray response;
    updateQuery = "UPDATE db_users SET task_" + str[0] + " = '" + str[1] + "' WHERE idport = '" + QString::number(a.peerPort())+"'";// + "' AND task_" + str[0] + " != '+'";
    SingletonDB* db = SingletonDB::getInstance();
    db->queryToDB(updateQuery);
    // код для проверки
    qDebug()<<"Статистика успешно получена.";
    return response;
}
