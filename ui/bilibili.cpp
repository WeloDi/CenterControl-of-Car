#include "ui/bilibili.h"
#include "ui_bilibili.h"

BiLiBiLi::BiLiBiLi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BiLiBiLi)
{
    ui->setupUi(this);
    wallpaper = new QLabel(this);
    wallpaper->move(0,0);

}

BiLiBiLi::~BiLiBiLi()
{
    delete ui;
}

void BiLiBiLi::initScreen()
{
    this->resize(width,height);
    wallpaper->setPixmap(QPixmap(":/resource/music/蓝色渐变.jpg").scaled(width,height));
}

