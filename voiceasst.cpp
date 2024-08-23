#include "voiceasst.h"
#include "ui_voiceasst.h"

VoiceAsst::VoiceAsst(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VoiceAsst)
{
    ui->setupUi(this);
}

VoiceAsst::~VoiceAsst()
{
    delete ui;
}
