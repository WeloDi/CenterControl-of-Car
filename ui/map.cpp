#include "ui/map.h"
#include "ui_map.h"

GaoDeMAP::GaoDeMAP(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GaoDeMAP)
{
    ui->setupUi(this);


}

GaoDeMAP::~GaoDeMAP()
{
    delete ui;
}

void GaoDeMAP::initScreen()
{
    this->setFixedSize(width,height);

    wallPaper = new QLabel(this);
    wallPaper->setFixedSize(width,height);
    wallPaper->setStyleSheet("background-color:rgb(70,70,70);");
    wallPaper->lower();

    ui->mainWidget->setFixedSize(width - width/12 - 5,height);
    ui->mainHLayout->setContentsMargins(0,0,0,0);

    ui->webview->load(QUrl(QString("file:///home/deng/i.mx6ull/project/CenterControl_of_Car/html_map/location.html")));

}
