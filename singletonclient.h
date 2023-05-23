#ifndef SingletonClientT_H
#define SingletonClientT_H


#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QObject>
#include <QDebug>

class SingletonClient;

class SingletonClient_destroyer {
private:
    SingletonClient* p_instance;

public:
    ~SingletonClient_destroyer() { delete p_instance; }
    void initialize(SingletonClient* p) { p_instance = p; }
};

class SingletonClient : public QObject {
    Q_OBJECT
private:
    static SingletonClient* p_instance;
    static SingletonClient_destroyer destroyer;
    QTcpSocket* socket;

protected:
    SingletonClient(QObject* parent = nullptr);
    SingletonClient(const SingletonClient&) = delete;
    SingletonClient& operator=(SingletonClient&) = delete;
    ~SingletonClient() {
        socket->close();
    }
    friend class SingletonClient_destroyer;

public:
    static SingletonClient* getInstance() {
        if (!p_instance) {
            p_instance = new SingletonClient();
            destroyer.initialize(p_instance);
        }
        return p_instance;
    }

public slots:
    void slot_send_to_server(QString str);
    QString slot_ready_read();
    void slot_connected();
};

#endif // SingletonClientT_H
