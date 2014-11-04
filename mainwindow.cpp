/*
** Copyright (c) 2014 Jarmo Hautakoski
**
** ArcanoidUbuntu project
**  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apptimer.h"

#define DEFAULT_GAME_ARENA_WIDTH 800
#define DEFAULT_GAME_ARENA_HEIGHT 600

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    appControl = new AppControl(ui->graphicsView);
    appControl->InitializeGame(DEFAULT_GAME_ARENA_WIDTH,DEFAULT_GAME_ARENA_HEIGHT);
    appTimer = new AppTimer((AppTimerIf*)this);
    appTimer->SetTimeout(20);

}

MainWindow::~MainWindow()
{
    delete appControl;
    delete appTimer;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (appControl)
        appControl->KeyEvent((Qt::Key)(e->key()));
}

void MainWindow::TimerEvent(void* timer)
{
    /* Take needed timemout actions */
    appControl->Timeout((AppTimer*)timer);
    /* TODO Proper window resize signal hooks + calculation */
    viewWidth = ui->graphicsView->viewport()->width()-10;
    viewHeight = ui->graphicsView->viewport()->height()-10;
}

void MainWindow::on_ReStartGame_clicked()
{
    delete appControl;
    appControl = new AppControl(ui->graphicsView);
    appControl->InitializeGame(viewWidth,viewHeight);

}

void MainWindow::on_actionReStart_triggered()
{
    delete appControl;
    appControl = new AppControl(ui->graphicsView);
    appControl->InitializeGame(viewWidth,viewHeight);
}

void MainWindow::on_actionPause_triggered()
{
    /* Stop timer */
    appTimer->Stop();
}

void MainWindow::on_actionResume_triggered()
{
    /* Stop timer */
    appTimer->Continue();
}

void MainWindow::on_actionEAsy_triggered()
{
    appControl->SetGameLevel(easy);
    appControl->ReInitializeGame();
}

void MainWindow::on_actionMedium_triggered()
{
    appControl->SetGameLevel(medium);
    appControl->ReInitializeGame();
}

void MainWindow::on_actionHard_triggered()
{
    appControl->SetGameLevel(hard);
    appControl->ReInitializeGame();
}
