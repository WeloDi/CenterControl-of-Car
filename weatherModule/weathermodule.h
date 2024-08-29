#ifndef WEATHERMODULE_H
#define WEATHERMODULE_H

#include <QWidget>

class WeatherModule : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherModule(QWidget *parent = nullptr);
};

#endif // WEATHERMODULE_H
