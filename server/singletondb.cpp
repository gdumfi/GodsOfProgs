#include "singletondb.h"

/**
 * @class SingletonDBDestroyer
 * @brief Вспомогательный класс для уничтожения SingletonDB при завершении программы
 */

/**
 * @brief Деструктор класса SingletonDBDestroyer
 */
SingletonDBDestroyer::~SingletonDBDestroyer()
{
    delete p_instance;
}

/**
 * @brief Инициализация указателя на SingletonDB
 * @param p Указатель на SingletonDB
 */
void SingletonDBDestroyer::initialize(SingletonDB* p)
{
    p_instance = p;
}

/**
 * @class SingletonDB
 * @brief Класс для работы с базой данных SQLite в рамках паттерна Singleton
 */

/**
 * @brief Конструктор класса SingletonDB
 */
SingletonDB::SingletonDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Univercity/QT_server/GodsOfProgs1/GodsOfProgs/Server/sqlite_users_db.db");
}

/**
 * @brief Открытие соединения с базой данных
 * @return true, если соединение установлено успешно, иначе false
 */
bool SingletonDB::openDB()
{
    if (!db.open())
    {
        qDebug() << "Failed to connect to the database";
        return false;
    }
    return true;
}

/**
 * @brief Выполнение SQL-запроса к базе данных
 * @param query Строка с SQL-запросом
 * @return Результат выполнения запроса или пустая строка в случае ошибки
 */
QString SingletonDB::queryToDB(QString query)
{
    if (!openDB())
    {
        qDebug() << "Failed to open the database";
        return "";
    }

    QSqlQuery sqlQuery(db);
    if (!sqlQuery.exec(query))
    {
        qDebug() << "Failed to execute the query: " << sqlQuery.lastError().text();
        return "";
    }

    QString result = "";
    while (sqlQuery.next())
    {
        result = sqlQuery.value(0).toString();
    }
    return result;
}

SingletonDB* SingletonDB::p_instance;
SingletonDBDestroyer SingletonDB::destroyer;
