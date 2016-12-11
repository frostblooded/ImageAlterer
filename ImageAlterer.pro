#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T16:17:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageAlterer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageblurrer.cpp

HEADERS  += mainwindow.h \
    imageblurrer.h

FORMS    += mainwindow.ui
