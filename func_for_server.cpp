#include "func_for_server.h"

QByteArray parsing(QString str)
{
    QStringList params = str.split('&');
    QString func_name = params.front();
    params.pop_front();

    if(func_name=="auth")
        return auth(params);
    else if (func_name == "reg")
        return reg(params);
    else if (func_name == "checktask")
        return checktask(params);
    else if (func_name == "stat")
        return stat(params);
    else
        return "Error";
}

QByteArray auth(QStringList str) {

    auto res =SingletonDB::getInstance()->queryToDB("select * from db_users where login = " + str[1]);
    qDebug()<<res;

    if(res.size()>0) return "auth&+";
    else
    {
        return "auth&-";
    }
}

QByteArray reg(QStringList str) {
    QByteArray response;
    // код для проверки
    response.append("Регистрация прошла успешно.");
    return response;
}

QByteArray checktask(QStringList str) {
    QByteArray response;
    // код для проверки
    response.append("Задачи проверены.");
    return response;
}

QByteArray stat(QStringList str) {
    QByteArray response;
    // код для проверки
    response.append("Статистика успешно получена.");
    return response;
}
