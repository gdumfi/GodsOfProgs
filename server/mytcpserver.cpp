#include "mytcpserver.h"

/**
 * @brief Деструктор класса MyTcpServer.
 * Закрывает сервер и устанавливает статус сервера в 0.
 */
MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status = 0;
}

/**
 * @brief Конструктор класса MyTcpServer.
 * Создает объект QTcpServer и устанавливает его для прослушивания входящих подключений.
 * Если сервер успешно запущен, устанавливает статус сервера в 1, иначе выводит сообщение об ошибке.
 * @param parent Родительский объект.
 */
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        server_status = 1;
        qDebug() << "server is started";
    }
}

/**
 * @brief Слот для обработки нового входящего соединения.
 * Если сервер в активном состоянии, создает новый объект QTcpSocket для подключившегося клиента.
 * Устанавливает необходимые соединения сигналов и добавляет сокет в список mTcpSocket.
 */
void MyTcpServer::slotNewConnection()
{
    if (server_status == 1) {
        QTcpSocket* curr_mTcpSocket = mTcpServer->nextPendingConnection();
        connect(curr_mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
        connect(curr_mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
        mTcpSocket.push_back(curr_mTcpSocket);
    }
}

/**
 * @brief Слот для чтения данных из сокета.
 * Читает данные из сокета curr_mTcpSocket и преобразует их в строку.
 * Вызывает функцию parsing() для обработки полученной строки.
 * Отправляет ответ обратно клиенту через curr_mTcpSocket.
 */
void MyTcpServer::slotServerRead()
{
    QByteArray array;
    QTcpSocket* curr_mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    qDebug() << "То, что в сокете до отправки в массив: " << curr_mTcpSocket->peek(curr_mTcpSocket->bytesAvailable());

    if (curr_mTcpSocket->bytesAvailable() > 0) {
        array.clear();
        array = curr_mTcpSocket->readAll();
        qDebug() << "Массив после считывания из сокета: " << array;
        QString task = QString::fromUtf8(array);
        qDebug() << task;
        QByteArray response = parsing(task, *curr_mTcpSocket);
        qDebug() << response;
        curr_mTcpSocket->write(response);
        qDebug() << "Правильно: " << curr_mTcpSocket->peek(curr_mTcpSocket->bytesAvailable());
    }
}

/**
 * @brief Слот для обработки отключения клиента.
 * Закрывает сокет curr_mTcpSocket и освобождает память.
 */
void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket* curr_mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    curr_mTcpSocket->close();
    curr_mTcpSocket->deleteLater();
}
