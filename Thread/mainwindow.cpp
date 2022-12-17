#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    thread(new MyThread(this)),
    task(new Task)
{
    ui->setupUi(this);

    // thread->start();   // 开启线程

    connect(this, &MainWindow::signalA, task, &Task::slotA);
    connect(this, &MainWindow::signalB, task, &Task::slotB);

    QThread *thread = new QThread(this); // 创建一个父线程
    thread->start();    // 开启线程

}

MainWindow::~MainWindow()
{
    thread->KILL();
    QThread::sleep(1);

    if (task != nullptr)
    {
        delete task;
    }

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit signalA(); // 让子线程开始工作
    qDebug() << "子线程A任务发布";
}

void MainWindow::on_pushButton_2_clicked()
{
    emit signalB();
    qDebug() << "子线程B任务发布";
}
