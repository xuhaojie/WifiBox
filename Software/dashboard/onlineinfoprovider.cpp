#include "onlineinfoprovider.h"
#include<QVariant>
#include<QByteArray>
#include<QJsonParseError>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonValue>
#include<QXmlStreamReader>
#include <QTextCodec>
OnlineInfoProvider::OnlineInfoProvider(QObject *parent)
    : QObject(parent)
{
    qInfo("OnlineInfoProvider::OnlineInfoProvider().\n");
    qDebug() << "before";
    manager = new QNetworkAccessManager(this);
    qDebug() << "after";
    if(0 == manager)
    {

        qFatal("Create QNetworkAccessManager failed!\n");

    }
    else
    {
        qInfo("QNetworkAccessManager created.\n");
    }

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));

    //启动程序后先查询ip定位默认城市
    choose = 0;
}

OnlineInfoProvider::~OnlineInfoProvider()
{

}

void OnlineInfoProvider::fetchWeather(const QString& city)
{
    QString address = "http://wthrcdn.etouch.cn/weather_mini?city=" + city;

    //request.setHeader(QNetworkRequest::ContentTypeHeader,"text/html;charset=utf-8");
    choose = 1;
    //QString url = URL_1 + m_city;
    if(manager)
    {
        manager->get(QNetworkRequest(QUrl(address)));
    }

}

QString OnlineInfoProvider::getCity()
{
    return m_city;
}

void OnlineInfoProvider::setCity(const QString &value)
{
    m_city = value;
    emit cityChanged(value);
}

QString OnlineInfoProvider::getWeather()
{
    return m_weather;
}

void OnlineInfoProvider::setWeather(const QString &value)
{
    m_weather = value;
    emit weatherChanged(value);
}

float OnlineInfoProvider::getTemperature()
{
    return m_temperature;
}

void OnlineInfoProvider::setTemperature(const float value)
{
    m_temperature = value;
    emit temperatureChanged(value);
}

float OnlineInfoProvider::getLowestTemperature()
{
    return m_lowestTemperature;
}

void OnlineInfoProvider::setLowestTemperature(const float value)
{
    m_lowestTemperature = value;
    emit lowestTemperatureChanged(value);
}

float OnlineInfoProvider::getHighestTemperature()
{
    return m_highestTemperature;
}

void OnlineInfoProvider::setHighestTemperature(const float value)
{
    m_highestTemperature = value;
    emit highestTemperatureChanged(value);
}

int OnlineInfoProvider::getHumidity()
{
    return m_humidity;
}

void OnlineInfoProvider::setHumidity(const int value)
{
    m_humidity = value;
    emit humidityChanged(value);
}

float OnlineInfoProvider::getWindForce()
{
    return m_windForce;
}

void OnlineInfoProvider::setWindForce(const float value)
{
    m_windForce = value;
    emit windForceChanged(value);
}
#include <QTextCodec>

inline QString GBK2UTF8(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

    QString g2u = gbk->toUnicode(gbk->fromUnicode(inStr));              // gbk  convert utf8
    return g2u;
}

inline QString UTF82GBK(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

    QString utf2gbk = gbk->toUnicode(inStr.toLocal8Bit());
    return utf2gbk;
}

inline std::string gbk2utf8(const QString &inStr)
{
    return GBK2UTF8(inStr).toStdString();
}

inline QString utf82gbk(const std::string &inStr)
{
    QString str = QString::fromStdString(inStr);

    return UTF82GBK(str);
}


void OnlineInfoProvider::replyFinished(QNetworkReply *reply)
{
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        if(choose ==0)
        {
            QJsonParseError json_error;
            QJsonDocument parse_doucment = QJsonDocument::fromJson(bytes,&json_error);

            if(json_error.error == QJsonParseError::NoError)
            {
                QJsonObject obj = parse_doucment.object();

                QJsonValue city = obj.take("city");
                setCity(city.toString());
            }
        }
        //QString result(bytes);
        //qDebug()<<result;
        else if(choose == 1)//今天天气+指数
        {
            QJsonParseError json_error;
            QJsonDocument parse_doucment = QJsonDocument::fromJson(bytes,&json_error);
            if(json_error.error == QJsonParseError::NoError)
            {
                QJsonObject obj = parse_doucment.object();

                QJsonValue city = obj.take("city");
                QJsonObject data = obj.take("data").toObject();


                QJsonValue value = data.take("wendu");
                float tmp = value.toString().toDouble();
                setTemperature(tmp);

                QJsonArray arry = data.take("forecast").toArray();
                for(int t=0;t<1;t++)
                {
                    QJsonObject fore = arry[t].toObject();
                    value = fore.take("type");
                    setWeather(value.toString());
                    value = fore.take("type");

                }

                //setCity(city.toString());
            }
        }
        else if(choose == 2)//未来5天天气
        {
            QString result(bytes);
            //qDebug()<<result;
            parseJson(result);
        }
    } else {
        //QMessageBox::information(this,tr("出错啦"),tr("网络错误,请检查网络连接"),QMessageBox::Ok,QMessageBox::Ok);
        //qDebug()<<"网络出错\n";
    }
    reply->deleteLater();
}


