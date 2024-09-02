#include "ui/weather.h"
#include "ui_weather.h"

Weather::Weather(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Weather)
{
    ui->setupUi(this);

    wallpaper = new QLabel(this);
    wallpaper->move(0,0);
    wallpaper->raise();

    //创建定时任务：实时获取天气信息
    timerUpdata = new QTimer(this);
    connect(timerUpdata, &QTimer::timeout, this, &Weather::onTimerUpdata);
    timerUpdata->start(3600000);//每小时更新一次

    updateAll();//首次更新
}

Weather::~Weather()
{
    delete ui;
}

void Weather::initScreen()
{

    this->setFixedSize(width,height);
    this->setStyleSheet("background-color: rgba(138, 180, 221, 1)");
    wallpaper->setFixedSize(width,height);
    wallpaper->setStyleSheet("background-color: rgba(138, 180, 221, 0.2);");

    //尺寸
    int menuBar_width = width / 12;
    int statusBar_height = height * 0.05;
    int left_width = (width - menuBar_width)/2 - 10;
    int left_height = height - statusBar_height;

    ui->leftwidget->setFixedSize(left_width,left_height);
    ui->rightwidget->setFixedSize(left_width,left_height);

    ui->cur_widget->setFixedSize(left_width,left_height/2-10);
    ui->module_widget->setFixedSize(left_width,left_height/2-10);

    ui->line1->setFixedHeight((left_height / 2 - 10) * 0.2);
    ui->line2->setFixedHeight((left_height / 2 - 10) * 0.6);
    ui->line3->setFixedHeight((left_height / 2 - 10) * 0.2);

    ui->local_icon->setFixedSize(left_width * 0.05,left_width * 0.05);
    ui->local_icon->setScaledContents(true);

    ui->air_icon->setFixedSize(left_width * 0.08,left_width * 0.08);
    ui->air_icon->setScaledContents(true);

    ui->weather_icon->setFixedSize(left_width/3,left_width/3);
    ui->weather_icon->setScaledContents(true);

    ui->humidity->setStyleSheet("background-color: rgba(128, 128, 128, 0.5);border-radius: 30px;");
    ui->wind->setStyleSheet("background-color: rgba(128, 128, 128, 0.5);border-radius: 30px;");
    ui->pressure->setStyleSheet("background-color: rgba(128, 128, 128, 0.5);border-radius: 30px;");
    ui->feelsLike->setStyleSheet("background-color: rgba(128, 128, 128, 0.5);border-radius: 30px;");
    ui->humidity_icon->setFixedSize(left_width/2/3,left_height/4/2);
    ui->wind_icon->setFixedSize(left_width/2/3,left_height/4/2);
    ui->pressure_icon->setFixedSize(left_width/2/3,left_height/4/2);
    ui->feelsLike_icon->setFixedSize(left_width/2/3-10,left_height/4/2-10);
    ui->humidity_icon->setScaledContents(true);
    ui->wind_icon->setScaledContents(true);
    ui->pressure_icon->setScaledContents(true);
    ui->feelsLike_icon->setScaledContents(true);

    ui->Weather_txt1->setFixedWidth(left_width/14);
    ui->Weather_txt2->setFixedWidth(left_width/14);
    ui->Weather_txt3->setFixedWidth(left_width/14);
    ui->Weather_txt4->setFixedWidth(left_width/14);
    ui->Weather_txt5->setFixedWidth(left_width/14);
    ui->Weather_txt6->setFixedWidth(left_width/14);
    ui->Weather_txt7->setFixedWidth(left_width/14);

    ui->Weather_icon1->setFixedSize(left_width/12,left_width/12);
    ui->Weather_icon1->setScaledContents(true);
    ui->Weather_icon2->setFixedSize(left_width/12,left_width/12);
    ui->Weather_icon2->setScaledContents(true);
    ui->Weather_icon3->setFixedSize(left_width/12,left_width/12);
    ui->Weather_icon3->setScaledContents(true);
    ui->Weather_icon4->setFixedSize(left_width/12,left_width/12);
    ui->Weather_icon4->setScaledContents(true);
    ui->Weather_icon5->setFixedSize(left_width/12,left_width/12);
    ui->Weather_icon5->setScaledContents(true);
    ui->Weather_icon6->setFixedSize(left_width/12,left_width/12);
    ui->Weather_icon6->setScaledContents(true);
    ui->Weather_icon7->setFixedSize(left_width/12,left_width/12);
    ui->Weather_icon7->setScaledContents(true);
}

void Weather::updateFuture(QLabel *day_txt, QLabel *Weather_txt, QLabel *Weather_icon, QLabel *TempMin, QLabel *TempMax,int index)
{
    day_txt->setText(weatherdata.info.day[index].fxDate.mid(5));
    Weather_txt->setText(weatherdata.info.day[index].textDay);
    TempMin->setText(weatherdata.info.day[index].tempMin);
    TempMax->setText(weatherdata.info.day[index].tempMax);
    QString icon_name = ":/resource/weather/icons/" + weatherdata.info.day[index].iconDay + ".png";
    qDebug() << icon_name;
    Weather_icon->setPixmap(QPixmap(icon_name));
}

void Weather::updateAll()
{
    weatherdata.getWeatherData();

    ui->local_name->setText(weatherdata.info.cityName);
    ui->temp->setText(weatherdata.info.temp);
    ui->weather_txt->setText(weatherdata.info.weather_txt);
    QString icon_name = ":/resource/weather/icons/" + weatherdata.info.weather_icon + ".png";
    qDebug() << icon_name;
    ui->weather_icon->setPixmap(QPixmap(icon_name));
    ui->air_txt->setText("空气优 30");

    ui->humidity_value->setText(weatherdata.info.humidity + "%");
    ui->wind_name->setText(weatherdata.info.windDir);
    ui->wind_value->setText(weatherdata.info.windScale+"级");
    ui->pressure_value->setText(weatherdata.info.pressure);
    ui->feelsLike_value->setText(weatherdata.info.feelsLike);

    for(int i = 0; i < 7; i++)
    {
        switch (i)
        {
            case 0:
                updateFuture(ui->day_txt1, ui->Weather_txt1,ui->Weather_icon1, ui->TempMin1, ui->TempMax1,0);
                break;
            case 1:
                updateFuture(ui->day_txt2, ui->Weather_txt2,ui->Weather_icon2, ui->TempMin2, ui->TempMax2,1);
                break;
            case 2:
                updateFuture(ui->day_txt3, ui->Weather_txt3,ui->Weather_icon3, ui->TempMin3, ui->TempMax3,2);
                break;
            case 3:
                updateFuture(ui->day_txt4, ui->Weather_txt4,ui->Weather_icon4, ui->TempMin4, ui->TempMax4,3);
                break;
            case 4:
                updateFuture(ui->day_txt5, ui->Weather_txt5,ui->Weather_icon5, ui->TempMin5, ui->TempMax5,4);
                break;
            case 5:
                updateFuture(ui->day_txt6, ui->Weather_txt6,ui->Weather_icon6, ui->TempMin6, ui->TempMax6,5);
                break;
            case 6:
                updateFuture(ui->day_txt7, ui->Weather_txt7,ui->Weather_icon7, ui->TempMin7, ui->TempMax7,6);
                break;
            default:
                break;
        }
    }
}


void Weather::onTimerUpdata()
{
    updateAll();
}
