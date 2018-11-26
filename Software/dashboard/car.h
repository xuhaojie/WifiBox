#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QQuickItem>
#include <qmap.h>
#include "datasource.h"

class Car : public QObject
{
    Q_OBJECT
    Q_ENUMS(Alarm)
    Q_ENUMS(Door)
    Q_ENUMS(Lamp)
    Q_ENUMS(Line)
    Q_ENUMS(Relay)
    Q_ENUMS(GearMode)
    Q_ENUMS(GearProfile)
    Q_ENUMS(RadioBand)
    Q_ENUMS(AmplifierSource)

// 即时状态
    // 转速
    Q_PROPERTY(float rev READ getRev WRITE setRev NOTIFY revChanged)
    // 车速
    Q_PROPERTY(float speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    // 当前档位，如1、2、3、4
    Q_PROPERTY(int gear READ getGear WRITE setGear NOTIFY gearChanged)
    // 档位模式 N R M等
    Q_PROPERTY(int gearMode READ getGearMode WRITE setGearMode NOTIFY gearModeChanged)
    // 档位风格 雪地模式 运动模式等
    Q_PROPERTY(int gearProfile READ getGearProfile WRITE setGearProfile NOTIFY gearProfileChanged)
    // 当前油耗
    Q_PROPERTY(float oilWare READ getOilWare WRITE setOilWare NOTIFY oilWareChanged)
    // 续航距离
    Q_PROPERTY(int cruisingRange READ getCruisingRange WRITE setCruisingRange NOTIFY cruisingRangeChanged)

    // 定速巡航速度
    Q_PROPERTY(int cruisingSpeed READ getCruisingSpeed WRITE setCruisingSpeed NOTIFY cruisingSpeedChanged)
    // 定速巡航模式
    Q_PROPERTY(int cruisingMode READ getCruisingMode WRITE setCruisingMode NOTIFY cruisingModeChanged)


    // 油量
    Q_PROPERTY(float fuelLevel READ getFuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged)
    // 水温水温
    Q_PROPERTY(float waterTemperature READ getWaterTemperature WRITE setWaterTemperature NOTIFY waterTemperatureChanged)
    // 当前油温
    Q_PROPERTY(float oilTemperature READ getOilTemperature WRITE setOilTemperature NOTIFY oilTemperatureChanged)
    // 当前外部温度
    Q_PROPERTY(float outsideTemperature READ getOutsideTemperature WRITE setOutsideTemperature NOTIFY outsideTemperatureChanged)

    Q_PROPERTY(unsigned int alarmState READ getAlarmState WRITE setAlarmState NOTIFY alarmStateChanged)
    Q_PROPERTY(unsigned int lampState READ getLampState WRITE setLampState NOTIFY lampStateChanged)
    Q_PROPERTY(unsigned int doorState READ getDoorState WRITE setDoorState NOTIFY doorStateChanged)
    Q_PROPERTY(unsigned int buttonState READ getButtonState WRITE setButtonState NOTIFY buttonStateChanged)
    Q_PROPERTY(int rcWheelState READ getRcWheelState WRITE setRcWheelState NOTIFY rcWheelStateChanged)
    Q_PROPERTY(unsigned int lineState READ getLineState WRITE setLineState NOTIFY lineStateChanged)

    Q_PROPERTY(unsigned int doorAlarm READ getDoorAlarm WRITE setDoorAlarm NOTIFY doorAlarmChanged)

    Q_PROPERTY(float frontRadarDistanceA READ getFrontRadarDistanceA WRITE setFrontRadarDistanceA NOTIFY frontRadarDistanceAChanged)
    Q_PROPERTY(float frontRadarDistanceB READ getFrontRadarDistanceB WRITE setFrontRadarDistanceB NOTIFY frontRadarDistanceBChanged)
    Q_PROPERTY(float frontRadarDistanceC READ getFrontRadarDistanceC WRITE setFrontRadarDistanceC NOTIFY frontRadarDistanceCChanged)
    Q_PROPERTY(float frontRadarDistanceD READ getFrontRadarDistanceD WRITE setFrontRadarDistanceD NOTIFY frontRadarDistanceDChanged)

    Q_PROPERTY(float rearRadarDistanceA READ getRearRadarDistanceA WRITE setRearRadarDistanceA NOTIFY rearRadarDistanceAChanged)
    Q_PROPERTY(float rearRadarDistanceB READ getRearRadarDistanceB WRITE setRearRadarDistanceB NOTIFY rearRadarDistanceBChanged)
    Q_PROPERTY(float rearRadarDistanceC READ getRearRadarDistanceC WRITE setRearRadarDistanceC NOTIFY rearRadarDistanceCChanged)
    Q_PROPERTY(float rearRadarDistanceD READ getRearRadarDistanceD WRITE setRearRadarDistanceD NOTIFY rearRadarDistanceDChanged)

    // 方向
    Q_PROPERTY(float gpsDirction READ getGpsDirction WRITE setGpsDirction NOTIFY gpsDirctionChanged)
    // 速度
    Q_PROPERTY(float gpsSpeed READ getGpsSpeed WRITE setGpsSpeed NOTIFY gpsSpeedChanged)
    // 卫星数量
    Q_PROPERTY(float gpsSatellites READ getGpsSatellites WRITE setGpsSatellites NOTIFY gpsSatellitesChanged)
    // 经度
    Q_PROPERTY(float gpsLongitude READ getGpsLongitude WRITE setGpsLongitude NOTIFY gpsLongitudeChanged)
    // 纬度
    Q_PROPERTY(float gpsLatitude READ getGpsLatitude WRITE setGpsLatitude NOTIFY gpsLatitudeChanged)
    // GPS海拔数据
    Q_PROPERTY(float gpsAltitude READ getGpsAltitude WRITE setGpsAltitude NOTIFY gpsAltitudeChanged)

    // 收音机频率
    Q_PROPERTY(float radioFrequency READ getRadioFrequency WRITE setRadioFrequency NOTIFY radioFrequencyChanged)
    // 收音机波段
    Q_PROPERTY(int radioBand READ getRadioBand WRITE setRadioBand NOTIFY radioBandChanged)

    // 音响信号源
    Q_PROPERTY(int amplifierSource READ getAmplifierSource WRITE setAmplifierSource NOTIFY amplifierSourceChanged)
    // 音响音量
    Q_PROPERTY(int amplifierVolume READ getAmplifierVolume WRITE setAmplifierVolume NOTIFY amplifierVolumeChanged)
    // 电池电压
    Q_PROPERTY(float batteryVoltage READ getBatteryVoltage WRITE setBatteryVoltage NOTIFY batteryVoltageChanged)

    // 协议盒输入电压
    Q_PROPERTY(float powerVoltage READ getPowerVoltage WRITE setPowerVoltage NOTIFY powerVoltageChanged)

    // 输入电压
    Q_PROPERTY(float inputVoltageA READ getInputVoltageA WRITE setInputVoltageA NOTIFY inputVoltageAChanged)
    Q_PROPERTY(float inputVoltageB READ getInputVoltageB WRITE setInputVoltageB NOTIFY inputVoltageBChanged)
    Q_PROPERTY(float inputVoltageC READ getInputVoltageC WRITE setInputVoltageC NOTIFY inputVoltageCChanged)
    Q_PROPERTY(float inputVoltageD READ getInputVoltageD WRITE setInputVoltageD NOTIFY inputVoltageDChanged)

    // 继电器
    Q_PROPERTY(unsigned int relayState READ getRelayState WRITE setRelayState NOTIFY relayStateChanged)

    Q_PROPERTY(float chipVoltage READ getChipVoltage WRITE setChipVoltage NOTIFY chipVoltageChanged)
    Q_PROPERTY(float chipTemperature READ getChipTemperature WRITE setChipTemperature NOTIFY chipTemperatureChanged)


// 统计信息
    // 旅程距离？ 307有个精确到分米的当前行程距离
    Q_PROPERTY(float journeyDistance READ getJourneyDistance WRITE setJourneyDistance NOTIFY journeyDistanceChanged)

    // 旅程1信息
    Q_PROPERTY(float trip1Speed READ getTrip1Speed WRITE setTrip1Speed NOTIFY trip1SpeedChanged)
    Q_PROPERTY(float trip1OilWare READ getTrip1OilWare WRITE setTrip1OilWare NOTIFY trip1OilWareChanged)
    Q_PROPERTY(int trip1Mileage READ getTip1Mileage WRITE setTrip1Mileage NOTIFY trip1MileageChanged)
    // 旅程2信息
    Q_PROPERTY(float trip2Speed READ getTrip2Speed WRITE setTrip2Speed NOTIFY trip2SpeedChanged)
    Q_PROPERTY(float trip2OilWare READ getTrip2OilWare WRITE setTrip2OilWare NOTIFY trip2OilWareChanged)
    Q_PROPERTY(int trip2Mileage READ getTrip2Mileage WRITE setTrip2Mileage NOTIFY trip2MileageChanged)

    // 总里程
    Q_PROPERTY(unsigned int totalMileage READ getTotalMileage WRITE setTotalMileage NOTIFY totalMileageChanged)


// 车辆固有信息
    Q_PROPERTY(QString vin READ getVin WRITE setVin NOTIFY vinChanged)




public:
    explicit Car(QObject *parent = 0);
    ~Car();

    enum Alarm
    {
        Alarm_ABS       = 0x0001,
        Alarm_AirBag    = 0x0002,
        Alarm_AirBag2   = 0x0004,
        Alarm_Brake     = 0x0008,

        Alarm_Battery   = 0x0010,
        Alarm_Caution   = 0x0020,
        Alarm_Door      = 0x0040,
        Alarm_Engine    = 0x0080,

        Alarm_ESP       = 0x0100,
        Alarm_LowFuel   = 0x0200,
        Alarm_MotorOil  = 0x0400,
        Alarm_SeatBelt  = 0x0800,

        Alarm_Stop      = 0x1000,
        Alarm_Warning   = 0x2000
    };

    enum Lamp{
        Lamp_HighBeam       = 0x01,
        Lamp_DippedBeam     = 0x02,
        Lamp_FrontFog       = 0x04,
        Lamp_RearFog        = 0x08,
        Lamp_Left           = 0x10,
        Lamp_Right          = 0x20,
        Lamp_Reversing      = 0x40,
        Lamp_DashBoard      = 0x80

    };

    enum Door{
        Door_FrontLeft      = 0x01,
        Door_FrontRight     = 0x02,
        Door_RearLeft       = 0x04,
        Door_RearRight      = 0x08,
        Door_Boot           = 0x10,
        Door_Hood           = 0x20

    };

    enum Button{
        Button_Audio_Source             = 0x01,
        Button_Audio_VolumeDown         = 0x02,
        Button_Audio_VolumeUp           = 0x04,
        Button_Audio_Mute               = 0x06,
        Button_Audio_Prev               = 0x10,
        Button_Audio_Next               = 0x20,
    };

    enum Line{
        Line_Acc            = 0x01,
        Line_Reverse        = 0x02
    };

    enum GearMode{
        GearMode_M          = 0,
        GearMode_N          = 1,
        GearMode_P          = 2,
        GearMode_D          = 3,
        GearMode_R          = 4,
    };

    enum GearProfile{
        GearProfile_Normal     = 0,
        GearProfile_Snow       = 1,
        GearProfile_Sport      = 2,
    };


    enum RadioBand{
        Band_None   = 0,
        Band_AM     = 1,
        Band_FM     = 2
    };

    enum AmplifierSource{
        Source_None     = 0,
        Source_CD       = 1,
        Source_Radio    = 2,
        Source_CDC      = 3,
        Source_Blutooth = 4,
        Source_USB      = 5,
        Source_AUX      = 6,
        Source_AUX2     = 7,
    };

    enum Relay{
        Relay_A         = 0x01,
        Relay_B         = 0x02,
        Relay_C         = 0x04,
        Relay_D         = 0x08,
        Relay_E         = 0x10,
        Relay_F         = 0x20,
        Relay_G         = 0x40,
        Relay_H         = 0x80,
    };

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void sendCommand(const QString& command);

    float getRev() const;
    void setRev(float value);

    float getSpeed() const;
    void setSpeed(float value);

    // 当前档位，如1、2、3、4
    int getGear() const;
    void setGear(int value);

    // 档位模式 N R M等
    int getGearMode() const;
    void setGearMode(int value);

    // 档位风格 雪地模式 运动模式等
    int getGearProfile() const;
    void setGearProfile(int value);

    // 当前油耗
    float getOilWare() const;
    void setOilWare(float value);

    // 续航距离
    int getCruisingRange() const;
    void setCruisingRange(int value);


    // 定速巡航速度
    int getCruisingSpeed() const;
    int setCruisingSpeed(int value);

    // 定速巡航模式
    int getCruisingMode() const;
    void setCruisingMode(unsigned int value);

    // 油量
    float getFuelLevel() const;
    void setFuelLevel(float value);

    // 水温
    float getWaterTemperature() const;
    void setWaterTemperature(float value);

    // 当前油温
    float getOilTemperature() const;
    void setOilTemperature(float value);

    float getOutsideTemperature() const;
    void setOutsideTemperature(float value);

    unsigned int getAlarmState() const;
    void setAlarmState(unsigned int value);

    unsigned int getLampState() const;
    void setLampState(unsigned int value);

    unsigned int getDoorState() const;
    void setDoorState(unsigned int value);

    unsigned int getButtonState() const;
    void setButtonState(unsigned int value);

    int getRcWheelState() const;
    void setRcWheelState(int value);

    unsigned int getLineState() const;
    void setLineState(unsigned int value);

    unsigned int getDoorAlarm() const;
    void setDoorAlarm(unsigned int value);

    float getFrontRadarDistanceA() const;
    void setFrontRadarDistanceA(float value);
    float getFrontRadarDistanceB() const;
    void setFrontRadarDistanceB(float value);
    float getFrontRadarDistanceC() const;
    void setFrontRadarDistanceC(float value);
    float getFrontRadarDistanceD() const;
    void setFrontRadarDistanceD(float value);

    float getRearRadarDistanceA() const;
    void setRearRadarDistanceA(float value);
    float getRearRadarDistanceB() const;
    void setRearRadarDistanceB(float value);
    float getRearRadarDistanceC() const;
    void setRearRadarDistanceC(float value);
    float getRearRadarDistanceD() const;
    void setRearRadarDistanceD(float value);

    float getGpsDirction() const;
    void setGpsDirction(float value);
    float getGpsSpeed() const;
    void setGpsSpeed(float value);
    int getGpsSatellites() const;
    void setGpsSatellites(int value);
    float getGpsLongitude() const;
    void setGpsLongitude(float value);
    float getGpsLatitude() const;
    void setGpsLatitude(float value);
    float getGpsAltitude() const;
    void setGpsAltitude(float value);

    // 收音机频率
    float getRadioFrequency() const;
    void setRadioFrequency(float value);
    // 收音机波段
    int getRadioBand() const;
    void setRadioBand(int value);

    // 音响信号源
    int getAmplifierSource() const;
    void setAmplifierSource(int value);
    // 音响音量
    int getAmplifierVolume() const;
    void setAmplifierVolume(int value);

    // 电池电压
    float getBatteryVoltage() const;
    void setBatteryVoltage(float value);

    // 协议盒输入电压
    float getPowerVoltage() const;
    void setPowerVoltage(float value);

    // 输入电压
    float getInputVoltageA() const;
    void setInputVoltageA(float value);
    float getInputVoltageB() const;
    void setInputVoltageB(float value);
    float getInputVoltageC() const;
    void setInputVoltageC(float value);
    float getInputVoltageD() const;
    void setInputVoltageD(float value);

    // 继电器
    unsigned int getRelayState() const;
    void setRelayState(unsigned int value);

    float getChipVoltage() const;
    void setChipVoltage(float value);

    float getChipTemperature() const;
    void setChipTemperature(float value);

    float getJourneyDistance() const;
    void setJourneyDistance(float value);

    float getTrip1Speed() const;
    void setTrip1Speed(float value);

    float getTrip1OilWare() const;
    void setTrip1OilWare(float value);

    unsigned int getTip1Mileage() const;
    void setTrip1Mileage(unsigned int value);


    float getTrip2Speed() const;
    void setTrip2Speed(float value);

    float getTrip2OilWare() const;
    void setTrip2OilWare(float value);

    unsigned int getTrip2Mileage() const;
    void setTrip2Mileage(unsigned int value);

    unsigned int getTotalMileage() const;
    void setTotalMileage(unsigned int value);

    QString getVin() const;
    void setVin(const QString& vin);

signals:
    void revChanged(float value);
    void speedChanged(float value);
    void gearChanged(int value);
    void gearModeChanged(int value);
    void gearProfileChanged(int value);
    void fuelLevelChanged(float value);
    void oilWareChanged(float value);
    void cruisingRangeChanged(int value);
    void cruisingSpeedChanged(int value);
    void cruisingModeChanged(int value);

    void oilTemperatureChanged(float value);
    void waterTemperatureChanged(float value);
    void outsideTemperatureChanged(float value);

    void alarmStateChanged(unsigned int value);
    void lampStateChanged(unsigned int value);
    void doorStateChanged(unsigned int value);
    void buttonStateChanged(unsigned int value);
    void rcWheelStateChanged(int value);
    void lineStateChanged(unsigned int value);
    void doorAlarmChanged(unsigned int value);


    void frontRadarDistanceAChanged(float value);
    void frontRadarDistanceBChanged(float value);
    void frontRadarDistanceCChanged(float value);
    void frontRadarDistanceDChanged(float value);

    void rearRadarDistanceAChanged(float value);
    void rearRadarDistanceBChanged(float value);
    void rearRadarDistanceCChanged(float value);
    void rearRadarDistanceDChanged(float value);

    void gpsDirctionChanged(float value);
    void gpsSpeedChanged(float value);
    void gpsSatellitesChanged(unsigned int value);
    void gpsLongitudeChanged(float value);
    void gpsLatitudeChanged(float value);
    void gpsAltitudeChanged(float value);

    void radioFrequencyChanged(float value);
    void radioBandChanged(int value);

    void amplifierSourceChanged(int value);
    void amplifierVolumeChanged(int value);

    void batteryVoltageChanged(float value);

    void powerVoltageChanged(float value);

    void inputVoltageAChanged(float value);
    void inputVoltageBChanged(float value);
    void inputVoltageCChanged(float value);
    void inputVoltageDChanged(float value);

    void relayStateChanged(unsigned int value);
    void chipVoltageChanged(float value);
    void chipTemperatureChanged(float value);

    void journeyDistanceChanged(float value);

    void trip1SpeedChanged(float value);
    void trip1OilWareChanged(float value);
    void trip1MileageChanged(unsigned int value);

    void trip2SpeedChanged(float value);
    void trip2OilWareChanged(float value);
    void trip2MileageChanged(unsigned int value);

    void totalMileageChanged(unsigned int value);



    void vinChanged(const QString& vin);


protected slots:

    void onDataChanged(const QString& key, const QString& value);


protected:
//    void timerEvent(QTimerEvent *e);

    void speedDecoder(const QString& key, const QString& value);
    void revDecoder(const QString& key, const QString& value);
    void gearDecoder(const QString& key, const QString& value);
    void gearModeDecoder(const QString& key, const QString& value);
    void gearProfileDecoder(const QString& key, const QString& value);
    void oilWareDecoder(const QString& key, const QString& value);

    void cruisingRangeDecoder(const QString& key, const QString& value);
    void cruisingSpeedDecoder(const QString& key, const QString& value);
    void cruisingModeDecoder(const QString& key, const QString& value);

    void fuelLevelDecoder(const QString& key, const QString& value);
    void waterTemperatureDecoder(const QString& key, const QString& value);
    void oilTemperatureDecoder(const QString& key, const QString& value);
    void outsideTemperatureDecoder(const QString& key, const QString& value);

    void alarmStateDecoder(const QString& key, const QString& value);
    void lampStateDecoder(const QString& key, const QString& value);
    void doorStateDecoder(const QString& key, const QString& value);
    void buttonStateDecoder(const QString& key, const QString& value);
    void buttonWheelDecoder(const QString& key, const QString& value);
    void lineStateDecoder(const QString& key, const QString& value);

    void doorAlarmDecoder(const QString& key, const QString& value);



    void frontRadarDistanceADecoder(const QString& key, const QString& value);
    void frontRadarDistanceBDecoder(const QString& key, const QString& value);
    void frontRadarDistanceCDecoder(const QString& key, const QString& value);
    void frontRadarDistanceDDecoder(const QString& key, const QString& value);

    void rearRadarDistanceADecoder(const QString& key, const QString& value);
    void rearRadarDistanceBDecoder(const QString& key, const QString& value);
    void rearRadarDistanceCDecoder(const QString& key, const QString& value);
    void rearRadarDistanceDDecoder(const QString& key, const QString& value);

    void gpsDirctionDecoder(const QString& key, const QString& value);
    void gpsSpeedDecoder(const QString& key, const QString& value);
    void gpsSatellitesDecoder(const QString& key, const QString& value);
    void gpsLongitudeDecoder(const QString& key, const QString& value);
    void gpsLatitudeDecoder(const QString& key, const QString& value);
    void gpsAltitudeDecoder(const QString& key, const QString& value);


    void radioFrequencyDecoder(const QString& key, const QString& value);
    void radioBandDecoder(const QString& key, const QString& value);
    void amplifierSourceDecoder(const QString& key, const QString& value);
    void amplifierVolumeDecoder(const QString& key, const QString& value);

    void batteryVoltageDecoder(const QString& key, const QString& value);
    void powerVoltageDecoder(const QString& key, const QString& value);
    void inputVoltageADecoder(const QString& key, const QString& value);
    void inputVoltageBDecoder(const QString& key, const QString& value);
    void inputVoltageCDecoder(const QString& key, const QString& value);
    void inputVoltageDDecoder(const QString& key, const QString& value);

    void relayStateDecoder(const QString& key, const QString& value);

    void chipVoltageDecoder(const QString& key, const QString& value);
    void chipTemperatureDecoder(const QString& key, const QString& value);



    void journeyDistanceDecoder(const QString& key, const QString& value);

    void trip1SpeedDecoder(const QString& key, const QString& value);
    void trip1OilWareDecoder(const QString& key, const QString& value);
    void trip1MileageDecoder(const QString& key, const QString& value);

    void trip2SpeedDecoder(const QString& key, const QString& value);
    void trip2OilWareDecoder(const QString& key, const QString& value);
    void trip2MileageDecoder(const QString& key, const QString& value);

    void totalMileageDecoder(const QString& key, const QString& value);

    void vinDecoder(const QString& key, const QString& value);


private:

// 即时信息
    // 转速
    float m_rev;
    // 车速
    float m_speed;
    // 当前档位，如1、2、3、4
    int m_gear;
    // 档位模式 N R M等
    int m_gearMode;
    // 档位风格 雪地模式 运动模式等
    int m_gearProfile;
    // 当前油耗
    float m_oilWare;
    int m_cruisingRange;
    int m_cruisingSpeed;
    int m_cruisingMode;

    // 油量
    float m_fuelLevel;
    // 水温
    float m_waterTemperature;
    // 当前油温
    float m_oilTemperature;
    float m_outsideTemperature;

    unsigned int m_lampState;
    unsigned int m_alarmState;
    unsigned int m_doorState;
    unsigned int m_buttonState;
    unsigned int m_lineState;

    int m_rcWheelState;

    unsigned int m_doorAlarm;

    float m_frontRadarDistanceA;
    float m_frontRadarDistanceB;
    float m_frontRadarDistanceC;
    float m_frontRadarDistanceD;

    float m_rearRadarDistanceA;
    float m_rearRadarDistanceB;
    float m_rearRadarDistanceC;
    float m_rearRadarDistanceD;

    // 方向
    float m_gpsDirction;
    // 速度
    float m_gpsSpeed;
    // 卫星数量
    float m_gpsSatellites;
    // 经度
    float m_gpsLongitude;
    // 纬度
    float m_gpsLatitude;
    // GPS海拔数据
    float m_gpsAltitude;


    // 收音机频率
    float m_radioFrequency;
    // 收音机波段
    int m_radioBand;
    // 音响信号源
    int m_amplifierSource;
    // 音响音量
    int m_amplifierVolume;

    // 电池电压
    float m_batteryVoltage;

    // 协议盒输入电压
    float m_powerVoltage;

    // 输入电压
    float m_inputVoltageA;
    float m_inputVoltageB;
    float m_inputVoltageC;
    float m_inputVoltageD;


    unsigned int m_relayState;
    float m_chipVoltage;
    float m_chipTemperature;

// 统计信息
    // 旅程距离？
    float m_journeyDistance;

    // 旅程1信息
    float m_trip1Speed;
    float m_trip1OilWare;
    float m_trip1Mileage;

    // 旅程2信息
    float m_trip2Speed;
    float m_trip2OilWare;
    float m_trip2Mileage;

    // 总里程
    unsigned int m_totalMileage;




    QString m_vin;

    DataSource m_dataSource;

    typedef void (Car::*DataDecoder)(const QString& key, const QString& value);

    typedef QMap<QString,DataDecoder> DecoderMap;
    DecoderMap m_decoderMap; //定义一个QMap对象

};

#endif // CAR_H
