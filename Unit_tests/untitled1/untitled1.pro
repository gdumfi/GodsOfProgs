QT += testlib network sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_qwe.cpp \
    ../Server/func_for_server.cpp \
    ../Server/mytcpserver.cpp \
    ../Server/singletondb.cpp

HEADERS += \
    ../Server/func_for_server.h \
    ../Server/mytcpserver.h \
    ../Server/singletondb.h
