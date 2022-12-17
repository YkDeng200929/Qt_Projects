#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "A.hpp"
#include "B.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    aa(new A(this)),     // 这样就不用释放aa了
    bb(new B(this))
{
    ui->setupUi(this);

    // 传统写法
    // connect(this, SIGNAL(sig_A(int)), this, SLOT(slot_A(int)));

    // 新式写法
    // connect(this, &MainWindow::sig_A, this, &MainWindow::slot_A);

    // 解决函数重载问题
    // connect(this, &MainWindow::sig_A, this, static_cast<void (MainWindow::*)(int)>(&MainWindow::slot_A));

    // λ表达式信号与槽 C++11特性
    /*
    connect(this, &MainWindow::sig_A, [](int i){
        qDebug() << "λ表达式信号与槽 " << i;
    });
    */

    // 对象与对象之间通信
    // connect(this, &MainWindow::sig_B, aa, &A::slot_B);
    connect(aa, &A::sig_ASignal, bb, &B::slot_BSlot);
    connect(bb, &B::sig_BSignal, aa, &A::slot_ASlot);

    emit sig_A(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_A(int i)
{
    qDebug() << i;
}

// 窗口事件
void MainWindow::on_pushButton_clicked()
{
    qDebug()  << "Oh~";
    emit sig_B("hello~");
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "A click";
    emit aa->sig_ASignal("A点击发送信号");
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "B_click";
    emit bb->sig_BSignal("B点击发送信号");
}
