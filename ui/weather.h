#ifndef WEATHER_H
#define WEATHER_H

#include "function/weatherdata.h"
#include <QWidget>
#include <QLabel>
#include <QTimer>

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

private:
    Ui::Weather *ui;
    QTimer *timerUpdata;
    WeatherData weatherdata;
    void updateFuture(QLabel *day_txt, QLabel *Weather_txt, QLabel *Weather_icon, QLabel *TempMin, QLabel *TempMax,int index);
    void updateAll();
private slots:
    void onTimerUpdata();
};

#endif // WEATHER_H
