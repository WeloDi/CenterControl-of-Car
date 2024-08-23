#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>

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

    int width = 1024;
    int height = 600;

private:
    Ui::Weather *ui;
};

#endif // WEATHER_H
