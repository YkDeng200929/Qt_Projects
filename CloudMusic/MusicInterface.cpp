#include "MusicInterface.hpp"
#include "ui_MusicInterface.h"
#include <QDebug>
#include <QTime>
#include <QTextBlock>
#include <QImage>
#include <QMessageBox>

MusicInterface::MusicInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MusicInterface),
    httpHandle(new HttpHandle(this)),
    musicPlayer(new MusicPlayer(this)),
    shufflePlay(false),
    aboutInterface(new AboutInterface)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/new/prefix1/Image/music.ico"));
    setWindowTitle("CloudMusicPlayer");
    // setFixedSize(size());

    QTime time = QTime::currentTime();
    qsrand(time.msecsSinceStartOfDay());

    connect(httpHandle, &HttpHandle::signal_musicList, this, &MusicInterface::slot_showMusicList);
    connect(ui->horizontalSlider_volumn, &QSlider::sliderMoved, musicPlayer, &MusicPlayer::setVolume);
    connect(musicPlayer, &MusicPlayer::stateChanged, this, &MusicInterface::slot_flushMusicPlayButton);
    connect(musicPlayer, &MusicPlayer::mediaStatusChanged, this, &MusicInterface::slot_shufflePlay);
    connect(musicPlayer, &MusicPlayer::positionChanged, this, &MusicInterface::slot_flushStartTimeProgress);
    connect(musicPlayer, &MusicPlayer::durationChanged, this, &MusicInterface::slot_flushEndTimeProgress);
    connect(musicPlayer, &MusicPlayer::signal_getLine, this, &MusicInterface::slot_pointLine);

    initTableWidget();
    initLyricsWindow();
}

MusicInterface::~MusicInterface()
{
    if (aboutInterface != nullptr)
    {
        delete aboutInterface;
    }
    delete ui;
}

void MusicInterface::initLyricsWindow()
{
    QPalette palette = ui->textEdit_lyrics->palette();			//获取textEdit的调色板
    palette.setColor(QPalette::Highlight, QColor(Qt::transparent));	//将选中区域背景改为透明
    palette.setColor(QPalette::HighlightedText, QColor(255, 219, 37));	//将选中区域的文字改为红色
    ui->textEdit_lyrics->setPalette(palette);				//将调色板设置到textEdit
    ui->textEdit_lyrics->setReadOnly(true);				//设置为只读
    ui->textEdit_lyrics->document()->setDefaultTextOption(QTextOption(Qt::AlignHCenter));	//文字居中显示
}

void MusicInterface::initTableWidget()
{
    // ui->tableWidget_musicList->setStyleSheet("selection-background-color:red; selection-color: white;"); //设置tableWidget QSS样式表，背景为红色，字体为白色
    ui->tableWidget_musicList->hideColumn(0);	//隐藏第一列
    ui->tableWidget_musicList->hideColumn(1);	//隐藏第二列
    ui->tableWidget_musicList->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget_musicList->setSelectionBehavior(QAbstractItemView::SelectRows);//一次选一行
    ui->tableWidget_musicList->setFocusPolicy(Qt::NoFocus);	//去掉虚线框
    ui->tableWidget_musicList->setSortingEnabled(false);	//增加表头排序功能
    ui->tableWidget_musicList->horizontalHeader()->setFixedHeight(30);    //固定列头高度为30像素
    ui->tableWidget_musicList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue; border-radius: 0px; border: 3px solid rgb(240, 194, 197);}");   //设置tabWidget列头QSS样式表，背景为天蓝
    ui->tableWidget_musicList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表头拉伸
    ui->tableWidget_musicList->horizontalHeader()->setHighlightSections(false);       //选中列头不在高亮
    ui->tableWidget_musicList->verticalHeader()->hide();//隐藏行头
    ui->tableWidget_musicList->verticalHeader()->setHighlightSections(false);         //选中行头不在高亮
    ui->tableWidget_musicList->setAlternatingRowColors(true);   // 设置间隔行不同颜色
    ui->tableWidget_musicList->setPalette(QPalette(QColor(135, 206, 235))); // 设置间隔行颜色
}

