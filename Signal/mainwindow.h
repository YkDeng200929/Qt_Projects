#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// 记得引用头文件
#include "A.hpp"
#include "B.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:        // 信号
    void sig_A(int i);
    void sig_B(QString qstr);

public slots:   // 槽
    void slot_A(int i);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    A *aa;  // 对象间通信，创建两个对象
    B *bb;
};

#endif // MAINWINDOW_H
