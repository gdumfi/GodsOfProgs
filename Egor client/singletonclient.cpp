#include "mainwindow.h"
#include "singletonclient.h"


SingletonClient::SingletonClient(QObject * parent):QObject(parent){
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 33333);
    connect(socket, SIGNAL(connected()), SLOT(slot_connected()));
    //connect(socket, SIGNAL(readyRead()),SLOT(slot_ready_read()));
}

void SingletonClient::slot_send_to_server(QString str){
    qDebug() << "запрос дошел до синглетона передачи: " << "|| "<< str;
    qDebug() << "Сокет синглетона" <<   socket->peek(socket->bytesAvailable());
    socket->write(str.toUtf8());
}

/*QString SingletonClient::slot_ready_read() {
    qDebug() << "запрос дошел до синглетона приема";
    qDebug() << "В сокет лежит это: " <<   socket->peek(socket->bytesAvailable());
    QByteArray array;
    array.clear();
    //QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    qDebug() << "В сокет лежит это: " <<   socket->peek(socket->bytesAvailable());
    while (socket->bytesAvailable() > 0) {
        array.append(socket->readAll());
    }
    QString task;
    task.clear();
    task = QString::fromUtf8(array.constData(), array.size());
    return task;
}*/

QString SingletonClient::slot_ready_read() {
    QByteArray array;
    QString task;
    task.clear();
    //while(m_pTcpSocket->bytesAvailable()>0)
    //{
    //    msg += m_pTcpSocket->readAll();
    //}
    if (socket->waitForConnected(500)){
        socket->waitForReadyRead(500);
        array = socket->readAll();
        task = QString::fromUtf8(array.constData(), array.size());
    }
    //qDebug()<<msg<<"Проверка 1";

    return task;
}

void SingletonClient::slot_connected(){
    qDebug()<<"Соеднение прошло успешно";
}


SingletonClient * SingletonClient::p_instance;
SingletonClient_destroyer SingletonClient::destroyer;
