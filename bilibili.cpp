#include "bilibili.h"
#include "ui_bilibili.h"

BiLiBiLi::BiLiBiLi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BiLiBiLi)
{
    ui->setupUi(this);
}

BiLiBiLi::~BiLiBiLi()
{
    delete ui;
}
