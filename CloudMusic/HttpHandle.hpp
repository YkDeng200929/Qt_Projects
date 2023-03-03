#ifndef HTTPHANDLE_HPP
#define HTTPHANDLE_HPP

#include <QObject>
#include <QNetworkAccessManager>

class HttpHandle : public QObject
{
    Q_OBJECT
public:
    explicit HttpHandle(QObject *parent = nullptr);

    /***************************************************************
      *  @brief     发送搜索请求
      *  @param     body    待搜索音乐名
      *  @note      公有函数
      *  @Sample usage:     函数的使用方法
     **************************************************************/
    QByteArray postSearch(const QString &body);

    // 获取专辑封面
    QByteArray getPicture(const QString &picUrl);

    // 通过搜索栏的搜索关键字搜索音乐列表
    void searchMusicList(const QString &searchData);

    // 搜索音乐url
    QString searchMusicUrl(const QString &id);

    // 搜索歌词
    QString searchMusicLyric(const QString &id);

    // 搜索专辑封面
    QString searchMusicPicurl(const QString &picid);

signals:
    void signal_musicList(QStringList musicList);

public slots:

private:
    QNetworkAccessManager *manager;
};

#endif // HTTPHANDLE_HPP
