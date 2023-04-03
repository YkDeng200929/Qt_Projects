#ifndef WEATHER_WIDGET_HPP
#define WEATHER_WIDGET_HPP

#include <QDialog>

enum {
    MON = 0,
    TUES,
    WEN,
    THURS,
    FRI,
    SAT,
    SUN,
};

const QString week[] = {
    "星期一",
    "星期二",
    "星期三",
    "星期四",
    "星期五",
    "星期六",
    "星期日"
};

namespace Ui {
class Weather_Widget;
}

class Weather_Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Weather_Widget(QWidget *parent = 0);
    ~Weather_Widget();

private:
    Ui::Weather_Widget *ui;
};

#endif // WEATHER_WIDGET_HPP
