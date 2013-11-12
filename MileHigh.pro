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
    milehigh.cpp \
    objects/plane.cpp \
    objects/obstacle.cpp \
    objects/runway.cpp \
    mainwindow.cpp \
    objects/waypoint.cpp

HEADERS  += \
    milehigh.h \
    objects/plane.h \
    objects/obstacle.h \
    objects/runway.h \
    mainwindow.h \
    objects/waypoint.h

FORMS    += \
    mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
