#include "weatherdata.h"


WeatherData::WeatherData()
{
    //创建网络访问管理器
    myNetAccessManager = new QNetworkAccessManager();
    connect(myNetAccessManager,&QNetworkAccessManager::finished,this, &WeatherData::onReply);
}

bool WeatherData::getWeatherData()
{
    updataFlag = false;
    upData(1);

    QEventLoop loop;

    connect(this, &WeatherData::weatherDataUpdated, &loop, &QEventLoop::quit);

    loop.exec();

    disconnect(this, &WeatherData::weatherDataUpdated, &loop, &QEventLoop::quit);

    return true;
}

void WeatherData::upData(int type)
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
            url = QUrl("https://geoapi.qweather.com/v2/city/lookup?key=0f7271f1c38e42b7b7b5a0951e4dd6f9&location=" + info.cityName);
            break;
        case 3:
            //和风天气获取当天天气信息
            url = QUrl("https://devapi.qweather.com/v7/weather/now?key=0f7271f1c38e42b7b7b5a0951e4dd6f9&location=" + info.citycode);
            break;
        case 4:
            //和风天气获取未来7天信息
            url = QUrl("https://devapi.qweather.com/v7/weather/7d?key=0f7271f1c38e42b7b7b5a0951e4dd6f9&location=" + info.citycode);
            break;
        default:
            break;
    }
    myNetAccessManager->get(QNetworkRequest(url));
}

void WeatherData::parse_json(QByteArray &byteArray)
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
        info.cityName = rootObj["city"].toString();
        upData(2);
    }
    else if(rootObj.contains("location"))
    {
        QJsonArray locationArray = rootObj["location"].toArray();   //获取location列表
        QJsonObject firstObject = locationArray.at(0).toObject();   //获取第一个元素
        if (firstObject.contains("id"))
        {
            info.citycode = firstObject["id"].toString();
            upData(3);
        }
    }
    else if(rootObj.contains("now"))
    {
        QJsonObject now = rootObj["now"].toObject();
        info.temp = now["temp"].toString();
        info.weather_txt = now["text"].toString();
        info.weather_icon = now["icon"].toString();
        info.windDir = now["windDir"].toString();
        info.feelsLike = now["feelsLike"].toString();
        info.windScale = now["windScale"].toString();
        info.humidity = now["humidity"].toString();
        info.pressure = now["pressure"].toString();
        upData(4);
    }
    else if(rootObj.contains("daily"))
    {
        QJsonArray dailyArray = rootObj["daily"].toArray();
        int i = 0;
        for (const QJsonValue &dailyValue : dailyArray)
        {
            if (dailyValue.isObject())
            {
                QJsonObject dailyObj = dailyValue.toObject();
                info.day[i].fxDate = dailyObj["fxDate"].toString();
                info.day[i].textDay = dailyObj["textDay"].toString();
                info.day[i].iconDay = dailyObj["iconDay"].toString();
                info.day[i].tempMax = dailyObj["tempMax"].toString();
                info.day[i].tempMin = dailyObj["tempMin"].toString();
                i++;
            }
        }
        updataFlag = true;
        emit weatherDataUpdated();
    }
}

void WeatherData::onReply(QNetworkReply *replay)
{
    int status_code = replay->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(replay->error()!= QNetworkReply::NoError || status_code != 200)
    {
        qDebug() << replay->errorString().toLatin1().data();
        // QMessageBox::warning(this,"天气","获取数据失败",QMessageBox::Ok);
    }
    else
    {
        QByteArray byteArray = replay->readAll();
        parse_json(byteArray);
    }
    replay->deleteLater();
}