void MusicInterface::shufflePlayIconStyle()
{
    if (shufflePlay)
    {
        ui->pushButton_shuffle->setStyleSheet("QPushButton {"
                                              "border-image: url(:/new/prefix1/Image/sufflex_hover.png); "
                                              "}"
                                              "QPushButton:pressed {"
                                              "border-image: url(:/new/prefix1/Image/sufflex.png);"
                                              "}"
                                              "QPushButton:hover {"
                                              "background-color: rgb(95, 177, 221)"
                                              "}"
                                              );
    }
    else
    {
        ui->pushButton_shuffle->setStyleSheet("QPushButton {"
                                              "border-image: url(:/new/prefix1/Image/queue_hover.png);"
                                              "}"
                                              "QPushButton:pressed {"
                                              "border-image: url(:/new/prefix1/Image/queue.png);"
                                              "}"
                                              "QPushButton:hover {"
                                              "background-color: rgb(95, 177, 221)"
                                              "}"
                                              );
    }
}

void MusicInterface::slot_pointLine(int linePoint)
{
    int line = linePoint;
    //获取当前光标
    QTextCursor tc2 = ui->textEdit_lyrics->textCursor();
    //在textEdit中找到指定行位置
    int pos2 = ui->textEdit_lyrics->document()->findBlockByLineNumber(line).position();
    //将光标设置到指定位置
    tc2.setPosition(pos2, QTextCursor::MoveAnchor);
    //光标设置成选中一整行，并且保持此状态
    tc2.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    //将设置好的光标属性放到textEdit中
    ui->textEdit_lyrics->setTextCursor(tc2);
}

void MusicInterface::slot_flushStartTimeProgress(qint64 ms)
{
    ui->horizontalSlider_playProgress->setValue(ms);
    QTime time = QTime::fromMSecsSinceStartOfDay(ms);
    ui->label_startTime->setText(time.toString("mm:ss"));
}

void MusicInterface::slot_flushEndTimeProgress(qint64 ms)
{
    // 设置水平滑条的秒数
    ui->horizontalSlider_playProgress->setMaximum(ms);
    // 将毫秒数转换成秒数
    QTime time = QTime::fromMSecsSinceStartOfDay(ms);
    // 将秒数格式转换为mm:ss格式
    ui->label_endTime->setText(time.toString("mm:ss"));
}

void MusicInterface::slot_shufflePlay(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        if (shufflePlay)
        {
            int line = ui->tableWidget_musicList->rowCount();	//获取当前共有多少行
            int num = qrand() % line;
            if (num == line - 1)
            {
                num = 0;
            }
            on_tableWidget_musicList_cellDoubleClicked(num, 0);

            ui->tableWidget_musicList->selectRow(num);		//选中第line行
        }
        else
        {
            on_pushButton_nextMusic_clicked();
        }
    }
    else if (status == QMediaPlayer::InvalidMedia)
    {
        QMessageBox msgBox;
        msgBox.setText("Invalid Music");
        msgBox.setInformativeText("Please charge VIP");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, "是");
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.setIconPixmap(QPixmap(":/new/prefix1/Image/music.ico"));
        msgBox.setWindowIcon(QIcon(":/new/prefix1/Image/music.ico"));
        msgBox.setWindowTitle("Invalid Music");
        int ret=msgBox.exec();
        if(ret==QMessageBox::Yes)
        {
            msgBox.setText("Thanks");
            msgBox.setInformativeText("Thank you for your top-up");
            msgBox.setStandardButtons(QMessageBox::Close);
            msgBox.exec();
        }
    }
}

void MusicInterface::slot_flushMusicPlayButton(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState)
    {
        // 所有的ui空间都属于MusicInterface的对象, 所以这里可以直接调用graphicview
        ui->graphicsView->startNeedleAnimation();
        ui->graphicsView->startAnimation();
        ui->pushButton_musicPlay->setStyleSheet("QPushButton {"
                                                "border-image: url(:/new/prefix1/Image/pause_hover2.png); "
                                                "}"
                                                "QPushButton:pressed {"
                                                "border-image: url(:/new/prefix1/Image/pause2.png);"
                                                "}"
                                                "QPushButton:hover {"
                                                "background-color: rgb(95, 177, 221)"
                                                "}"
                                                );
    }
    else
    {
        ui->graphicsView->pauseNeedleAnimation();
        ui->graphicsView->pauseAnimation();
        ui->pushButton_musicPlay->setStyleSheet("QPushButton {"
                                                "border-image: url(:/new/prefix1/Image/play_hover.png);"
                                                "}"
                                                "QPushButton:pressed {"
                                                "border-image: url(:/new/prefix1/Image/play.png);"
                                                "}"
                                                "QPushButton:hover {"
                                                "background-color: rgb(95, 177, 221)"
                                                "}"
                                                );
    }
}

