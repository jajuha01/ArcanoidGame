/*
** Copyright (c) 2014 Jarmo Hautakoski
**
** ArcanoidUbuntu project
**  */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
