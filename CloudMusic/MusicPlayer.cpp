#include "MusicPlayer.hpp"
#include <QTime>
#include <QDebug>

MusicPlayer::MusicPlayer(QObject *parent) : QMediaPlayer(parent)
{
    setVolume(30);
    setNotifyInterval(200);
    connect(this, &MusicPlayer::positionChanged, this, &MusicPlayer::slot_getLine);
}

QString MusicPlayer::getLyrics(QString lyricsData)
{
    QString newLyrics;
    QStringList lyricsList = lyricsData.split('\n');
    lyricsInfo.clear();
    int line = 0;
    for (int i = 0; i < lyricsList.size(); i++)
    {
        QStringList lineLyrics = lyricsList[i].split(']');
        if (lineLyrics.size() != 2)
        {
            continue;
        }
        newLyrics = newLyrics + lineLyrics[1].trimmed() + "\r\n";
        QString lyricsTime = lineLyrics[0].remove('[');
        if (lyricsTime.size() == 8)
        {
            lyricsTime += '0';
        }
        QTime qint_lyricsTime = QTime::fromString(lyricsTime, "mm:ss.zzz");
        lyricsInfo.insert(qint_lyricsTime.msecsSinceStartOfDay(), line++);
    }
    return newLyrics;
}

void MusicPlayer::slot_getLine(qint64 position)
{
    if (lyricsInfo.isEmpty())
    {
        return ;
    }

    int endLine = (--(lyricsInfo.end())).value();

    QMap<qint64, int>::iterator lyricsLiterator = lyricsInfo.upperBound(position);
    // if (lyricsLiterator.value() != 0)
    if (lyricsLiterator != lyricsInfo.begin())
    {
        --lyricsLiterator;
    }
    if (lyricsLiterator.value()+6 <= endLine)
    {
        signal_getLine(lyricsLiterator.value()+6);
    }
    signal_getLine(lyricsLiterator.value());
}
