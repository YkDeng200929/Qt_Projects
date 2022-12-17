#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <QMediaPlayer>
#include <QMap>

class MusicPlayer : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit MusicPlayer(QObject *parent = nullptr);
    QString getLyrics(QString lyricsData);

signals:
    void signal_getLine(int line);

public slots:
    void slot_getLine(qint64 position);

private:
    QMap<qint64, int> lyricsInfo; // 存储歌词时间与对应行的容器
};

#endif // MUSICPLAYER_HPP
