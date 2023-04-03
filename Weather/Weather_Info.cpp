#include "Weather_Info.hpp"
#include "ui_Weather_Info.h"

Weather_Info::Weather_Info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Weather_Info)
{
    ui->setupUi(this);
}

Weather_Info::~Weather_Info()
{
    delete ui;
}