void MusicInterface::slot_showMusicList(QStringList musicList)
{
    int line = ui->tableWidget_musicList->rowCount();
    ui->tableWidget_musicList->insertRow(line);
    for (int i = 0; i < musicList.size(); i++)
    {
        ui->tableWidget_musicList->setItem(line, i, new QTableWidgetItem(musicList[i]));
    }
}

void MusicInterface::on_lineEdit_searchBar_returnPressed()
{
    ui->tableWidget_musicList->clearContents();
    ui->tableWidget_musicList->setRowCount(0);
    QString searchData = ui->lineEdit_searchBar->text();
    httpHandle->searchMusicList(searchData);
}

void MusicInterface::on_tableWidget_musicList_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column)
    QString musicId = ui->tableWidget_musicList->item(row,0)->text();  //获取第row行，第column列的数据
    QString musicUrl = httpHandle->searchMusicUrl(musicId);

    QString lyrics = httpHandle->searchMusicLyric(musicId);
    QString newLyrics = musicPlayer->getLyrics(lyrics);

    QString picId = ui->tableWidget_musicList->item(row, 1)->text();
    QString picUrl = httpHandle->searchMusicPicurl(picId);
    picUrl.replace("300y300", "1200y1200");
    QByteArray picInfo = httpHandle->getPicture(picUrl);
    QImage img = QImage::fromData(picInfo);
    ui->graphicsView->setMusicImage(img);
    // img.save("1.png");

    ui->textEdit_lyrics->setText(newLyrics);
    musicPlayer->setMedia(QUrl(musicUrl));
    musicPlayer->play();
}

void MusicInterface::on_pushButton_lastSong_clicked()
{
    int line = ui->tableWidget_musicList->rowCount();	//获取当前共有多少行
    int row = ui->tableWidget_musicList->currentRow();	//获取当前选中行
    if (row == -1)
    {
        return ;
    }
    if (row == 0)
    {
        row = line;
    }
    on_tableWidget_musicList_cellDoubleClicked(--row, 0);
    ui->tableWidget_musicList->selectRow(row);		//选中第line行
}

void MusicInterface::on_pushButton_nextMusic_clicked()
{
    int line = ui->tableWidget_musicList->rowCount();	//获取当前共有多少行
    int row = ui->tableWidget_musicList->currentRow();	//获取当前选中行
    if (row == -1)
    {
        return ;
    }
    if (row == line - 1)
    {
        row = 0;
    }
    on_tableWidget_musicList_cellDoubleClicked(++row, 0);
    ui->tableWidget_musicList->selectRow(row);		//选中第line行

}

void MusicInterface::on_pushButton_musicPlay_clicked()
{
    if (musicPlayer->state() == QMediaPlayer::PlayingState)
    {
        musicPlayer->pause();
    }
    else if (musicPlayer->state() == QMediaPlayer::PausedState)
    {
        musicPlayer->play();
    }
    else
    {
        int row = ui->tableWidget_musicList->currentRow();	//获取当前选中行
        if (row == -1)
        {
            return ;
        }
        on_tableWidget_musicList_cellDoubleClicked(row, 0);
    }
}

void MusicInterface::on_pushButton_shuffle_clicked()
{
    if (shufflePlay)
    {
        shufflePlay = false;
        shufflePlayIconStyle();
    }
    else
    {
        shufflePlay = true;
        shufflePlayIconStyle();
    }
}

void MusicInterface::on_horizontalSlider_playProgress_sliderMoved(int position)
{
    musicPlayer->setPosition(position);
}

void MusicInterface::on_action_triggered()
{
    aboutInterface->show();
}
