#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T14:30:40
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = desktop_app
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    requestapi.cpp

HEADERS  += mainwindow.h \
    requestapi.h

FORMS    += mainwindow.ui
