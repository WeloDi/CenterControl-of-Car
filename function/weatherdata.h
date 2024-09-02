#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QMessageBox>
#include <QDebug>
#include <QEventLoop>
struct Dayinfo
{
    QString fxDate;     //日期
    QString textDay;    //白天天气状况
    QString iconDay;    //白天图标序列
    QString tempMax;    //最高温
    QString tempMin;    //最低温
};

struct WeatherInfo
{
    QString cityName;   //城市名
    QString citycode;   //城市码
    QString temp;       //温度
    QString weather_txt;//天气
    QString weather_icon;//图标
    QString feelsLike;  //体感温度
    QString windDir;    //风向
    QString windScale;  //风力
    QString humidity;   //湿度
    QString pressure;   //压强
    Dayinfo day[7];
};

class WeatherData : public QObject
{
    Q_OBJECT
public:
    WeatherData();
    WeatherInfo info;
    bool getWeatherData();
private:
    QNetworkAccessManager *myNetAccessManager;
    bool updataFlag = false;

    void upData(int type);
    void parse_json(QByteArray &byteArray);
private slots:
    void onReply(QNetworkReply *replay);

signals:
    void weatherDataUpdated();
};

#endif // WEATHERDATA_H
