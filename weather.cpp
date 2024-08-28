#include "weather.h"
#include "ui_weather.h"

Weather::Weather(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Weather)
{
    ui->setupUi(this);

    wallpaper = new QLabel(this);
    wallpaper->move(0,0);
    wallpaper->lower();

    //创建网络访问管理器
    myNetAccessManager = new QNetworkAccessManager(this);
    connect(myNetAccessManager,&QNetworkAccessManager::finished,this, &Weather::onReply);

    //创建定时任务：实时获取天气信息
    timerUpdata = new QTimer(this);
    connect(timerUpdata, &QTimer::timeout, this, &Weather::onTimerUpdata);
    timerUpdata->start(3600000);//每小时更新一次

    getData(1);//首次更新所有信息
}

Weather::~Weather()
{
    delete ui;
}

void Weather::initScreen()
{
    this->resize(width,height);
    wallpaper->setPixmap(QPixmap(":/resource/weather/sky.jpg").scaled(width,height));

    //布局
    int menuBar_width = width / 12;
    int statusBar_height = height * 0.05;
    int left_width = (width - menuBar_width)/2 - 20;
    int left_height = height - statusBar_height;

    ui->leftwidget->setFixedSize(left_width,left_height);
    ui->rightwidget->setFixedSize(left_width,left_height);
    ui->leftwidget->setStyleSheet("background:transparent;");

    ui->cur_widget->setFixedSize(left_width,left_height/2-10);
    ui->module_widget->setFixedSize(left_width,left_height/2-10);
    ui->cur_widget->setStyleSheet("background:transparent;");
    ui->module_widget->setStyleSheet("background:transparent;");


}

void Weather::updateWeatherInfo(QLabel *day_txt, QLabel *Weather_txt, QLabel *iWeather_icon, QLabel *TempMin, QLabel *TempMax)
{
    day_txt->setText(weatherInfo.fxDate);
    Weather_txt->setText(weatherInfo.textDay);
    TempMin->setText(weatherInfo.tempMin);
    TempMax->setText(weatherInfo.tempMax);
}

void Weather::getData(int type)
{
    QUrl url;
    switch(type)
    {
        case 1:
            //根据IP获取城市名（高德API）
            url = QUrl("https://restapi.amap.com/v3/ip?&output=json&key=c76ff9110dfdbf5bb9cbcd89b8fb7e8f");
            break;
        case 2:
            //和风天气根据城市名获取code
            url = QUrl("https://geoapi.qweather.com/v2/city/lookup?key=0f7271f1c38e42b7b7b5a0951e4dd6f9&location=" + cityName);
            break;
        case 3:
            //和风天气获取当天天气信息
            url = QUrl("https://devapi.qweather.com/v7/weather/now?key=0f7271f1c38e42b7b7b5a0951e4dd6f9&location=" + citycode);
            break;
        case 4:
            //和风天气获取未来7天信息
            url = QUrl("https://devapi.qweather.com/v7/weather/7d?key=0f7271f1c38e42b7b7b5a0951e4dd6f9&location=" + citycode);
            break;
        default:
            break;
    }
    myNetAccessManager->get(QNetworkRequest(url));
}

void Weather::parse_json(QByteArray &byteArray)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(byteArray,&err);
    if(err.error != QJsonParseError::NoError)
    {
        return;
    }

    QJsonObject rootObj = doc.object();

    if (rootObj.contains("city"))
    {
        cityName = rootObj["city"].toString();
        ui->local_name->setText(cityName);
        getData(2);
    }
    else if(rootObj.contains("location"))
    {
        QJsonArray locationArray = rootObj["location"].toArray();   //获取location列表
        QJsonObject firstObject = locationArray.at(0).toObject();   //获取第一个元素
        if (firstObject.contains("id"))
        {
            citycode = firstObject["id"].toString();
            // qDebug() << citycode;
            getData(3);
        }
    }
    else if(rootObj.contains("now"))
    {
        QJsonObject now = rootObj["now"].toObject();
        ui->temp->setText(now["temp"].toString());              //温度
        // feelsLike->setValue(now["feelsLike"].toString());   //体感温度
        QString pixmap_name = now["icon"].toString();
        pixmap_name = ":/resource/weather/" + pixmap_name + ".svg";
        ui->weather_icon->setPixmap(QPixmap(pixmap_name).scaled(100,100));      //设置天气图标
        ui->weather_txt->setText(now["text"].toString());       //天气状况
        // wind->setName(now["windDir"].toString());           //风向
        // wind->setValue(now["windScale"].toString());        //风力
        // humidity->setValue(now["humidity"].toString());     //湿度
        // pressure->setValue(now["pressure"].toString());     //大气压强
        getData(4);
    }
    else if(rootObj.contains("daily"))
    {
        QJsonArray dailyArray = rootObj["daily"].toArray();
        int i = 1;
        for (const QJsonValue &dailyValue : dailyArray)
        {
            if (dailyValue.isObject())
            {
                QJsonObject dailyObj = dailyValue.toObject();
                weatherInfo.fxDate = dailyObj["fxDate"].toString();
                weatherInfo.tempMax = dailyObj["tempMax"].toString();
                weatherInfo.tempMin = dailyObj["tempMin"].toString();
                weatherInfo.textDay = dailyObj["textDay"].toString();
                weatherInfo.iconDay = dailyObj["iconDay"].toString();

                switch (i)
                {
                    case 1:
                        updateWeatherInfo(ui->day_txt1, ui->Weather_txt1,ui->Weather_icon1, ui->TempMin1, ui->TempMax1);
                        break;
                    case 2:
                        updateWeatherInfo(ui->day_txt2, ui->Weather_txt2,ui->Weather_icon2, ui->TempMin2, ui->TempMax2);
                        break;
                    case 3:
                        updateWeatherInfo(ui->day_txt3, ui->Weather_txt3,ui->Weather_icon2, ui->TempMin3, ui->TempMax3);
                        break;
                    case 4:
                        updateWeatherInfo(ui->day_txt4, ui->Weather_txt4,ui->Weather_icon4, ui->TempMin4, ui->TempMax4);
                        break;
                    case 5:
                        updateWeatherInfo(ui->day_txt5, ui->Weather_txt5,ui->Weather_icon5, ui->TempMin5, ui->TempMax5);
                        break;
                    case 6:
                        updateWeatherInfo(ui->day_txt6, ui->Weather_txt6,ui->Weather_icon6, ui->TempMin6, ui->TempMax6);
                        break;
                    case 7:
                        updateWeatherInfo(ui->day_txt7, ui->Weather_txt7,ui->Weather_icon7, ui->TempMin7, ui->TempMax7);
                        break;
                    default:
                        break;
                }
                i++;
            }
        }
    }
}


void Weather::onReply(QNetworkReply *replay)
{

    int status_code = replay->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(replay->error()!= QNetworkReply::NoError || status_code != 200)
    {
        qDebug() << replay->errorString().toLatin1().data();
        QMessageBox::warning(this,"天气","获取数据失败",QMessageBox::Ok);
    }
    else
    {
        QByteArray byteArray = replay->readAll();
        // qDebug() << byteArray.data();
        parse_json(byteArray);
    }
    replay->deleteLater();
}

void Weather::onTimerUpdata()
{
    getData(1);
}

