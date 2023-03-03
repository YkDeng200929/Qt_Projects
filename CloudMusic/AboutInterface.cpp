#include "AboutInterface.hpp"
#include "ui_AboutInterface.h"

AboutInterface::AboutInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutInterface)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/new/prefix1/Image/music.ico"));
    setWindowTitle("关于");
    setFixedSize(size());
}

AboutInterface::~AboutInterface()
{
    delete ui;
}
