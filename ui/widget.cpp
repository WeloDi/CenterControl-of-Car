#include "ui/widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initApp();
    initScreen();
    initStatusBar();
    initMenuBar();
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
    wallpaper->setPixmap(QPixmap(":/resource/home/background.jpg").scaled(width,height));
}

void Widget::initStatusBar()
{
    status_w = width;
    status_h = height * 0.05;
    statusBar = new QWidget(this);
    // statusBar->setStyleSheet("background-color:rgb(0,0,0);");
    statusBar->setGeometry(QRect(0, 0, status_w, status_h));

    //时间显示
    int time_h = status_h * 0.8;
    int time_w = time_h * 2;
    timeLabel = new QLabel(this);
    timeLabel->setObjectName("timeLabel");
    timeLabel->setAlignment(Qt::AlignTop);
    timeLabel->setStyleSheet("background:transparent;color:white;font-family:'Microsoft YaHei';font-size: 18px;");
    timeLabel->resize(time_w, time_h);

    // 创建定时器并设置定时器事件
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateTime);
    timer->start(1000); // 每秒更新一次

    //wifi图标显示
    int wifi_h = status_h * 0.7;
    int wifi_w = status_h * 0.75;

    wifiLabel = new QLabel(this);
    wifiLabel->setObjectName("wifiLabel");
    wifiLabel->setAlignment(Qt::AlignCenter);
    wifiLabel->setStyleSheet("background:transparent;");
    wifiLabel->resize(wifi_w, wifi_h);

    //查询wifi状态
    wifiLabel->setPixmap(QPixmap(":/resource/statusbar/wifi_lv3.png").scaled(wifi_w,wifi_h));

    layout_status = new QHBoxLayout(this);
    layout_status->setSpacing(10);//图标间距
    layout_status->setContentsMargins(0, 0, 4, 4);
    layout_status->addStretch(1);
    layout_status->addWidget(wifiLabel);
    layout_status->addWidget(timeLabel);
    statusBar->setLayout(layout_status);
}

void Widget::initMenuBar()
{
    menu_w = width / 12;
    menu_h = height;
    int pos_x = 0;
    int pos_y = 0;

    int width_btn = menu_w * 0.7;
    int height_btn = width_btn;

    //创建菜单栏
    menuBar = new QWidget(this);
    menuBar->setObjectName("menubar");
    menuBar->setStyleSheet("background-color:rgba(50,50,50,0.6);border-top-right-radius: 15px;border-bottom-right-radius: 15px;");
    menuBar->setGeometry(QRect(pos_x, pos_y, menu_w, menu_h));

    // 创建按钮并设置图标
    btn_voice = new QPushButton(menuBar);
    btn_voice->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_voice->setIcon(QIcon(":/resource/appIcon/siri_off.png"));
    btn_voice->setIconSize(QSize(width_btn*0.6, height_btn*0.6));
    connect(btn_voice, &QPushButton::clicked, this, &Widget::onbtn_voiceClicked);

    btn_music = new QPushButton(menuBar);
    btn_music->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_music->setIcon(QIcon(":/resource/appIcon/音乐_off.png"));
    btn_music->setIconSize(QSize(width_btn*0.6, height_btn*0.6));
    connect(btn_music, &QPushButton::clicked, this, &Widget::onbtn_musicClicked);

    btn_bilibili = new QPushButton(menuBar);
    btn_bilibili->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_bilibili->setIcon(QIcon(":/resource/appIcon/摄像头_off.png"));
    btn_bilibili->setIconSize(QSize(width_btn*0.6, height_btn*0.6));
    connect(btn_bilibili, &QPushButton::clicked, this, &Widget::onbtn_bilibiliClicked);

    btn_map = new QPushButton(menuBar);
    btn_map->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_map->setIcon(QIcon(":/resource/appIcon/导航_off.png"));
    btn_map->setIconSize(QSize(width_btn*0.6, height_btn*0.6));
    connect(btn_map, &QPushButton::clicked, this, &Widget::onbtn_mapClicked);

    btn_weather = new QPushButton(menuBar);
    btn_weather->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_weather->setIcon(QIcon(":/resource/appIcon/天气_off.png"));
    btn_weather->setIconSize(QSize(width_btn*0.6, height_btn*0.6));
    connect(btn_weather, &QPushButton::clicked, this, &Widget::onbtn_weatherClicked);

    btn_car = new QPushButton(menuBar);
    btn_car->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_car->setIcon(QIcon(":/resource/appIcon/车辆_off.png"));
    btn_car->setIconSize(QSize(width_btn*0.5, height_btn*0.5));
    connect(btn_car, &QPushButton::clicked, this, &Widget::onbtn_carClicked);

    btn_centerCtrl = new QPushButton(menuBar);
    btn_centerCtrl->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_centerCtrl->setIcon(QIcon(":/resource/appIcon/控制_off.png"));
    btn_centerCtrl->setIconSize(QSize(width_btn*0.7, height_btn*0.7));
    connect(btn_centerCtrl, &QPushButton::clicked, this, &Widget::onbtn_centerCtrlClicked);

    btn_home = new QPushButton(menuBar);
    btn_home->setStyleSheet("border-radius: 27px;background: transparent;");
    btn_home->setIcon(QIcon(":/resource/appIcon/主页_on.png"));
    btn_home->setIconSize(QSize(width_btn*0.5, height_btn*0.5));
    connect(btn_home, &QPushButton::clicked, this, &Widget::onbtn_homeClicked);

    //将按钮添加到布局中
    layout = new QVBoxLayout(menuBar);
    layout->addStretch();
    layout->addWidget(btn_voice);
    layout->addStretch();
    layout->addWidget(btn_music);
    layout->addStretch();
    layout->addWidget(btn_map);
    layout->addStretch();
    layout->addWidget(btn_bilibili);
    layout->addStretch();
    layout->addWidget(btn_weather);
    layout->addStretch();
    layout->addWidget(btn_car);
    layout->addStretch();
    layout->addWidget(btn_centerCtrl);
    layout->addStretch();
    layout->addWidget(btn_home);
    layout->addStretch();
    menuBar->setLayout(layout);

}

