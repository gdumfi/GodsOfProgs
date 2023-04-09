#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::~MyTcpServer()
{
    //mTcpSocket->close();
    mTcpServer->close();
    server_status=0;
}
//штука с сокетами
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
//штука с бд
 /*   db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    if (db.open())
    {
        qDebug("open");

    }
    else
    {
        qDebug("close");
    }

    query = new QSqlQuery(db);
    query -> exec("CREATE TABLE AUTH (FIO TEXT, EMAIL TEXT, PASSWORD TEXT)");
*/
}

void MyTcpServer::slotNewConnection(){
    //коннекты
    if(server_status==1){
        QTcpSocket* curr_mTcpSocket;
        curr_mTcpSocket = mTcpServer->nextPendingConnection();
        curr_mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        connect(curr_mTcpSocket, &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(curr_mTcpSocket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
        mTcpSocket.push_back(curr_mTcpSocket);
    }
}

void MyTcpServer::slotServerRead(){
    QByteArray array;
    QString str;
    QTcpSocket* curr_mTcpSocket = (QTcpSocket*)sender();
    while(curr_mTcpSocket->bytesAvailable()>0)
    {
       array.append(curr_mTcpSocket->readAll());
       str+=array;
    }
    array="";
    array.append(str.toUtf8());
//нэробит почему то
    QString task = array.left(str.size() - 2);
    qDebug()<<task;
    QByteArray a;
    a = parsing(task);
    qDebug()<<a;
    curr_mTcpSocket->write(a);
}
//диконнеты
void MyTcpServer::slotClientDisconnected(){

    QTcpSocket* curr_mTcpSocket = (QTcpSocket*)sender();
    curr_mTcpSocket->close();
    curr_mTcpSocket->deleteLater();
}

void connectiontodb()
{
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
}

