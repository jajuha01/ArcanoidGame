#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <apptimer.h>
#include <appcontrol.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public AppTimerIf
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *e);
    /* implementation for Timeout event */
    virtual void TimerEvent(void* timer);
private slots:
    void on_ReStartGame_clicked();

    void on_actionReStart_triggered();

    void on_actionPause_triggered();

    void on_actionResume_triggered();

    void on_actionEAsy_triggered();

    void on_actionMedium_triggered();

    void on_actionHard_triggered();

private:
    Ui::MainWindow *ui;
    AppTimer* appTimer;
    AppControl* appControl;
    int viewWidth,viewHeight;
};

#endif // MAINWINDOW_H
