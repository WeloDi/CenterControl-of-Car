#ifndef WIDGET_H
#define WIDGET_H
#include <iostream>
#include <QWidget>
#include <QScreen>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QTimer>
#include <QDateTime>
#include <QGridLayout>
#include <QPushButton>
#include <QStackedWidget>
#include "qqmusic.h"
#include "bilibili.h"
#include "ctrlcenter.h"
#include "gaodemap.h"
#include "weather.h"
#include "voiceasst.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    //background
    int width = 1024;
    int height = 600;
    QLabel *wallpaper;
    QLabel *timeLabel;
    QLabel *dateLabel;

    //menu bar
    QWidget *menuBar;
    QPushButton *btn_home;
    QPushButton *btn_music;
    QPushButton *btn_map;
    QPushButton *btn_voice;
    QPushButton *btn_centerCtrl;
    QPushButton *btn_bilibili;
    QPushButton *btn_weather;
    QHBoxLayout *layout;

    //APP
    QStackedWidget *stackedWidget;
    CtrlCenter *page_ctrlCenter;
    VoiceAsst *page_voiceAsst;
    QQMusic *page_qqMusic;
    BiLiBiLi *page_Bilibili;
    GaoDeMAP *page_gaoDe;
    Weather *page_weather;

    void initScreen();
    void initTime();
    void initMenuBar();
    void initApp();

private slots:
    void updateTime();
    void onbtn_homeClicked();
    void onbtn_centerCtrlClicked();
    void onbtn_voiceClicked();
    void onbtn_musicClicked();
    void onbtn_bilibiliClicked();
    void onbtn_mapClicked();
    void onbtn_weatherClicked();


};
#endif // WIDGET_H
