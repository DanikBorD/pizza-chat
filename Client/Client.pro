#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T16:12:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chatclient.cpp \
    loginform.cpp

HEADERS  += mainwindow.h \
    chatclient.h \
    loginform.h

FORMS    += mainwindow.ui \
    loginform.ui
