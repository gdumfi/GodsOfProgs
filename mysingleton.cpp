#ifndef MYSINGLETON_H
#define MYSINGLETON_H
#include <QSqlDataBase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

//Улучшенная реализация
class MySingleton {
public:
    static MySingleton& instance() {
        static MySingleton singleton;
        return singleton;
    }

    // Другие методы и члены класса

private:
    MySingleton() { /* ... */ }
    MySingleton(const MySingleton&) = delete;
    void operator=(const MySingleton&) = delete;
    ~MySingleton() { /* ... */ }

    // Другие приватные члены класса
};


//SingletonDestroyer Singleton::destroyer;
//Singleton * SingletonDestroyer::p_instance;
#endif // MYSINGLETON_H
