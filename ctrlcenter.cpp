#include "ctrlcenter.h"
#include "ui_ctrlcenter.h"
#include <iostream>
CtrlCenter::CtrlCenter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CtrlCenter)
{
    ui->setupUi(this);

    initVoice();
    initBrightness();

}

CtrlCenter::~CtrlCenter()
{
    delete ui;
}

void CtrlCenter::initScreen()
{
    wallpaper = new QLabel(this);
    wallpaper->move(0,0);
    this->resize(width,height);
    wallpaper->resize(width,height);
    wallpaper->setStyleSheet("QLabel{background-color:rgb(35,35,35);}");
    wallpaper->lower();//显示在最下层
}

void CtrlCenter::initVoice()
{
    volume = new QSlider(Qt::Vertical, this);
    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(20);
    volume->setInvertedAppearance(false);
    volume->setGeometry(200,100,40,height/5);
    volume->setStyleSheet(
        "QSlider::groove:vertical {"
        "   border: 1px solid #999999;"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #c4c4c4);"
        "   height: 150px;"
        "   margin: 0px 0;"
        "   border-radius: 10px;"
        "}"

        "QSlider::handle:vertical {"
        "   background: transparent;"
        "   border: 0px solid #5c5c5c;"
        "   width: 50px;"
        "   height: 30px;"
        "   margin: -2px 0;"
        "   border-radius: 10px;"
        "}"

        "QSlider::sub-page:vertical {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
        "   border-radius: 0px;"
        "}"
    );
    connect(volume, &QSlider::valueChanged, this, &CtrlCenter::onvolumeValueChanged);
}

void CtrlCenter::initBrightness()
{
    brightness = new QSlider(Qt::Vertical, this);
    brightness->setMinimum(2);
    brightness->setMaximum(52);
    brightness->setValue(40);
    brightness->setGeometry(300,100,40,height/5);
    brightness->setStyleSheet(
        "QSlider::groove:vertical {"
        "   border: 1px solid #999999;"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #c4c4c4);"
        "   height: 150px;"
        "   margin: 0px 0;"
        "   border-radius: 10px;"
        "}"

        "QSlider::handle:vertical {"
        "   background: transparent;"
        "   border: 0px solid #5c5c5c;"
        "   width: 50px;"
        "   height: 30px;"
        "   margin: -2px 0;"
        "   border-radius: 10px;"
        "}"

        "QSlider::sub-page:vertical {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
        "   border-radius: 0px;"
        "}"
    );
    connect(brightness, &QSlider::valueChanged, this, &CtrlCenter::onbrightnessChanged);
}


void CtrlCenter::onvolumeValueChanged(int value)
{

}


void CtrlCenter::onbrightnessChanged(int value)
{
    QString command = "echo " + QString::number(value)+ " > /sys/devices/platform/backlight/backlight/backlight/brightness";
    system(command.toUtf8().constData());
}
