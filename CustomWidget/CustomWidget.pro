#-------------------------------------------------
#
# Project created by QtCreator 2016-08-01T21:25:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomWidget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    custom_cpu_widget.cpp \
    custom_slider_widget.cpp

HEADERS  += widget.h \
    custom_cpu_widget.h \
    custom_slider_widget.h

RESOURCES += \
    resources.qrc
