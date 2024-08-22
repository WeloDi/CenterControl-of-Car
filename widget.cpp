#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initScreen();
    initTime();
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
    //创建菜单栏背景
    menuBar = new QLabel(this);
    menuBar->setObjectName("menubar");
    menuBar->setStyleSheet("background-color:rgba(66, 66 66, 1);border-radius: 25px;");
    menuBar->setGeometry(QRect((width - width_bar)/2, height - height_bar - 10, width_bar, height_bar));

}

void Widget::updateTime()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString date = curTime.toString("yyyy-MM-dd");
    QString time = curTime.toString("HH:mm");
    dateLabel->setText(date);
    timeLabel->setText(time);
}


