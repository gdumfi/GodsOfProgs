#include <QCoreApplication>
#include "singletondb.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<SingletonDB::getInstance()->queryToDB("SELECT * FROM demo;");

    return a.exec();
}