void Widget::initApp()
{
    //空白页
    QWidget *defaultPage = new QWidget(this);
    defaultPage->setStyleSheet("background: transparent;");

    //控制中心
    page_ctrlCenter = new CtrlCenter(this);
    page_ctrlCenter->width = this->width;
    page_ctrlCenter->height = this->height;
    page_ctrlCenter->initScreen();

    //语音助手
    page_voiceAsst = new VoiceAsst(this);
    page_voiceAsst->width = this->width;
    page_voiceAsst->height = this->height;
    page_voiceAsst->initScreen();


    //music
    page_Music = new QQMusic(this);
    page_Music->width = this->width;
    page_Music->height = this->height;
    page_Music->initScreen();

    //Bilbili
    page_Bilibili = new BiLiBiLi(this);
    page_Bilibili->width = this->width;
    page_Bilibili->height = this->height;
    page_Bilibili->initScreen();

    //高德地图
    page_gaoDe = new GaoDeMAP(this);
    page_gaoDe->width = this->width;
    page_gaoDe->height = this->height;
    page_gaoDe->initScreen();

    //天气
    page_weather = new Weather(this);
    page_weather->width = this->width;
    page_weather->height = this->height;
    page_weather->initScreen();

    //车辆
    page_car = new Car(this);
    page_car->width = this->width;
    page_car->height = this->height;
    page_car->initScreen();

    // 初始化StackedWidget用于存放不同应用的界面
    stackedWidget = new QStackedWidget(this);
    // stackedWidget->setGeometry(menu_w, 30, this->width - menu_w, this->height - status_h);
    stackedWidget->setGeometry(0, 0, width, height );

    stackedWidget->addWidget(defaultPage);
    stackedWidget->addWidget(page_ctrlCenter);
    stackedWidget->addWidget(page_voiceAsst);
    stackedWidget->addWidget(page_Music);
    stackedWidget->addWidget(page_Bilibili);
    stackedWidget->addWidget(page_gaoDe);
    stackedWidget->addWidget(page_weather);
    stackedWidget->addWidget(page_car);

}

void Widget::updateTime()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString time = curTime.toString("HH:mm");
    timeLabel->setText(time);
}

void Widget::onbtn_homeClicked()
{
    btn_voice->setIcon(QIcon(":/resource/appIcon/siri_off.png"));
    btn_home->setIcon(QIcon(":/resource/appIcon/主页_on.png"));
    btn_centerCtrl->setIcon(QIcon(":/resource/appIcon/控制_off.png"));
    btn_weather->setIcon(QIcon(":/resource/appIcon/天气_off.png"));
    btn_map->setIcon(QIcon(":/resource/appIcon/导航_off.png"));
    btn_bilibili->setIcon(QIcon(":/resource/appIcon/摄像头_off.png"));
    btn_music->setIcon(QIcon(":/resource/appIcon/音乐_off.png"));
    btn_car->setIcon(QIcon(":/resource/appIcon/车辆_off.png"));
    stackedWidget->setCurrentIndex(0);
    wallpaper->show();
}

void Widget::onbtn_centerCtrlClicked()
{
    wallpaper->hide();
    btn_voice->setIcon(QIcon(":/resource/appIcon/siri_off.png"));
    btn_home->setIcon(QIcon(":/resource/appIcon/主页_off.png"));
    btn_weather->setIcon(QIcon(":/resource/appIcon/天气_off.png"));
    btn_map->setIcon(QIcon(":/resource/appIcon/导航_off.png"));
    btn_bilibili->setIcon(QIcon(":/resource/appIcon/摄像头_off.png"));
    btn_music->setIcon(QIcon(":/resource/appIcon/音乐_off.png"));
    btn_car->setIcon(QIcon(":/resource/appIcon/车辆_off.png"));
    btn_centerCtrl->setIcon(QIcon(":/resource/appIcon/控制_on.png"));
    stackedWidget->setCurrentIndex(1);
}

