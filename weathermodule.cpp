#include "weathermodule.h"
#include "ui_weathermodule.h"

WeatherModule::WeatherModule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeatherModule)
{
    ui->setupUi(this);

    //设置控件主体
    this->setObjectName("myWidget");
    this->setStyleSheet("background-color:rgba(128, 128, 128, 0.6);border-radius: 20px;");
}

WeatherModule::~WeatherModule()
{
    delete ui;
}

void WeatherModule::initLayout()
{
    leftWidget = new QWidget(this);
    leftWidget->resize(width/2,height);
    leftWidget->setStyleSheet("background-color: transparent;");


    moduleName = new QLabel(leftWidget);
    moduleName->setGeometry(20,20,width/5,width/8);
    moduleName->setStyleSheet("background-color: transparent;color: white;font-size: 14px;");

    modulevalue = new QLabel(leftWidget);
    modulevalue->setGeometry(20,50,100,40);
    modulevalue->setStyleSheet("background-color: transparent;color: white;font-size: 30px;");
    QVBoxLayout *vlayout = new QVBoxLayout(leftWidget);
    vlayout->addStretch(1);
    vlayout->addWidget(moduleName);
    vlayout->addWidget(modulevalue);
    vlayout->addStretch(1);
    leftWidget->setLayout(vlayout);


    moduleicon = new QLabel(this);
    moduleicon->setGeometry(200,30,100,100);
    moduleicon->setStyleSheet("background-color: transparent;");

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addStretch(1);
    hlayout->addWidget(leftWidget);
    hlayout->addStretch(1);
    hlayout->addWidget(moduleicon);
    hlayout->addStretch(1);
    this->setLayout(hlayout);

}

void WeatherModule::setSize(int w, int h)
{
    this->width = w;
    this->height = h;
    this->resize(width,height);
}

void WeatherModule::setName(const QString name)
{
    moduleName->setText(name);
}

void WeatherModule::setValue(const QString value)
{
    modulevalue->setText(value);
}

void WeatherModule::setIcon(const QPixmap pix)
{
    moduleicon->setPixmap(pix);
}
