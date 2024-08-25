#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QLabel>
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
};

#endif // WEATHER_H
