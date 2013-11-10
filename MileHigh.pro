#-------------------------------------------------
#
# Project created by QtCreator 2013-11-10T14:26:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MileHigh
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    milehigh.cpp

HEADERS  += mainwindow.h \
    milehigh.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
