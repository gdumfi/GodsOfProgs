#ifndef FUNC_FOR_SERVER_H
#define FUNC_FOR_SERVER_H
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QStringList>
#include <QDebug>
#include "singletondb.h"
QByteArray parsing(QString str,QTcpSocket &a );

QByteArray auth(QStringList str, QTcpSocket &a);
QByteArray reg(QStringList str, QTcpSocket &a);
QByteArray true_anws(QStringList str);
QByteArray resolve(QStringList str, QTcpSocket &a);
QByteArray exit(QTcpSocket &a);

////////////////////////////////////////////////


#endif // FUNC_FOR_SERVER_H
