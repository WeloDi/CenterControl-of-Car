#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initScreen();
    initTime();
    initMenuBar();
    initApp();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initScreen()
{
    //设置屏幕尺寸
#if __arm__
    // 获取当前屏幕
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    width = screenGeometry.width();
    height = screenGeometry.height();
    this->resize(width, height);
#else
    this->resize(width,height);
#endif
    //设置背景图
    wallpaper = new QLabel(this);
    wallpaper->resize(width,height);
    wallpaper->move(0,0);
    wallpaper->setPixmap(QPixmap(":/resource/image/car.jpg").scaled(width,height));
}

void Widget::initTime()
{
    int time_width = width / 5;
    int time_height = height / 7;
    // QGridLayout *gridLayout = new QGridLayout(this);

    // 创建时间标签
    timeLabel = new QLabel(this);
    timeLabel->setObjectName("timeLabel");
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setStyleSheet("background:transparent;color:white;font-family:'Microsoft YaHei';font-size: 80px;");
    timeLabel->setGeometry(QRect(width/2 - time_width/2, height/10, time_width, time_height));

    // 创建日期标签
    dateLabel = new QLabel(this);
    dateLabel->setObjectName("dateLabel");
    dateLabel->setAlignment(Qt::AlignCenter);
    dateLabel->setStyleSheet("background:transparent;color:white;font-family:'Microsoft YaHei';font-size: 30px;");
    dateLabel->setGeometry(QRect(width/2 - time_width/2, height/8 + time_height, time_width, time_height/2));


    // 创建定时器并设置定时器事件
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateTime);
    timer->start(1000); // 每秒更新一次
}

void Widget::initMenuBar()
{
    int width_bar = width * 0.99;
    int height_bar = height / 7;
    int pos_x = (width - width_bar)/2;
    int pos_y = height - height_bar - 8;

    int width_btn = width_bar / 13;
    int height_btn = height_bar * 0.8;

    //创建菜单栏
    // menuBar = new QLabel(this);
    menuBar = new QWidget(this);
    menuBar->setObjectName("menubar");
    menuBar->setStyleSheet("background-color:rgba(160,160,160,0.7);border-radius: 25px;");
    menuBar->setGeometry(QRect(pos_x, pos_y, width_bar, height_bar));

    // 创建按钮并设置图标

    btn_home = new QPushButton(menuBar);
    btn_home->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_home->setIcon(QIcon(":/resource/image/home.png"));
    btn_home->setIconSize(QSize(width_btn, height_btn));
    connect(btn_home, &QPushButton::clicked, this, &Widget::onbtn_homeClicked);

    btn_music = new QPushButton(menuBar);
    btn_music->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_music->setIcon(QIcon(":/resource/image/QQ音乐.png"));
    btn_music->setIconSize(QSize(width_btn, height_btn));
    connect(btn_music, &QPushButton::clicked, this, &Widget::onbtn_musicClicked);

    btn_bilibili = new QPushButton(menuBar);
    btn_bilibili->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_bilibili->setIcon(QIcon(":/resource/image/bilibili.png"));
    btn_bilibili->setIconSize(QSize(width_btn, height_btn));
    connect(btn_bilibili, &QPushButton::clicked, this, &Widget::onbtn_bilibiliClicked);

    btn_map = new QPushButton(menuBar);
    btn_map->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_map->setIcon(QIcon(":/resource/image/高德地图.png"));
    btn_map->setIconSize(QSize(width_btn, height_btn));
    connect(btn_map, &QPushButton::clicked, this, &Widget::onbtn_mapClicked);

    btn_weather = new QPushButton(menuBar);
    btn_weather->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_weather->setIcon(QIcon(":/resource/image/天气.png"));
    btn_weather->setIconSize(QSize(width_btn+10, height_btn+10));
    connect(btn_weather, &QPushButton::clicked, this, &Widget::onbtn_weatherClicked);

    btn_voice = new QPushButton(menuBar);
    btn_voice->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_voice->setIcon(QIcon(":/resource/image/siri.png"));
    btn_voice->setIconSize(QSize(width_btn, height_btn));
    connect(btn_voice, &QPushButton::clicked, this, &Widget::onbtn_voiceClicked);

    btn_centerCtrl = new QPushButton(menuBar);
    btn_centerCtrl->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_centerCtrl->setIcon(QIcon(":/resource/image/控制中心.png"));
    btn_centerCtrl->setIconSize(QSize(width_btn, height_btn));
    connect(btn_centerCtrl, &QPushButton::clicked, this, &Widget::onbtn_centerCtrlClicked);

    //将按钮添加到布局中
    layout = new QHBoxLayout(menuBar);
    layout->addStretch();
    layout->addWidget(btn_home);
    layout->addWidget(btn_centerCtrl);
    layout->addWidget(btn_voice);
    layout->addWidget(btn_music);
    layout->addWidget(btn_bilibili);
    layout->addWidget(btn_map);
    layout->addWidget(btn_weather);
    layout->addStretch();
    menuBar->setLayout(layout);

}

