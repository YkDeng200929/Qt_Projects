#ifndef HTTPHANDLE_HPP
#define HTTPHANDLE_HPP

#include <QObject>
#include <QNetworkAccessManager>

class HttpHandle : public QObject
{
    Q_OBJECT
public:
    explicit HttpHandle(QObject *parent = nullptr);
    QByteArray postSearch(const QString &city);
    QByteArray postCityForWeather(const QString &cityId);
    void searchCityWeather(const QString &cityId, const QString &cityName, const QString &admain);
    void searchCityId(const QString &searchData);

signals:
    void signal_weatherList(QStringList weatherList);

public slots:

private:
    QNetworkAccessManager *manager;
};

#endif // HTTPHANDLE_HPP
