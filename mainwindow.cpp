#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic/world.h"
#include "scene.h"
#include "point.h"
#include "iostream"
#include "camera.h"

#include <QKeyEvent>
#include <cmath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QGraphicsScene* sceneUi = new QGraphicsScene(this);
    Camera cam0(0, 0, 0, -135, 0, 0);
    Camera cam1(0, 0, 0, -90, 0, 0);
    Camera cam2(0, 0, 0, 180, 0, 0);
    Camera cam3(0, 0, 0, 130, 180, 0);
    Scene *scene = new Scene(sceneUi, 640, 640, 640);
    scene->addCamera(cam0);
    scene->addCamera(cam1);
    scene->addCamera(cam2);
    scene->addCamera(cam3);
    scene->setCurCam(0);

    controller = new Controller(scene, new World(640, 640, 640));
    ui->setupUi(this);
    ui->graphicsView->centerOn(0, 0);
    ui->graphicsView->setScene(sceneUi);
    controller->generateWorld();
    on_curTime_timeChanged(ui->curTime->time());

    timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
        switch(event->key())
        {
        case Qt::Key_0:
            controller->setCurCam(0);
            break;
        case Qt::Key_1:
            controller->setCurCam(1);
            break;
        case Qt::Key_2:
            controller->setCurCam(2);
            break;
        case Qt::Key_3:
            controller->setCurCam(3);
            break;
        case Qt::Key_W:
            controller->plusAngleX();
            break;
        case Qt::Key_S:
            controller->minusAngleX();
            break;
        case Qt::Key_A:
            controller->plusAngleY();
            break;
        case Qt::Key_D:
            controller->minusAngleY();
            break;
        }
}

void MainWindow::on_curTime_timeChanged(const QTime &time)
{
    double hours = time.hour();
    double min = time.minute();
    double angle = hours * 15 + min * 0.15 - 90;

    controller->setCurSunAngle(angle);
}

void MainWindow::updateTime()
{
    if (ui->checkBoxChangeTime->isChecked())
    {
        auto curTime = ui->curTime->time();
        int h = curTime.hour();
        int m = step + curTime.minute();
        if (curTime.minute() + step >= 60)
        {
            h += 1;
            m = m - 60;
        }
        if (h == 24)
            h = 0;

        curTime.setHMS(h, m, curTime.second());
        ui->curTime->setTime(curTime);
    }
    timer.start();
}

void MainWindow::on_checkBoxChangeTime_clicked()
{
    if (ui->checkBoxChangeTime->isChecked())
        ui->curTime->setEnabled(0);
    else
        ui->curTime->setEnabled(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    controller->plusAngleX();
}

void MainWindow::on_pushButton_6_clicked()
{
    controller->minusAngleX();
}

void MainWindow::on_pushButton_4_clicked()
{
    controller->plusAngleY();
}

void MainWindow::on_pushButton_5_clicked()
{
    controller->minusAngleY();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    controller->setIsShadow(arg1);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    step = ui->spinBox->value();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    int num = ui->spinBox_2->value();
    controller->setNumThreads(num);
}
