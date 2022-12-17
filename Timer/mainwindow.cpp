#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this))
{
    ui->setupUi(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::outPut);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *tEvent)
{
    qDebug() << tEvent->timerId() << "到点";
    killTimer(tEvent->timerId());
}

void MainWindow::outPut()
{
    // qDebug() << "定时器到时";
    if (ui->label->isHidden())
    {// 设置按钮闪烁
        ui->label->show();
    }
    else
    {
        ui->label->hide();
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (timer->isActive())
    {
        return ;
    }
    // timer->start(2000);
    timer->start(200);
}

void MainWindow::on_pushButton_2_clicked()
{
    timer->stop();
}

void MainWindow::on_pushButton_3_clicked()
{
    int id = startTimer(200);
    qDebug() << id << "开始计时";
}
