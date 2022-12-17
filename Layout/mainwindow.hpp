#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void signal_CycClick14(QString str);
    void signal_CycClick15(QString str);
    void signal_CycClick16(QString str);

private slots:

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
