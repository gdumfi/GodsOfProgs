#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("DRIVER = {SQL Server}; SERVER = (127.0.0.1); DATABASE = (sqlite)")
    if (db.open)
    {
        qDebug()<<"opened";
    }
    else
    {
        qDebug()<<"closed";
    }
    
    MyTcpServer server;
    return a.exec();
}
