#include "gaodemap.h"
#include "ui_gaodemap.h"

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
