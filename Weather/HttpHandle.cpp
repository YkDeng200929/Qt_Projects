#include "HttpHandle.hpp"
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>

QString g_api = "9d1f7a5a2db8467dbbd828b176315fe5";
HttpHandle::HttpHandle(QObject *parent) : QObject(parent),
    manager(new QNetworkAccessManager(this))
{
}

QByteArray HttpHandle::postSearch(const QString &city)
{
    QNetworkRequest request(QUrl(QString("https://geoapi.qweather.com/v2/city/lookup?location=%1&key=%2").arg(city).arg(g_api)));
    QNetworkReply *reply = manager->get(request);

    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    return reply->readAll();
}

QByteArray HttpHandle::postCityForWeather(const QString &cityId)
{
    QNetworkRequest request(QUrl(QString("https://devapi.qweather.com/v7/weather/3d?location=%1&key=%2").arg(cityId).arg(g_api)));
    QNetworkReply *reply = manager->get(request);


    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    return reply->readAll();
}

void HttpHandle::searchCityWeather(const QString &cityId, const QString &cityName, const QString &admain)
{
    QByteArray weatherInfo = postCityForWeather(cityId);

    QByteArray weatherJson = postCityForWeather(cityId);
    QJsonParseError error;
    QJsonDocument documentWeather = QJsonDocument::fromJson(weatherJson, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << "解析天气失败！错误原因: " << error.errorString();
        return ;
    }
    QJsonObject cityWeather = documentWeather.object();
    QJsonArray cityWeatherInfo = cityWeather["daily"].toArray();
    for (int j = 0; j < cityWeatherInfo.size(); j++)
    {
        QJsonObject dailyWeather = cityWeatherInfo[j].toObject();
        QString weather = dailyWeather["textDay"].toString();        
        QString weatherData = dailyWeather["fxDate"].toString();

        QString tempMax = dailyWeather["tempMax"].toString();
        QString tempMin = dailyWeather["tempMin"].toString();
        QString tempRange = QString("%1~%2").arg(tempMax).arg(tempMin);
        QString pressure = dailyWeather["pressure"].toString();


        QStringList weatherList;
        weatherList << weatherData << admain << cityName << weather << tempRange << pressure;
        emit signal_weatherList(weatherList);
    }
}

void HttpHandle::searchCityId(const QString &searchData)
{
    QByteArray geoData = postSearch(searchData);

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(geoData, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << "解析位置信息失败！错误原因: " << error.errorString();
        return ;
    }

    QJsonObject cityArray = document.object();
    QJsonArray cityLocation = cityArray["location"].toArray();
    for (int i = 0; i < cityLocation.size(); i++)
    {
        QJsonObject cityInfo = cityLocation[i].toObject();
        QString cityNameId = cityInfo["id"].toString();
        QString cityName = cityInfo["name"].toString();
        QString admain =cityInfo["adm1"].toString();
        searchCityWeather(cityNameId, cityName, admain);
    }
}
