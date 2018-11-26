#ifndef ONLINEINFOPROVIDER_H
#define ONLINEINFOPROVIDER_H
#include <QObject>
#include <QQuickItem>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
struct Forecast
{
    QString fengxiang;
    QString fengli;
    QString high;
    QString type;
    QString low;
    QString date;
};

struct Today
{
    QString ganmao;
    QString city;
    QString updatetime;
    QString wendu;
    QString fengli;
    QString fengxiang;
    QString sunrise;
    QString sunset;
    QString shidu;
};
class OnlineInfoProvider : public QObject
{
        Q_OBJECT
        // 城市
        Q_PROPERTY(QString city READ getCity WRITE setCity NOTIFY cityChanged)
        // 天气
        Q_PROPERTY(QString weather READ getWeather WRITE setWeather NOTIFY weatherChanged)
        // 温度
        Q_PROPERTY(float temperature READ getTemperature WRITE setTemperature NOTIFY temperatureChanged)
        // 最低温
        Q_PROPERTY(float lowestTemperature READ getLowestTemperature WRITE setLowestTemperature NOTIFY lowestTemperatureChanged)
        // 最高温
        Q_PROPERTY(float highestTemperature READ getHighestTemperature WRITE setHighestTemperature NOTIFY highestTemperatureChanged)
        // 湿度
        Q_PROPERTY(int humidity READ getHumidity WRITE setHumidity NOTIFY humidityChanged)
        // 风力
        Q_PROPERTY(int windForce READ getWindForce WRITE setWindForce NOTIFY windForceChanged)


public:
    public:
        explicit OnlineInfoProvider(QObject *parent = 0);
        ~OnlineInfoProvider();
        Q_INVOKABLE void fetchCity();
        Q_INVOKABLE void fetchWeather(const QString& city);
public:

    QString getCity(void);
    void setCity(const QString& value);

    QString getWeather(void);
    void setWeather(const QString& value);

    float getTemperature(void);
    void setTemperature(const float value);

    float getLowestTemperature(void);
    void setLowestTemperature(const float value);

    float getHighestTemperature(void);
    void setHighestTemperature(const float value);

    int getHumidity(void);
    void setHumidity(const int value);

    float getWindForce(void);
    void setWindForce(const float value);



signals:
    void weatherChanged(const QString& value);
    void cityChanged(const QString& value);
    void temperatureChanged(float value);
    void lowestTemperatureChanged(float value);
    void highestTemperatureChanged(float value);
    void humidityChanged(int value);
    void windForceChanged(int value);

protected slots:
    void replyFinished(QNetworkReply *reply);

protected:
    QString m_city;
    QString m_weather;
    float m_temperature;
    float m_lowestTemperature;
    float m_highestTemperature;
    int m_humidity;
    int m_windForce;



    QNetworkAccessManager *manager;
    QString URL_1;
    QString URL_2;

    Forecast forecast[5];
    Today today;

    void parseJson(QString Json);
    void parseXml(QString Xml);
    void parseCity(QString City);

    int choose;//0.查询IP 1.今天天气+指数 2.未来5天天气

    //QPixmap pixmap;
};

#endif // ONLINEINFOPROVIDER_H
