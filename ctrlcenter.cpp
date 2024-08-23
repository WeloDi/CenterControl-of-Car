#include "ctrlcenter.h"
#include "ui_ctrlcenter.h"

CtrlCenter::CtrlCenter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CtrlCenter)
{
    ui->setupUi(this);

    volume = new QSlider(Qt::Vertical, this);
    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(20);
    volume->setGeometry(width-50,height/40,40,height/5);
    connect(volume, &QSlider::valueChanged, this, &CtrlCenter::onvolumeValueChanged);

}

CtrlCenter::~CtrlCenter()
{
    delete ui;
}

void CtrlCenter::onvolumeValueChanged()
{

}