void Widget::onbtn_voiceClicked()
{
    wallpaper->hide();
    btn_voice->setIcon(QIcon(":/resource/appIcon/siri_on.png"));
    btn_home->setIcon(QIcon(":/resource/appIcon/主页_off.png"));
    btn_centerCtrl->setIcon(QIcon(":/resource/appIcon/控制_off.png"));
    btn_weather->setIcon(QIcon(":/resource/appIcon/天气_off.png"));
    btn_map->setIcon(QIcon(":/resource/appIcon/导航_off.png"));
    btn_bilibili->setIcon(QIcon(":/resource/appIcon/摄像头_off.png"));
    btn_car->setIcon(QIcon(":/resource/appIcon/车辆_off.png"));
    btn_music->setIcon(QIcon(":/resource/appIcon/音乐_off.png"));
    stackedWidget->setCurrentIndex(2);
}

void Widget::onbtn_musicClicked()
{
    wallpaper->hide();
    btn_voice->setIcon(QIcon(":/resource/appIcon/siri_off.png"));
    btn_home->setIcon(QIcon(":/resource/appIcon/主页_off.png"));
    btn_centerCtrl->setIcon(QIcon(":/resource/appIcon/控制_off.png"));
    btn_weather->setIcon(QIcon(":/resource/appIcon/天气_off.png"));
    btn_map->setIcon(QIcon(":/resource/appIcon/导航_off.png"));
    btn_bilibili->setIcon(QIcon(":/resource/appIcon/摄像头_off.png"));
    btn_car->setIcon(QIcon(":/resource/appIcon/车辆_off.png"));
    btn_music->setIcon(QIcon(":/resource/appIcon/音乐_on.png"));
    stackedWidget->setCurrentIndex(3);
}

void Widget::onbtn_bilibiliClicked()
{
    wallpaper->hide();
    btn_voice->setIcon(QIcon(":/resource/appIcon/siri_off.png"));
    btn_home->setIcon(QIcon(":/resource/appIcon/主页_off.png"));
    btn_centerCtrl->setIcon(QIcon(":/resource/appIcon/控制_off.png"));
    btn_weather->setIcon(QIcon(":/resource/appIcon/天气_off.png"));
    btn_map->setIcon(QIcon(":/resource/appIcon/导航_off.png"));
    btn_music->setIcon(QIcon(":/resource/appIcon/音乐_off.png"));
    btn_car->setIcon(QIcon(":/resource/appIcon/车辆_off.png"));
    btn_bilibili->setIcon(QIcon(":/resource/appIcon/摄像头_on.png"));
    stackedWidget->setCurrentIndex(4);
}

void Widget::onbtn_mapClicked()
{
    wallpaper->hide();
    btn_voice->setIcon(QIcon(":/resource/appIcon/siri_off.png"));
    btn_home->setIcon(QIcon(":/resource/appIcon/主页_off.png"));
    btn_centerCtrl->setIcon(QIcon(":/resource/appIcon/控制_off.png"));
    btn_weather->setIcon(QIcon(":/resource/appIcon/天气_off.png"));
    btn_bilibili->setIcon(QIcon(":/resource/appIcon/摄像头_off.png"));
    btn_music->setIcon(QIcon(":/resource/appIcon/音乐_off.png"));
    btn_car->setIcon(QIcon(":/resource/appIcon/车辆_off.png"));
    btn_map->setIcon(QIcon(":/resource/appIcon/导航_on.png"));
    stackedWidget->setCurrentIndex(5);
}

void Widget::onbtn_weatherClicked()
{
    wallpaper->hide();
    btn_voice->setIcon(QIcon(":/resource/appIcon/siri_off.png"));
    btn_home->setIcon(QIcon(":/resource/appIcon/主页_off.png"));
    btn_centerCtrl->setIcon(QIcon(":/resource/appIcon/控制_off.png"));
    btn_map->setIcon(QIcon(":/resource/appIcon/导航_off.png"));
    btn_bilibili->setIcon(QIcon(":/resource/appIcon/摄像头_off.png"));
    btn_music->setIcon(QIcon(":/resource/appIcon/音乐_off.png"));
    btn_car->setIcon(QIcon(":/resource/appIcon/车辆_off.png"));
    btn_weather->setIcon(QIcon(":/resource/appIcon/天气_on.png"));
    stackedWidget->setCurrentIndex(6);
}

void Widget::onbtn_carClicked()
{
    wallpaper->hide();
    btn_voice->setIcon(QIcon(":/resource/appIcon/siri_off.png"));
    btn_home->setIcon(QIcon(":/resource/appIcon/主页_off.png"));
    btn_centerCtrl->setIcon(QIcon(":/resource/appIcon/控制_off.png"));
    btn_map->setIcon(QIcon(":/resource/appIcon/导航_off.png"));
    btn_bilibili->setIcon(QIcon(":/resource/appIcon/摄像头_off.png"));
    btn_music->setIcon(QIcon(":/resource/appIcon/音乐_off.png"));
    btn_weather->setIcon(QIcon(":/resource/appIcon/天气_off.png"));
    btn_car->setIcon(QIcon(":/resource/appIcon/车辆_on.png"));
    stackedWidget->setCurrentIndex(7);
}

