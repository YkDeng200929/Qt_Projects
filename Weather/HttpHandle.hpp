#ifndef HTTPHANDLE_HPP
#define HTTPHANDLE_HPP

#include <QObject>
#include <QNetworkAccessManager>

class HttpHandle : public QObject
{
    Q_OBJECT
public:
    explicit HttpHandle(QObject *parent = nullptr);

    // 发送搜索请求
    QByteArray postSearch(const QString &city);
    // 发送指定城市
    QByteArray postCityForWeather(const QString &cityId);
    // 搜索城市天气
    void searchCityWeather(const QString &cityId, const QString &cityName, const QString &admain);
    // 通过城市ID获取天气信息
    void searchCityId(const QString &searchData);
    // 获取预警信息
    void get_warning_info();

signals:
    // 把天气信息发送给主界面
    void signal_weatherList(QStringList weatherList);

public slots:

private:
    QNetworkAccessManager *manager;
    QString weather_api = "9d1f7a5a2db8467dbbd828b176315fe5";
};

#endif // HTTPHANDLE_HPP
