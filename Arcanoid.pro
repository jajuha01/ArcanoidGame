#-------------------------------------------------
#
# Project created by QtCreator 2014-10-07T08:45:12
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arcanoid
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    apptimer.cpp \
    appcontrol.cpp \
    player.cpp \
    gameball.cpp \
    obstacle.cpp \
    gamesound.cpp

HEADERS  += mainwindow.h \
    apptimer.h \
    appcontrol.h \
    player.h \
    gameball.h \
    obstacle.h \
    gamesound.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resource.qrc
