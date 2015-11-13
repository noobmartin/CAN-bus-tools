#-------------------------------------------------
#
# Project created by QtCreator 2014-03-08T19:35:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_POSIX_IPC

DEPENDPATH += ../../libraries/data_distribution
INCLUDEPATH += ../../libraries/data_distribution

TARGET = dashboard
TEMPLATE = app

LIBS += -lrt

SOURCES += main.cpp\
        mainwindow.cpp \
    boxmeter.cpp \
    testwidget.cpp \
    sharedmemory.cpp \
    ../../libraries/data_distribution/distribution_areas.c

HEADERS  += mainwindow.h \
    boxmeter.h \
    testwidget.h \
    sharedmemory.h

RESOURCES +=
