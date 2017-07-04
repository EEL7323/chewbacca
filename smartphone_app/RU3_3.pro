#-------------------------------------------------
#
# Project created by QtCreator 2017-06-28T12:41:46
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RU3_3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    file.cpp \
    nextdialog.cpp \
    transactionsdialog.cpp \
    mytcpdialog.cpp \
    mytcpsocket.cpp \
    comingdialog.cpp \
    creditdialog.cpp \
    enterdialog.cpp

HEADERS  += mainwindow.h \
    file.h \
    nextdialog.h \
    transactionsdialog.h \
    mytcpdialog.h \
    mytcpsocket.h \
    comingdialog.h \
    creditdialog.h \
    enterdialog.h

FORMS    += mainwindow.ui \
    nextdialog.ui \
    transactionsdialog.ui \
    mytcpdialog.ui \
    comingdialog.ui \
    creditdialog.ui \
    enterdialog.ui

CONFIG += mobility
MOBILITY = 

