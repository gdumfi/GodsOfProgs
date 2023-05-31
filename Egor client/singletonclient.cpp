#include "mainwindow.h"
#include "singletonclient.h"

/**
 * @brief Конструктор класса SingletonClient.
 * @param parent Указатель на родительский объект.
 */
SingletonClient::SingletonClient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 33333);
    connect(socket, SIGNAL(connected()), SLOT(slot_connected()));
    // connect(socket, SIGNAL(readyRead()), SLOT(slot_ready_read()));
}

/**
 * @brief Отправляет строку на сервер через сокет.
 * @param str Строка для отправки на сервер.
 */
void SingletonClient::slot_send_to_server(QString str) {
    qDebug() << "запрос дошел до синглетона передачи: " << "|| " << str;
    qDebug() << "Сокет синглетона" << socket->peek(socket->bytesAvailable());
    socket->write(str.toUtf8());
}

/**
 * @brief Считывает ответ от сервера.
 * @return Ответ от сервера в виде строки.
 */
QString SingletonClient::slot_ready_read() {
    QByteArray array;
    QString task;
    task.clear();
    // while (m_pTcpSocket->bytesAvailable() > 0)
    // {
    //     msg += m_pTcpSocket->readAll();
    // }
    if (socket->waitForConnected(500)) {
        socket->waitForReadyRead(500);
        array = socket->readAll();
        task = QString::fromUtf8(array.constData(), array.size());
    }
    // qDebug()<<msg<<"Проверка 1";

    return task;
}

/**
 * @brief Слот, вызываемый при успешном соединении с сервером.
 */
void SingletonClient::slot_connected() {
    qDebug() << "Соединение прошло успешно";
}

SingletonClient *SingletonClient::p_instance;
SingletonClient_destroyer SingletonClient::destroyer;
