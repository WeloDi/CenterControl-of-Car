#include "weather.h"
#include "ui_weather.h"

Weather::Weather(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Weather)
{
    ui->setupUi(this);

    wallpaper = new QLabel(this);
    wallpaper->move(0,0);
}

Weather::~Weather()
{
    delete ui;
}

void Weather::initScreen()
{
    this->resize(width,height);
    wallpaper->setPixmap(QPixmap(":/resource/music/蓝色渐变.jpg").scaled(width,height));
}
