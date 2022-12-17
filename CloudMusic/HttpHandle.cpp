#include "HttpHandle.hpp"
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>

HttpHandle::HttpHandle(QObject *parent) : QObject(parent),
    manager(new QNetworkAccessManager(this))
{

}

QByteArray HttpHandle::postSearch(const QString &body)
{
    // 3、设计请求内容
    // QNetworkRequest request(QUrl("https://l-by.cn/yinyue/api.php"));
    QNetworkRequest request(QUrl(QString("https://l-%1.cn/yinyue/api.php").arg("by")));
    // 4、设计请求头信息
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("application/x-www-form-urlencoded; charset=UTF-8"));

    // 5、manager对象发送请求数据, reply对象接收返回信息
    QNetworkReply *reply = manager->post(request, body.toUtf8());

    // 6、开启一个事件循环， 当用户输入时退出当前正在进行的传输
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    // 7、读取所有的返回内容并返回
    return reply->readAll();
}

QByteArray HttpHandle::getPicture(const QString &picUrl)
{
    QNetworkRequest request(picUrl);
    QNetworkReply *reply = manager->get(request);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    return reply->readAll();
}

void HttpHandle::searchMusicList(const QString &searchData)
{
    // 1、处理用户搜索信息后打包成附属体
    QString body = QString("types=search&count=30&source=netease&pages=1&name=%1").arg(searchData);

    // 2、将body给传输搜索信息函数处理并接受返回的信息
    QByteArray musicData = postSearch(body);

    // 8、将读取到的json数据存到document中
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(musicData, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << "解析音乐列表Json数据失败！错误原因: " << error.errorString();
        return ;
    }

    // 9、把json数据文件转化为json类型的数组
    QJsonArray musicArray = document.array();
    // 10、依次解析json数据
    for (int i = 0; i < musicArray.size(); i++)
    {
        QJsonObject musicObject = musicArray[i].toObject();
        QString id = QString::number(musicObject["id"].toInt());
        QString name = musicObject["name"].toString();
        QString album = musicObject["album"].toString();
        QString picid = musicObject["pic_id"].toString();
        QString artist;
        QJsonArray artistArr = musicObject["artist"].toArray();
        for (int j = 0; j < artistArr.size(); j++)
        {
            QString allArtist = artistArr[j].toString();
            artist += allArtist + ',';
        }
        artist.chop(1); // 删除最后一个逗号

        QStringList musicInfo;
        musicInfo << id << picid << name << artist << album;
        emit signal_musicList(musicInfo);
    }
}

QString HttpHandle::searchMusicUrl(const QString &id)
{
    QString body = QString("types=url&id=%1&source=netease").arg(id);

    QByteArray musicData = postSearch(body);

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(musicData, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << "获取音乐URL失败！错误原因: " << error.errorString();
        return QString(); // <==> return QString {} <==> return {}表示返回空
    }
    QJsonObject musicObj = document.object();
    QString musicUrl = musicObj["url"].toString();

    return musicUrl;
}

QString HttpHandle::searchMusicLyric(const QString &id)
{
    QString body = QString("types=lyric&id=%1&source=netease").arg(id);

    QByteArray musicData = postSearch(body);

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(musicData, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << "获取歌词信息失败！错误原因: " << error.errorString();
        return {};
    }
    QJsonObject lyricObj = document.object();
    QString musicLyrics = lyricObj["lyric"].toString();
    return musicLyrics;
}

QString HttpHandle::searchMusicPicurl(const QString &picid)
{
    QString body = QString("types=pic&id=%1&source=netease").arg(picid);

    QByteArray musicData = postSearch(body);

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(musicData, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << "获取专辑信息失败错误原因: " << error.errorString();
        return {};
    }
    QJsonObject albumObj = document.object();
    QString albumUrl = albumObj["url"].toString();
    return albumUrl;
}
