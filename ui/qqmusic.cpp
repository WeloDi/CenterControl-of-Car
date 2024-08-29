#include "ui/qqmusic.h"
#include "ui_qqmusic.h"

QQMusic::QQMusic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QQMusic)
{
    ui->setupUi(this);
    wallpaper = new QLabel(this);
    wallpaper->move(0,0);

}

QQMusic::~QQMusic()
{
    delete ui;
}

void QQMusic::initScreen()
{
    this->resize(width,height);
    wallpaper->setPixmap(QPixmap(":/resource/music/蓝色渐变.jpg").scaled(width,height));
}
