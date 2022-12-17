#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signal_CycClick14(QString)), this, SLOT(on_pushButton_14_clicked()));
    connect(this, SIGNAL(signal_CycClick15(QString)), this, SLOT(on_pushButton_15_clicked()));
    connect(this, SIGNAL(signal_CycClick16(QString)), this, SLOT(on_pushButton_16_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_15_clicked()
{   // 第一页按钮
    int totalPage = ui->stackedWidget->count();
    int current = ui->stackedWidget->currentIndex();
    qDebug()  << totalPage << " " << current << " " << current % totalPage;
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_16_clicked()
{   // 第二页按钮
    int totalPage = ui->stackedWidget->count();
    int current = ui->stackedWidget->currentIndex();
    qDebug()  << totalPage << " " << current << " " << current % totalPage;
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_14_clicked()
{   // 第三页按钮
    int totalPage = ui->stackedWidget->count();
    int current = ui->stackedWidget->currentIndex();
    qDebug()  << totalPage << " " << current << " " << current % totalPage;
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_12_clicked()
{   // 循环翻页按钮
    int current = ui->stackedWidget->currentIndex();
    int totalPage = ui->stackedWidget->count();
    switch (current % totalPage - 1) {
    case 0:
        emit signal_CycClick15("click");
        break;
    case 1:
        emit signal_CycClick16("click");
        break;
    default:
        emit signal_CycClick14("click");
        break;
    }
}
