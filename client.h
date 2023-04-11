#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QList>


class SingletonClient;

class SingletonClientDestroyer
{
    private:
        SingletonClient * p_instance;
    public:
        ~SingletonClientDestroyer();
};


class SingletonClient
{
    private:
        static SingletonClient * p_instance;
        static SingletonClientDestroyer destroyer;
        QTcpSocket *socket;
    protected:
        SingletonClient();
        SingletonClient(const SingletonClient& )= delete;
        SingletonClient& operator = (SingletonClient &) = delete;
        ~SingletonClient(){db.close();};
        friend class SingletonClientDestroyer;
    public:
        static SingletonClient* getInstance(){//poluchit' ssylku na ob'ekt vozvraschaet ukazatel' na ob'ekt
            if (!p_instance)
            {
                p_instance = new SingletonClient();
                destroyer.initialize(p_instance);
            }
            return p_instance;
        }
       bool connectToServer(); // ecli socket ne pustoy
       void sendToServer(QString); // otpravit' soobschenie
       slot readyRead(); // void slot

};


#endif // SingletonClient_H
