#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QByteArray>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include "weathermodule.h"

struct WeatherInfo
{
    QString fxDate;//日期
    QString tempMax;
    QString tempMin;
    QString textDay;//白天天气状况
    QString iconDay;//图标序列
};

namespace Ui
{
class Weather;
}

class Weather : public QWidget
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = nullptr);
    ~Weather();

    //background
    int width = 1024;
    int height = 600;
    QLabel *wallpaper;

    void initScreen();
    void updataNatureData();
private:
    Ui::Weather *ui;
    QNetworkAccessManager *myNetAccessManager;
    QString cityName = "";
    QString citycode = "";
    QTimer *timerUpdata;

    struct WeatherInfo weatherInfo;

    //module
    // QWidget *moduleData;
    // WeatherModule *humidity;
    // WeatherModule *wind;
    // WeatherModule *pressure;
    // WeatherModule *feelsLike;

    void updateWeatherInfo(QLabel *day_txt, QLabel *Weather_txt,QLabel *icon, QLabel *TempMin, QLabel *TempMax);
    void getData(int type);
    void parse_json(QByteArray &byteArray);

private slots:
    void onReply(QNetworkReply *replay);
    void onTimerUpdata();

};

#endif // WEATHER_H
