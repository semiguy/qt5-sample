#-------------------------------------------------
#
# Project created by QtCreator 2016-08-08T16:23:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += network

TARGET = blockingfortuneclient
TEMPLATE = app


SOURCES += main.cpp\
        blockingclient.cpp \
    fortunethread.cpp

HEADERS  += blockingclient.h \
    fortunethread.h
