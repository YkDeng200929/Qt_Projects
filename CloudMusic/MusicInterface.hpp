#ifndef MUSICINTERFACE_HPP
#define MUSICINTERFACE_HPP

#include <QMainWindow>
#include "HttpHandle.hpp"
#include "MusicPlayer.hpp"
#include "AboutInterface.hpp"

namespace Ui {
class MusicInterface;
}

class MusicInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit MusicInterface(QWidget *parent = 0);
    ~MusicInterface();

private:
    void initLyricsWindow();
    void initTableWidget();
    void shufflePlayIconStyle();

private slots:
    void slot_pointLine(int linePoint);

    // 刷新开始时间秒数
    void slot_flushStartTimeProgress(qint64 ms);

    void slot_flushEndTimeProgress(qint64 ms);

    /***************************************************************
      *  @brief     随机播放
      *  @param     status (音乐播放状态)
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void slot_shufflePlay(QMediaPlayer::MediaStatus status);

    /***************************************************************
      *  @brief     改变播放按钮样式
      *  @param     status (音乐播放状态)
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void slot_flushMusicPlayButton(QMediaPlayer::State state);

    /***************************************************************
      *  @brief     在tabWidget中显示音乐列表
      *  @param     musicList (音乐列表)
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void slot_showMusicList(QStringList musicList);

    /***************************************************************
      *  @brief     回车时捕获搜索栏中的内容
      *  @param     musicList (音乐列表)
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void on_lineEdit_searchBar_returnPressed();

    /***************************************************************
      *  @brief     双击表格中音乐名时播放音乐并显示歌词信息
      *  @param     row, colum
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void on_tableWidget_musicList_cellDoubleClicked(int row, int column);

    /***************************************************************
      *  @brief     点击上一首按钮时播放上一首歌曲
      *  @param     void
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void on_pushButton_lastSong_clicked();

    /***************************************************************
      *  @brief     点击下一首按钮时播放下一首歌曲
      *  @param     void
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void on_pushButton_nextMusic_clicked();

    /***************************************************************
      *  @brief     双击播放按钮时播放歌曲
      *  @param     void
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void on_pushButton_musicPlay_clicked();

    /***************************************************************
      *  @brief     点击随机播放按钮时随机播放
      *  @param     void
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void on_pushButton_shuffle_clicked();

    /***************************************************************
      *  @brief     移动播放状态条时跳转到相应的播放时间
      *  @param     position 播放位置
      *  @note      槽函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    void on_horizontalSlider_playProgress_sliderMoved(int position);

    void on_action_triggered();

private:
    Ui::MusicInterface *ui;
    HttpHandle *httpHandle;         // 该对象负责处理Http过程
    MusicPlayer *musicPlayer;
    bool shufflePlay;
    AboutInterface *aboutInterface;

};

#endif // MUSICINTERFACE_HPP
