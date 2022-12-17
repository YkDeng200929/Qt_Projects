#include "Weather.hpp"
#include "ui_Weather.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    httpHandle(new HttpHandle(this))
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/prefix1/Icon/bitbug_favicon.ico"));

    init_tableWidget();
    connect(httpHandle, &HttpHandle::signal_weatherList, this, &MainWindow::slot_showWeatherList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_tableWidget()
{
    // ui->tableWidget_musicList->setStyleSheet("selection-background-color:red; selection-color: white;"); //设置tableWidget QSS样式表，背景为红色，字体为白色
    // ui->tableWidget_weatherInfo->hideColumn(0);	//隐藏第一列
    // ui->tableWidget_musicList->hideColumn(1);	//隐藏第二列
    ui->tableWidget_weatherInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget_weatherInfo->setSelectionBehavior(QAbstractItemView::SelectRows);//一次选一行
    ui->tableWidget_weatherInfo->setFocusPolicy(Qt::NoFocus);	//去掉虚线框
    ui->tableWidget_weatherInfo->setSortingEnabled(false);	//增加表头排序功能

    ui->tableWidget_weatherInfo->horizontalHeader()->setFixedHeight(30);    //固定列头高度为30像素
    ui->tableWidget_weatherInfo->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue; border-radius: 0px; border: 3px solid rgb(240, 194, 197);}");   //设置tabWidget列头QSS样式表，背景为天蓝
    ui->tableWidget_weatherInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表头拉伸
    ui->tableWidget_weatherInfo->horizontalHeader()->setHighlightSections(false);       //选中列头不在高亮

    ui->tableWidget_weatherInfo->verticalHeader()->hide();//隐藏行头
    ui->tableWidget_weatherInfo->verticalHeader()->setHighlightSections(false);         //选中行头不在高亮
    ui->tableWidget_weatherInfo->setAlternatingRowColors(true);   // 设置间隔行不同颜色
    ui->tableWidget_weatherInfo->setPalette(QPalette(QColor(135, 206, 235))); // 设置间隔行颜色
}

void MainWindow::slot_showWeatherList(QStringList weatherList)
{
    int column = ui->tableWidget_weatherInfo->columnCount(); //获取当前有多少列
    int line = ui->tableWidget_weatherInfo->rowCount();
    ui->tableWidget_weatherInfo->insertRow(line);
    for (int i = 0; i < weatherList.size(); i++)
    {
        ui->tableWidget_weatherInfo->setItem(line, i, new QTableWidgetItem(weatherList[i]));
    }
    for (int j = 0; j < line + 1; j++)
    {
        for (int k = 0; k < column; k++)
        {
            ui->tableWidget_weatherInfo->item(j,k)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
    ui->tableWidget_weatherInfo->clearContents();
    ui->tableWidget_weatherInfo->setRowCount(0);
    QString searchData = ui->lineEdit->text();
    httpHandle->searchCityId(searchData);
}
