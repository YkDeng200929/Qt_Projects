#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(sig_page1()), this, SLOT(on_pushButton_clicked()));
    connect(this, SIGNAL(sig_page2()), this, SLOT(on_pushButton_3_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // 第二页按钮
    qDebug() << "Page 2";
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    // 第一页按钮
    qDebug() << "Page 1";
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    qDebug() << index;
    switch(index)
    {
        case 0:
            emit sig_page2();
            break;
        case 1:
            emit sig_page1();
            qDebug() << "ok";
            break;
    }
}
