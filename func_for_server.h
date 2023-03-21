#ifndef FUNC_FOR_SERVER_H
#define FUNC_FOR_SERVER_H
#include <QByteArray>
#include <QString>
#include <QList>
#include <QStringList>
QByteArray parsing(QString str);

QByteArray auth(QStringList str);
QByteArray reg(QStringList str);
QByteArray checktask(QStringList str);
QByteArray stat(QStringList str);


#endif // FUNC_FOR_SERVER_H
