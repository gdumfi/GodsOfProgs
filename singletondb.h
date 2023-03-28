#ifndef SINGLETONDB_H
#define SINGLETONDB_H
#include <QSqlDataBase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
//#include <QtCore>
class SingletonDB;

class SingletonDBDestroyer
{
    private:
        SingletonDB * p_instance;
    public:
        ~SingletonDBDestroyer();
        void initialize(SingletonDB * p);
};


class SingletonDB
{
    private:
        static SingletonDB * p_instance;
        static SingletonDBDestroyer destroyer;
        QSqlDatabase db;
    protected:
        SingletonDB();
        SingletonDB(const SingletonDB& );
        SingletonDB& operator = (SingletonDB &);
        ~SingletonDB(){db.close();};
        friend class SingletonDBDestroyer;
    public:
        static SingletonDB* getInstance(){
            if (!p_instance)
            {
                p_instance = new SingletonDB();
                destroyer.initialize(p_instance);
            }
            return p_instance;
        }

        QString queryToDB(QString query);

        bool openDB();
};


#endif // SINGLETONDB_H