//解析json格式的未来天气
void OnlineInfoProvider::parseJson(QString Json)
{
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(Json),&json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        QJsonObject obj = parse_doucment.object();

        QJsonValue desc = obj.take("desc");
        if(desc.toString() != "OK")
        {
            //qDebug()<<"城市错误\n";
            //QMessageBox::information(this,tr("抱歉"),tr("暂无此城市的天气情况"),QMessageBox::Ok,QMessageBox::Ok);
            return;
        }

        QJsonValue data = obj.take("data");
        today.ganmao = data.toObject().take("ganmao").toString();
        QJsonValue forecast1 = data.toObject().take("forecast");
        QJsonArray forecast2 = forecast1.toArray();
        for(int i=0; i<5; i++)
        {
            QJsonValue value = forecast2.at(i);
            QJsonObject object = value.toObject();
            forecast[i].fengxiang = object.take("fengxiang").toString();
            forecast[i].date = object.take("date").toString();
            forecast[i].fengli = object.take("fengli").toString();
            forecast[i].high = object.take("high").toString();
            forecast[i].low = object.take("low").toString();
            forecast[i].type = object.take("type").toString();
        }

        for(int i=0;i<5;i++)
        {
/*
            forecast_date_list[i]->setText(tr("%1").arg(forecast[i].date));
            forecast_temp_list[i]->setText(tr("%1 - %2").arg(forecast[i].low.split(" ").at(1)).arg(forecast[i].high.split(" ").at(1)));
            forecast_type_list[i]->setPixmap(QPixmap(tr(":/images/%1").arg(forecast[i].type)));
            forecast_type_list[i]->setToolTip(tr("%1 : %2 - %3").arg(forecast[i].type).arg(forecast[i].fengli).arg(forecast[i].fengxiang));
*/
        }
/*
        QString url = URL_2 + city;
        choose = 1;
        manager->get(QNetworkRequest(QUrl(url)));
*/

    }
    else
    {
        //qDebug()<<"Json错误";
        //QMessageBox::information(this,tr("出错啦"),tr("数据出错,请重试"),QMessageBox::Ok,QMessageBox::Ok);
        return;
    }
}

//解析XML格式的今天天气
void OnlineInfoProvider::parseXml(QString Xml)
{
    QXmlStreamReader xml(Xml);

    while(!xml.atEnd())
    {
        if(xml.hasError())
        {
            //QMessageBox::information(this,tr("出错啦"),tr("数据出错,请重试"),QMessageBox::Ok,QMessageBox::Ok);
            return;
        }
        else if(xml.isStartElement())
        {
            if(xml.name()=="city")
            {
                today.city = xml.readElementText();
            }
            else if(xml.name()=="updatetime")
            {
                today.updatetime = xml.readElementText();
            }
            else if(xml.name()=="wendu")
            {
                today.wendu = xml.readElementText();
            }
            else if(xml.name()=="fengli")
            {
                today.fengli = xml.readElementText();
            }
            else if(xml.name()=="shidu")
            {
                today.shidu = xml.readElementText();
            }
            else if(xml.name()=="fengxiang")
            {
                today.fengxiang = xml.readElementText();
            }
            else if(xml.name()=="sunrise_1")
            {
                today.sunrise = xml.readElementText();
            }
            else if(xml.name()=="sunset_1")
            {
                today.sunset = xml.readElementText();
                xml.clear();
/*
                ui->city->setText(tr("%1").arg(today.city));
                ui->temp->setText(tr("%1℃").arg(today.wendu));
                ui->sunrise->setText(tr("%1").arg(today.sunrise));
                ui->sunset->setText(tr("%1").arg(today.sunset));
                ui->label->setText(tr("日出"));
                ui->label_2->setText(tr("日落"));
                ui->label_3->setText(tr("湿度"));
                ui->shidu->setText(tr("%1").arg(today.shidu));
                ui->fengli->setText(tr("%1").arg(today.fengli));
                ui->fengxiang->setText(tr("%1").arg(today.fengxiang));
                ui->label_4->setText(tr("感\n冒\n指\n数"));
                ui->ganmao->setText(tr("%1").arg(today.ganmao));
*/

                return;
            }
            else
                xml.readNext();
        }
        else
            xml.readNext();
    }
    xml.clear();

}
void OnlineInfoProvider::fetchCity()
{
    qInfo("Enter OnlineInfoProvider::fetchCity.\n");
    QNetworkRequest request(QUrl("http://int.dpool.sina.com.cn/iplookup/iplookup.php?format=json"));
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("text/html;charset=utf-8"));
    choose=0;
    if(manager)
    {
        manager->get(request);
    }
    else
    {
        qCritical("manager = NULL !!!!\n");
    }
    qInfo("Leave OnlineInfoProvider::fetchCity.\n");
}


