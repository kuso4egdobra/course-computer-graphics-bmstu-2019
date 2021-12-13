#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller/controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Controller *controller;
    QTimer timer;
    int step = 1;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);


private slots:
    void on_curTime_timeChanged(const QTime &time);
    void updateTime();

    void on_checkBoxChangeTime_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
