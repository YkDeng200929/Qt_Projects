#include "Weather_Widget.hpp"
#include "ui_Weather_Widget.h"

Weather_Widget::Weather_Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Weather_Widget)
{
    ui->setupUi(this);
}

Weather_Widget::~Weather_Widget()
{
    delete ui;
}
