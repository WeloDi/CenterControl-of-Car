#include "voiceasst.h"
#include "ui_voiceasst.h"

VoiceAsst::VoiceAsst(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VoiceAsst)
{
    ui->setupUi(this);

    wallpaper = new QLabel(this);
    wallpaper->move(0,0);
}

VoiceAsst::~VoiceAsst()
{
    delete ui;
}

void VoiceAsst::initScreen()
{
    this->resize(width,height);
    wallpaper->setPixmap(QPixmap(":/resource/music/蓝色渐变.jpg").scaled(width,height));
}
