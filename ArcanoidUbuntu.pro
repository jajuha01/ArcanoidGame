#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T10:44:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArcanoidUbuntu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    appcontrol.cpp \
    apptimer.cpp \
    gameball.cpp \
    obstacle.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    appcontrol.h \
    apptimer.h \
    gameball.h \
    obstacle.h \
    player.h

FORMS    += mainwindow.ui
