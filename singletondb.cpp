#include "singletondb.h"

SingletonDBDestroyer::~SingletonDBDestroyer()
{
    delete p_instance;
}

void SingletonDBDestroyer::initialize(SingletonDB * p)
{
    p_instance = p;
}

SingletonDB::SingletonDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("../ConsoleAppSingletondb/sqlite.db");
}

bool SingletonDB::openDB()
{
    if (!db.open())
    {
        qDebug() << "Failed to connect to database";
        return false;
    }
    return true;
}

QString SingletonDB::queryToDB(QString query)
{
    if (!openDB()) {
            qDebug() << "Failed to open database";
            return "";
        }

        QSqlQuery sqlQuery(db);
        if (!sqlQuery.exec(query)) {
            qDebug() << "Failed to execute query: " << sqlQuery.lastError().text();
            return "";
        }
        QString result = "";
        while (sqlQuery.next()) {
            result = sqlQuery.value(0).toString();
        }
        return result;
}


SingletonDB * SingletonDB::p_instance;
SingletonDBDestroyer SingletonDB::destroyer;
