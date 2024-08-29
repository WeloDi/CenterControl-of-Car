#include "ui/gaodemap.h"
#include "ui_gaodemap.h"

GaoDeMAP::GaoDeMAP(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GaoDeMAP)
{
    ui->setupUi(this);
    wallpaper = new QLabel(this);
    wallpaper->move(0,0);
}

GaoDeMAP::~GaoDeMAP()
{
    delete ui;
}

void GaoDeMAP::initScreen()
{
    this->resize(width,height);
    wallpaper->setPixmap(QPixmap(":/resource/music/蓝色渐变.jpg").scaled(width,height));
}