void Widget::initApp()
{

    // 初始化StackedWidget用于存放不同应用的界面
    stackedWidget = new QStackedWidget(this);
    stackedWidget->setGeometry(0, 0, this->width, this->height - menuBar->height());

    //空白页
    QWidget *defaultPage = new QWidget(this);
    defaultPage->setStyleSheet("background: transparent;");
    stackedWidget->addWidget(defaultPage);

    //控制中心
    page_ctrlCenter = new CtrlCenter(this);
    page_ctrlCenter->width = this->width;
    page_ctrlCenter->height = this->height;

    //语音助手
    page_voiceAsst = new VoiceAsst(this);
    page_voiceAsst->width = this->width;
    page_voiceAsst->height = this->height;


    //QQmusic
    page_qqMusic = new QQMusic(this);
    page_qqMusic->width = this->width;
    page_qqMusic->height = this->height;

    //Bilbili
    page_Bilibili = new BiLiBiLi(this);
    page_Bilibili->width = this->width;
    page_Bilibili->height = this->height;

    //高德地图
    page_gaoDe = new GaoDeMAP(this);
    page_gaoDe->width = this->width;
    page_gaoDe->height = this->height;

    //天气
    page_weather = new Weather(this);
    page_weather->width = this->width;
    page_weather->height = this->height;

    stackedWidget->addWidget(page_ctrlCenter);
    stackedWidget->addWidget(page_voiceAsst);
    stackedWidget->addWidget(page_qqMusic);
    stackedWidget->addWidget(page_Bilibili);
    stackedWidget->addWidget(page_gaoDe);
    stackedWidget->addWidget(page_weather);

}

void Widget::updateTime()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString date = curTime.toString("yyyy-MM-dd");
    QString time = curTime.toString("HH:mm");
    dateLabel->setText(date);
    timeLabel->setText(time);
}

void Widget::onbtn_homeClicked()
{
    stackedWidget->setCurrentIndex(0);
    wallpaper->show();
    timeLabel->show();
    dateLabel->show();
}

void Widget::onbtn_centerCtrlClicked()
{
    timeLabel->hide();
    dateLabel->hide();
    wallpaper->hide();
    stackedWidget->setCurrentIndex(1);
}

void Widget::onbtn_voiceClicked()
{
    timeLabel->hide();
    dateLabel->hide();
    wallpaper->hide();
    stackedWidget->setCurrentIndex(2);
}

void Widget::onbtn_musicClicked()
{
    timeLabel->hide();
    dateLabel->hide();
    wallpaper->hide();
    stackedWidget->setCurrentIndex(3);
}

void Widget::onbtn_bilibiliClicked()
{
    timeLabel->hide();
    dateLabel->hide();
    wallpaper->hide();
    stackedWidget->setCurrentIndex(4);
}

void Widget::onbtn_mapClicked()
{
    timeLabel->hide();
    dateLabel->hide();
    wallpaper->hide();
    stackedWidget->setCurrentIndex(5);
}

void Widget::onbtn_weatherClicked()
{
    timeLabel->hide();
    dateLabel->hide();
    wallpaper->hide();
    stackedWidget->setCurrentIndex(6);
}

