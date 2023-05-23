#include "mytcpserver.h"

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status=0;
}
//штука с сокетами
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    //коннекты
    if(server_status==1){
        QTcpSocket* curr_mTcpSocket = mTcpServer->nextPendingConnection();
        //curr_mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        connect(curr_mTcpSocket, &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(curr_mTcpSocket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
        mTcpSocket.push_back(curr_mTcpSocket);
    }
}

void MyTcpServer::slotServerRead(){

    /*QByteArray array;
    array.clear();
    QTcpSocket* curr_mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    qDebug()<<"То, что в сокете до отправки в массив "<< curr_mTcpSocket->readAll();
    while (curr_mTcpSocket->bytesAvailable() > 0) {
        array.append(curr_mTcpSocket->readAll());
    }
    qDebug()<<"Массивпосле считывания из сокета "<< array;
    QString task;
    task.clear();
    task = QString::fromUtf8(array);
    qDebug() << task;
    QByteArray a = parsing(task, *curr_mTcpSocket);
    qDebug() << a;
    curr_mTcpSocket->write(a);*/
    QByteArray array;
    QTcpSocket* curr_mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    qDebug()<<"То, что в сокете до отправки в массив "<< curr_mTcpSocket->peek(curr_mTcpSocket->bytesAvailable());
    if (curr_mTcpSocket->bytesAvailable() > 0) {
        array.clear();
        array = curr_mTcpSocket->readAll();
        qDebug()<<"Массивпосле считывания из сокета "<< array;
        QString task;
        task.clear();
        task = QString::fromUtf8(array);
        qDebug() << task;
        QByteArray a;
        a.clear();
        a = parsing(task, *curr_mTcpSocket);
        qDebug() << a;
        curr_mTcpSocket->write(a);
        qDebug()<<"Правильно:  "<<curr_mTcpSocket->peek(curr_mTcpSocket->bytesAvailable());
    }
}
//диконнеты
void MyTcpServer::slotClientDisconnected(){

    QTcpSocket* curr_mTcpSocket = (QTcpSocket*)sender();
    curr_mTcpSocket->close();
    curr_mTcpSocket->deleteLater();
}
