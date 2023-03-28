#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<SingletonClient::getInstance()->/*метод*/;
    return a.exec();
}
