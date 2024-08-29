#include "ui/car.h"
#include "ui_car.h"

Car::Car(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Car)
{
    ui->setupUi(this);

    wallpaper = new QLabel(this);
    wallpaper->move(0,0);
}

Car::~Car()
{
    delete ui;
}

void Car::initScreen()
{
    this->resize(width,height);
    wallpaper->setPixmap(QPixmap(":/resource/music/蓝色渐变.jpg").scaled(width,height));
}
