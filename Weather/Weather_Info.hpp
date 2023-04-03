#ifndef WEATHER_INFO_HPP
#define WEATHER_INFO_HPP

#include <QWidget>

namespace Ui {
class Weather_Info;
}

class Weather_Info : public QWidget
{
    Q_OBJECT

public:
    explicit Weather_Info(QWidget *parent = 0);
    ~Weather_Info();

private:
    Ui::Weather_Info *ui;
};

#endif // WEATHER_INFO_HPP
