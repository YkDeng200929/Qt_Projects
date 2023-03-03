#ifndef WEATHER_HPP
#define WEATHER_HPP

#include <QMainWindow>
#include "HttpHandle.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init_tableWidget();

private slots:
    void slot_showWeatherList(QStringList weatherList);
    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    HttpHandle *httpHandle;
};

#endif // WEATHER_HPP
