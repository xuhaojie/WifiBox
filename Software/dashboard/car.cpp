#include <QTimerEvent>
#include <QDateTime>
#include <unistd.h>
#include "car.h"
#include "statename.h"

typedef struct {
    const char* Key;
    unsigned int Mask;
}KeyMaskMapItem;

int SetState(const KeyMaskMapItem* map, unsigned int& data,const QString &key, const QString &value)
{
    if(0 == map)
    {
        return -1;
    }
    const KeyMaskMapItem* p = map;
    unsigned newData = data;
    while(p->Key)
    {
        if(key == p->Key)
        {
            int val = value.toInt();
            if(val)
            {
                newData |= p->Mask;
            }
            else
            {
                newData &= ~(p->Mask);
            }
            if(newData != data)
            {
                data = newData;
                return 1;
            }
            else{
                return 0;
            }
        }
        ++p;
    }
    return -1;
}

Car::Car(QObject *parent)
    : QObject(parent),
    m_rev(0),
    m_speed(0),
    m_gear(0),
    m_gearMode(0),
    m_gearProfile(0),
    m_oilWare(0),
    m_cruisingRange(0),
    m_cruisingSpeed(0),
    m_cruisingMode(0),
    m_fuelLevel(0),
    m_waterTemperature(0),
    m_oilTemperature(0),
    m_outsideTemperature(0),
    m_lampState(0),
    m_alarmState(0),
    m_doorState(0),
    m_buttonState(0),
    m_rcWheelState(0),
    m_lineState(0),
    m_doorAlarm(0),
    m_frontRadarDistanceA(0),
    m_frontRadarDistanceB(0),
    m_frontRadarDistanceC(0),
    m_frontRadarDistanceD(0),
    m_rearRadarDistanceA(0),
    m_rearRadarDistanceB(0),
    m_rearRadarDistanceC(0),
    m_rearRadarDistanceD(0),
    m_gpsDirction(0),
    m_gpsSpeed(0),
    m_gpsSatellites(0),
    m_gpsLongitude(0),
    m_gpsLatitude(0),
    m_gpsAltitude(0),
    m_radioFrequency(0),
    m_radioBand(0),
    m_amplifierSource(0),
    m_amplifierVolume(0),
    m_batteryVoltage(12.6),
    m_powerVoltage(0),
    m_inputVoltageA(0),
    m_inputVoltageB(0),
    m_inputVoltageC(0),
    m_inputVoltageD(0),
    m_relayState(0),
    m_chipVoltage(0),
    m_chipTemperature(0),
    m_journeyDistance(0),
    m_trip1Speed(0),
    m_trip1OilWare(0),
    m_trip1Mileage(0),
    m_trip2Speed(0),
    m_trip2OilWare(0),
    m_trip2Mileage(0),
    m_totalMileage(0)
{
    // 基本信息

    m_decoderMap.insert(STATE_Car_Speed, &Car::speedDecoder);
    m_decoderMap.insert(STATE_Car_Rev, &Car::revDecoder);
    m_decoderMap.insert(STATE_Car_Gear, &Car::gearDecoder);
    m_decoderMap.insert(STATE_Car_GearMode, &Car::gearModeDecoder);
    m_decoderMap.insert(STATE_Car_GearProfile, &Car::gearProfileDecoder);
    m_decoderMap.insert(STATE_Car_OilWare, &Car::oilWareDecoder);

    m_decoderMap.insert(STATE_Car_CruisingRange, &Car::cruisingRangeDecoder);

    m_decoderMap.insert(STATE_Car_CruisingSpeed, &Car::cruisingSpeedDecoder);
    m_decoderMap.insert(STATE_Car_CruisingMode, &Car::cruisingModeDecoder);

// 适配协议盒错误
//    m_decoderMap.insert(STATE_Car_FuelLevel, &Car::fuelLevelDecoder);
    m_decoderMap.insert(STATE_Car_FeulLevel, &Car::fuelLevelDecoder);
    m_decoderMap.insert(STATE_Car_WaterTemp, &Car::waterTemperatureDecoder);
    m_decoderMap.insert(STATE_Car_OilTemp, &Car::oilTemperatureDecoder);
    m_decoderMap.insert(STATE_Car_OutsideTemp, &Car::outsideTemperatureDecoder);

    // 告警信息
    m_decoderMap.insert(STATE_Alarm_ABS, &Car::alarmStateDecoder);

    m_decoderMap.insert(STATE_Alarm_AirBag, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_AirBag2, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_Battery, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_Brake, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_Caution, &Car::alarmStateDecoder);
//    m_decoderMap.insert(STATE_Alarm_Door, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_Engine, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_ESP, &Car::alarmStateDecoder);
// 适配协议盒错误
//    m_decoderMap.insert(STATE_Alarm_LowFuel, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_LowFeul, &Car::alarmStateDecoder);

    m_decoderMap.insert(STATE_Alarm_MotorOil, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_SeatBelt, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_Stop, &Car::alarmStateDecoder);
    m_decoderMap.insert(STATE_Alarm_Warning, &Car::alarmStateDecoder);

    // 车灯状态
    m_decoderMap.insert(STATE_Lamp_DashBoard, &Car::lampStateDecoder);
    m_decoderMap.insert(STATE_Lamp_DippedBeam, &Car::lampStateDecoder);
    m_decoderMap.insert(STATE_Lamp_FrontFog, &Car::lampStateDecoder);
    m_decoderMap.insert(STATE_Lamp_HighBeam, &Car::lampStateDecoder);
    m_decoderMap.insert(STATE_Lamp_Left, &Car::lampStateDecoder);
    m_decoderMap.insert(STATE_Lamp_RearFog, &Car::lampStateDecoder);
    m_decoderMap.insert(STATE_Lamp_Reversing, &Car::lampStateDecoder);
    m_decoderMap.insert(STATE_Lamp_Right, &Car::lampStateDecoder);

    // 车门状态
    m_decoderMap.insert(STATE_DoorState_Boot, &Car::doorStateDecoder);
    m_decoderMap.insert(STATE_DoorState_FrontLeft, &Car::doorStateDecoder);
    m_decoderMap.insert(STATE_DoorState_FrontRight, &Car::doorStateDecoder);
    m_decoderMap.insert(STATE_DoorState_RearLeft, &Car::doorStateDecoder);
    m_decoderMap.insert(STATE_DoorState_RearRight, &Car::doorStateDecoder);
    //m_decoderMap.insert(STATE_DoorState_Hood, &Car::doorStateDecoder);


    // 车门告警
    m_decoderMap.insert(STATE_DoorAlarm_Boot, &Car::doorAlarmDecoder);
    m_decoderMap.insert(STATE_DoorAlarm_FrontLeft, &Car::doorAlarmDecoder);
    m_decoderMap.insert(STATE_DoorAlarm_FrontRight, &Car::doorAlarmDecoder);
    m_decoderMap.insert(STATE_DoorAlarm_RearLeft, &Car::doorAlarmDecoder);
    m_decoderMap.insert(STATE_DoorAlarm_RearRight, &Car::doorAlarmDecoder);
    m_decoderMap.insert(STATE_DoorAlarm_Hood, &Car::doorAlarmDecoder);

    // 按钮状态
    m_decoderMap.insert(STATE_Button_Audio_Source, &Car::buttonStateDecoder);
    m_decoderMap.insert(STATE_Button_Audio_VolumeDown, &Car::buttonStateDecoder);
    m_decoderMap.insert(STATE_Button_Audio_VolumeUp, &Car::buttonStateDecoder);
    m_decoderMap.insert(STATE_Button_Audio_Mute, &Car::buttonStateDecoder);
    m_decoderMap.insert(STATE_Button_Audio_Prev, &Car::buttonStateDecoder);
    m_decoderMap.insert(STATE_Button_Audio_Next, &Car::buttonStateDecoder);
    m_decoderMap.insert(STATE_Button_Audio_Wheel, &Car::buttonWheelDecoder);

    // 车门状态
    m_decoderMap.insert(STATE_Relay_A, &Car::relayStateDecoder);
    m_decoderMap.insert(STATE_Relay_B, &Car::relayStateDecoder);
    m_decoderMap.insert(STATE_Relay_C, &Car::relayStateDecoder);
    m_decoderMap.insert(STATE_Relay_D, &Car::relayStateDecoder);


    //m_decoderMap.insert(STATE_DoorState_Hood, &Car::doorStateDecoder);
    // 线路状态
    m_decoderMap.insert(STATE_Line_State_Acc, &Car::lineStateDecoder);
    m_decoderMap.insert(STATE_Line_State_Reverse, &Car::lineStateDecoder);

    m_decoderMap.insert(STATE_Decoder_Chip_Voltage, &Car::chipVoltageDecoder);
    m_decoderMap.insert(STATE_Decoder_Chip_Temperature, &Car::chipTemperatureDecoder);

    m_decoderMap.insert(STATE_Radar_FrontA, &Car::frontRadarDistanceADecoder);
    m_decoderMap.insert(STATE_Radar_FrontB, &Car::frontRadarDistanceBDecoder);
    m_decoderMap.insert(STATE_Radar_FrontC, &Car::frontRadarDistanceCDecoder);
    m_decoderMap.insert(STATE_Radar_FrontD, &Car::frontRadarDistanceDDecoder);

    m_decoderMap.insert(STATE_Radar_RearA, &Car::rearRadarDistanceADecoder);
    m_decoderMap.insert(STATE_Radar_RearB, &Car::rearRadarDistanceBDecoder);
    m_decoderMap.insert(STATE_Radar_RearC, &Car::rearRadarDistanceCDecoder);
    m_decoderMap.insert(STATE_Radar_RearD, &Car::rearRadarDistanceDDecoder);

    m_decoderMap.insert(STATE_Gps_Direction, &Car::gpsDirctionDecoder);
    m_decoderMap.insert(STATE_Gps_Speed, &Car::gpsSpeedDecoder);
    m_decoderMap.insert(STATE_Gps_Satellites, &Car::gpsSatellitesDecoder);
    m_decoderMap.insert(STATE_Gps_Longitude, &Car::gpsLongitudeDecoder);
    m_decoderMap.insert(STATE_Gps_Latitude, &Car::gpsLatitudeDecoder);
    m_decoderMap.insert(STATE_Gps_Altitude, &Car::gpsAltitudeDecoder);

    m_decoderMap.insert(STATE_Radio_Frequency, &Car::radioFrequencyDecoder);
    m_decoderMap.insert(STATE_Radio_Band, &Car::radioBandDecoder);

    m_decoderMap.insert(STATE_Amplifier_Source, &Car::amplifierSourceDecoder);
    m_decoderMap.insert(STATE_Amplifier_Volume, &Car::amplifierVolumeDecoder);

    m_decoderMap.insert(STATE_Battery_Voltage, &Car::batteryVoltageDecoder);
    m_decoderMap.insert(STATE_Power_Voltage, &Car::powerVoltageDecoder);

    m_decoderMap.insert(STATE_Input_Voltage_A, &Car::inputVoltageADecoder);
    m_decoderMap.insert(STATE_Input_Voltage_B, &Car::inputVoltageBDecoder);
    m_decoderMap.insert(STATE_Input_Voltage_C, &Car::inputVoltageCDecoder);
    m_decoderMap.insert(STATE_Input_Voltage_D, &Car::inputVoltageDDecoder);

    m_decoderMap.insert(STATE_Car_JourneyDistance, &Car::journeyDistanceDecoder);

    m_decoderMap.insert(STATE_Car_Trip1_Speed, &Car::trip1SpeedDecoder);
    m_decoderMap.insert(STATE_Car_Trip1_OilWare, &Car::trip1OilWareDecoder);
    m_decoderMap.insert(STATE_Car_Trip1_Mileage, &Car::trip1MileageDecoder);

    m_decoderMap.insert(STATE_Car_Trip2_Speed, &Car::trip2SpeedDecoder);
    m_decoderMap.insert(STATE_Car_Trip2_OilWare, &Car::trip2OilWareDecoder);
    m_decoderMap.insert(STATE_Car_Trip2_Mileage, &Car::trip2MileageDecoder);

    // 车架号
    m_decoderMap.insert(STATE_Car_TotalMileage, &Car::totalMileageDecoder);

    m_decoderMap.insert(STATE_Car_VIN, &Car::vinDecoder);

    connect(&m_dataSource, SIGNAL(dataChanged(QString,QString)), this, SLOT(onDataChanged(QString,QString)));
}

Car::~Car()
{
    m_dataSource.stop();
    m_dataSource.quit();
    if(!m_dataSource.wait(1000)) //Wait until it actually has terminated (max. 3 sec)
    {
        m_dataSource.terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
        m_dataSource.wait(); //We have to wait again here!
    }
}

void Car::start()
{
    m_dataSource.start();
}

void Car::stop()
{
    m_dataSource.stop();
}

void Car::sendCommand(const QString &command)
{
    if(command.at(command.length()-1) == '\n')
    {
        m_dataSource.send(command);
    }
    else
    {
        m_dataSource.send(command + "\n");

    }
}

float Car::getRev() const
{
    return m_rev;
}

void Car::setRev(float value)
{
    m_rev = value;
    emit revChanged(value);
}

float Car::getSpeed() const
{
    return m_speed;
}

void Car::setSpeed(float value)
{
    m_speed = value;
    emit speedChanged(value);
}

int Car::getGear() const
{
    return m_gear;
}

void Car::setGear(int value)
{
    m_gear = value;
    emit gearChanged(value);
}

int Car::getGearMode() const
{
    return m_gearMode;
}

void Car::setGearMode(int value)
{
    m_gearMode = value;
    emit speedChanged(value);
}

int Car::getGearProfile() const
{
    return m_gearProfile;
}

void Car::setGearProfile(int value)
{
    m_gearProfile = value;
    emit gearProfileChanged(value);
}

float Car::getOilWare() const
{
    return m_oilWare;
}

void Car::setOilWare(float value)
{
    m_oilWare = value;
    emit oilWareChanged(value);
}

int Car::getCruisingRange() const
{
    return m_cruisingRange;
}

void Car::setCruisingRange(int value)
{
    m_cruisingRange = value;
    emit cruisingRangeChanged(value);
}

int Car::getCruisingSpeed() const
{
    return m_cruisingSpeed;
}

int Car::setCruisingSpeed(int value)
{
    m_cruisingSpeed = value;
    emit cruisingSpeedChanged(value);
}

int Car::getCruisingMode() const
{
    return m_cruisingMode;
}

void Car::setCruisingMode(unsigned int value)
{
    m_cruisingMode = value;
    emit cruisingModeChanged(value);
}

float Car::getFuelLevel() const
{
    return m_fuelLevel;
}

void Car::setFuelLevel(float value)
{
    m_fuelLevel = value;
    emit fuelLevelChanged(value);
}

float Car::getWaterTemperature() const
{
    return m_waterTemperature;
}

void Car::setWaterTemperature(float value)
{
    m_waterTemperature = value;
    emit waterTemperatureChanged(value);
}

float Car::getOutsideTemperature() const
{
    return m_outsideTemperature;
}

void Car::setOutsideTemperature(float value)
{
    m_outsideTemperature = value;
    emit outsideTemperatureChanged(value);
}

float Car::getOilTemperature() const
{
    return m_oilTemperature;
}

void Car::setOilTemperature(float value)
{
    m_oilTemperature = value;
    emit oilTemperatureChanged(value);
}

unsigned int Car::getAlarmState() const
{
    return m_alarmState;
}

void Car::setAlarmState(unsigned int value)
{
    m_alarmState = value;
    emit alarmStateChanged(value);
}

unsigned int Car::getLampState() const
{
    return m_lampState;
}

void Car::setLampState(unsigned int value)
{
    m_lampState = value;
    emit lampStateChanged(value);
}

unsigned int Car::getDoorState() const
{
    return m_doorState;
}

void Car::setDoorState(unsigned int value)
{
    m_doorState = value;
    emit doorStateChanged(value);
}

unsigned int Car::getButtonState() const
{
    return m_buttonState;
}

void Car::setButtonState(unsigned int value)
{
    m_buttonState = value;
    emit buttonStateChanged(value);
}

int Car::getRcWheelState() const
{
    return m_rcWheelState;
}

void Car::setRcWheelState(int value)
{
    m_rcWheelState = value;
    emit rcWheelStateChanged(value);
}

unsigned int Car::getLineState() const
{
    return m_lineState;
}

void Car::setLineState(unsigned int value)
{
    m_lineState = value;
    emit lineStateChanged(value);
}

unsigned int Car::getDoorAlarm() const
{
    return m_doorAlarm;
}

void Car::setDoorAlarm(unsigned int value)
{
    m_doorAlarm = value;
    emit doorAlarmChanged(m_doorAlarm);
}

float Car::getFrontRadarDistanceA() const
{
    return m_frontRadarDistanceA;
}

void Car::setFrontRadarDistanceA(float value)
{
    m_frontRadarDistanceA = value;
    emit frontRadarDistanceAChanged(value);
}

float Car::getFrontRadarDistanceB() const
{
    return m_frontRadarDistanceB;
}

void Car::setFrontRadarDistanceB(float value)
{
    m_frontRadarDistanceB = value;
    emit frontRadarDistanceBChanged(value);
}
float Car::getFrontRadarDistanceC() const
{
    return m_frontRadarDistanceC;
}

void Car::setFrontRadarDistanceC(float value)
{
    m_frontRadarDistanceC = value;
    emit frontRadarDistanceCChanged(value);
}

float Car::getFrontRadarDistanceD() const
{
    return m_frontRadarDistanceD;
}

void Car::setFrontRadarDistanceD(float value)
{
    m_frontRadarDistanceD = value;
    emit frontRadarDistanceDChanged(value);
}

float Car::getRearRadarDistanceA() const
{
    return m_rearRadarDistanceA;
}

void Car::setRearRadarDistanceA(float value)
{
    m_rearRadarDistanceA = value;
    emit rearRadarDistanceAChanged(value);
}

float Car::getRearRadarDistanceB() const
{
    return m_rearRadarDistanceB;
}

void Car::setRearRadarDistanceB(float value)
{
    m_rearRadarDistanceB = value;
    emit rearRadarDistanceBChanged(value);
}

float Car::getRearRadarDistanceC() const
{
    return m_rearRadarDistanceC;
}

void Car::setRearRadarDistanceC(float value)
{
    m_rearRadarDistanceC = value;
    emit rearRadarDistanceCChanged(value);
}

float Car::getRearRadarDistanceD() const
{
    return m_rearRadarDistanceD;
}

void Car::setRearRadarDistanceD(float value)
{
    m_rearRadarDistanceD = value;
    emit rearRadarDistanceDChanged(value);
}

float Car::getGpsDirction() const
{
    return m_gpsDirction;
}

void Car::setGpsDirction(float value)
{
    m_gpsDirction = value;
    emit gpsDirctionChanged(value);
}

float Car::getGpsSpeed() const
{
    return m_gpsSpeed;
}

void Car::setGpsSpeed(float value)
{
    m_gpsSpeed = value;
    emit gpsSpeedChanged(value);
}

int Car::getGpsSatellites() const
{
    return m_gpsSatellites;
}

void Car::setGpsSatellites(int value)
{
    m_gpsSatellites = value;
    emit gpsSatellitesChanged(value);
}

float Car::getGpsLongitude() const
{
    return m_gpsLongitude;
}

void Car::setGpsLongitude(float value)
{
    m_gpsLongitude = value;
    emit gpsLongitudeChanged(value);
}

float Car::getGpsLatitude() const
{
    return m_gpsLatitude;
}

void Car::setGpsLatitude(float value)
{
    m_gpsLatitude = value;
    emit gpsLatitudeChanged(value);
}

float Car::getGpsAltitude() const
{
    return m_gpsAltitude;
}

void Car::setGpsAltitude(float value)
{
    m_gpsAltitude = value;
    emit gpsAltitudeChanged(value);
}

float Car::getRadioFrequency() const
{
    return m_radioFrequency;
}

void Car::setRadioFrequency(float value)
{
    m_radioFrequency = value;
    emit radioFrequencyChanged(value);
}

int Car::getRadioBand() const
{
    return m_radioBand;
}

void Car::setRadioBand(int value)
{
    m_radioBand = value;
    emit radioBandChanged(value);
}

int Car::getAmplifierSource() const
{
     return m_amplifierSource;
}

void Car::setAmplifierSource(int value)
{
    m_amplifierSource = value;
    emit amplifierSourceChanged(value);
}

int Car::getAmplifierVolume() const
{
     return m_amplifierVolume;
}

void Car::setAmplifierVolume(int value)
{
    m_amplifierVolume = value;
    emit amplifierVolumeChanged(value);
}

float Car::getBatteryVoltage() const
{
     return m_batteryVoltage;
}

void Car::setBatteryVoltage(float value)
{
    m_batteryVoltage = value;
    emit batteryVoltageChanged(value);
}

float Car::getPowerVoltage() const
{
    return m_powerVoltage;
}

void Car::setPowerVoltage(float value)
{
    m_powerVoltage = value;
    emit powerVoltageChanged(value);
}

float Car::getInputVoltageA() const
{
    return m_inputVoltageA;
}

void Car::setInputVoltageA(float value)
{
    m_inputVoltageA = value;
    emit inputVoltageAChanged(value);
}

float Car::getInputVoltageB() const
{
    return m_inputVoltageB;
}

void Car::setInputVoltageB(float value)
{
    m_inputVoltageB = value;
    emit inputVoltageBChanged(value);
}

float Car::getInputVoltageC() const
{
    return m_inputVoltageC;
}

void Car::setInputVoltageC(float value)
{
    m_inputVoltageC = value;
    emit inputVoltageCChanged(value);
}

float Car::getInputVoltageD() const
{
    return m_inputVoltageD;
}

void Car::setInputVoltageD(float value)
{
    m_inputVoltageD = value;
    emit inputVoltageDChanged(value);
}

unsigned int Car::getRelayState() const
{
    return m_relayState;
}

void Car::setRelayState(unsigned int value)
{
    m_relayState = value;
    emit relayStateChanged(value);
}

float Car::getChipVoltage() const
{
    return m_chipVoltage;
}

void Car::setChipVoltage(float value)
{
    m_chipVoltage = value;
    emit chipVoltageChanged(value);
}

float Car::getChipTemperature() const
{
    return m_chipTemperature;
}

void Car::setChipTemperature(float value)
{
    m_chipTemperature = value;
    emit chipTemperatureChanged(value);
}



float Car::getJourneyDistance() const
{
    return m_journeyDistance;
}

void Car::setJourneyDistance(float value)
{
    m_journeyDistance = value;
    emit journeyDistanceChanged(value);
}

float Car::getTrip1Speed() const
{
    return m_trip1Speed;
}

void Car::setTrip1Speed(float value)
{
    m_trip1Speed = value;
    emit trip1SpeedChanged(value);
}

float Car::getTrip1OilWare() const
{
    return m_trip1OilWare;
}

void Car::setTrip1OilWare(float value)
{
    m_trip1OilWare = value;
    emit trip1OilWareChanged(value);
}

unsigned int Car::getTip1Mileage() const
{
    return m_trip1Mileage;
}

void Car::setTrip1Mileage(unsigned int value)
{
    m_trip1Mileage = value;
    emit trip1MileageChanged(value);
}

float Car::getTrip2Speed() const
{
    return m_trip2Speed;
}

void Car::setTrip2Speed(float value)
{
    m_trip2Speed = value;
    emit trip2SpeedChanged(value);
}

float Car::getTrip2OilWare() const
{
    return m_trip2OilWare;
}

void Car::setTrip2OilWare(float value)
{
    m_trip2OilWare = value;
    emit trip2OilWareChanged(value);
}

unsigned int Car::getTrip2Mileage() const
{
    return m_trip2Mileage;
}

void Car::setTrip2Mileage(unsigned int value)
{
    m_trip2Mileage = value;
    emit trip2MileageChanged(value);
}

unsigned int Car::getTotalMileage() const
{
    return m_totalMileage;
}

void Car::setTotalMileage(unsigned int value)
{
    m_totalMileage = value;
    emit totalMileageChanged(value);
}

QString Car::getVin() const
{
    return m_vin;
}

void Car::setVin(const QString &vin)
{
    m_vin = vin;
    emit vinChanged(m_vin);
}

void Car::onDataChanged(const QString& key, const QString& value)
{
    DecoderMap::iterator it = m_decoderMap.find(key);
    if(it != m_decoderMap.end())
    {
        DataDecoder pDecoder = it.value();
        if(pDecoder)
        {
            (this->*pDecoder)(key, value);
        }
    }
}

void Car::speedDecoder(const QString& key, const QString& value)
{
    float val = value.toFloat();
    setSpeed(val);
}

void Car::revDecoder(const QString& key, const QString& value)
{
    float val = value.toFloat();
    setRev(val);
}

void Car::gearDecoder(const QString &key, const QString &value)
{
    int val = value.toInt();
    setGear(val);
}

void Car::gearModeDecoder(const QString &key, const QString &value)
{
    switch (value.at(0).toLatin1()) {
    case 'N':
        setGearMode(GearMode_N);
    case 'P':
        setGearMode(GearMode_P);
    case 'D':
        setGearMode(GearMode_D);
    case 'R':
        setGearMode(GearMode_R);
    default:
        setGearMode(GearMode_M);
        break;
    }
}

void Car::gearProfileDecoder(const QString &key, const QString &value)
{
    if(value == "Snow")
    {
        setGearProfile(GearProfile_Snow);
    }
    else if(value == "Sport")
    {
        setGearProfile(GearProfile_Sport);
    }
    else
    {
        setGearProfile(GearProfile_Normal);
    }
}

void Car::oilWareDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setOilWare(val);
}

void Car::cruisingRangeDecoder(const QString &key, const QString &value)
{
    int val = value.toFloat();
    setCruisingRange(val);
}

void Car::cruisingSpeedDecoder(const QString &key, const QString &value)
{
    int val = value.toFloat();
    setCruisingSpeed(val);
}

void Car::cruisingModeDecoder(const QString &key, const QString &value)
{
    int val = value.toFloat();
    setCruisingMode(val);
}

void Car::fuelLevelDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setFuelLevel(val);
}

void Car::waterTemperatureDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setWaterTemperature(val);
}

void Car::oilTemperatureDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setOilTemperature(val);
}

void Car::outsideTemperatureDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setOutsideTemperature(val);
}

void Car::alarmStateDecoder(const QString &key, const QString &value)
{
    static const KeyMaskMapItem alarmMap[] =
    {
        {STATE_Alarm_ABS,       Alarm_ABS},
        {STATE_Alarm_AirBag,    Alarm_AirBag},
        {STATE_Alarm_AirBag2,   Alarm_AirBag2},
        {STATE_Alarm_Battery,   Alarm_Battery},
        {STATE_Alarm_Brake,     Alarm_Brake},
        {STATE_Alarm_Caution,   Alarm_Caution},
        {STATE_Alarm_Door,      Alarm_Door},
        {STATE_Alarm_Engine,    Alarm_Engine},
        {STATE_Alarm_ESP,       Alarm_ESP},
// 适配协议盒错误
//        {STATE_Alarm_LowFuel,   Alarm_LowFuel},
        {STATE_Alarm_LowFeul,   Alarm_LowFuel},
        {STATE_Alarm_MotorOil,  Alarm_MotorOil},
        {STATE_Alarm_SeatBelt,  Alarm_SeatBelt},
        {STATE_Alarm_Stop,      Alarm_Stop},
        {STATE_Alarm_Warning,   Alarm_Warning},
        {0,0},
    };
    if(SetState(alarmMap,m_alarmState,key,value) > 0)
    {
        emit alarmStateChanged(m_alarmState);
    }
}

void Car::lampStateDecoder(const QString &key, const QString &value)
{
    static const KeyMaskMapItem lampMap[] =
    {
        {STATE_Lamp_DashBoard,  Lamp_DashBoard},
        {STATE_Lamp_DippedBeam, Lamp_DippedBeam},
        {STATE_Lamp_FrontFog,   Lamp_FrontFog},
        {STATE_Lamp_HighBeam,   Lamp_HighBeam},
        {STATE_Lamp_Left,       Lamp_Left},
        {STATE_Lamp_RearFog,    Lamp_RearFog},
        {STATE_Lamp_Reversing,  Lamp_Reversing},
        {STATE_Lamp_Right,      Lamp_Right},
        {0,0},
    };
    if(SetState(lampMap,m_lampState,key,value) > 0)
    {
        emit lampStateChanged(m_lampState);
    }
}

void Car::doorStateDecoder(const QString &key, const QString &value)
{
    static const KeyMaskMapItem doorMap[] =
    {
        {STATE_DoorState_Boot,          Door_Boot},
        {STATE_DoorState_FrontLeft,     Door_FrontLeft},
        {STATE_DoorState_FrontRight,    Door_FrontRight},
        {STATE_DoorState_RearLeft,      Door_RearLeft},
        {STATE_DoorState_RearRight,     Door_RearRight},
//        {STATE_DoorState_Hood,          Door_Hood},
        {0,0},
    };

    if(SetState(doorMap,m_doorState,key,value) > 0)
    {
        emit doorStateChanged(m_doorState);
    }
}

void Car::buttonStateDecoder(const QString &key, const QString &value)
{
    static const KeyMaskMapItem buttonMap[] =
    {
        {STATE_Button_Audio_Source,     Button_Audio_Source},
        {STATE_Button_Audio_VolumeDown, Button_Audio_VolumeDown},
        {STATE_Button_Audio_VolumeUp,   Button_Audio_VolumeUp},
        {STATE_Button_Audio_Mute,     Button_Audio_Mute},
        {STATE_Button_Audio_Prev,     Button_Audio_Prev},
        {STATE_Button_Audio_Next,     Button_Audio_Next},
        {0,0},
    };

    if(SetState(buttonMap,m_buttonState,key,value) > 0)
    {
        emit buttonStateChanged(m_buttonState);
    }
}

void Car::buttonWheelDecoder(const QString& key, const QString& value)
{
    int val = value.toInt();
    setRcWheelState(val);
}

void Car::lineStateDecoder(const QString &key, const QString &value)
{
    static const KeyMaskMapItem lineMap[] =
    {
        {STATE_Line_State_Acc,          Line_Acc},
        {STATE_Line_State_Reverse,     Line_Reverse},
        {0,0},
    };

    if(SetState(lineMap, m_lineState, key, value) > 0)
    {
        emit lineStateChanged(m_lineState);
    }
}

void Car::doorAlarmDecoder(const QString &key, const QString &value)
{
    static const KeyMaskMapItem doorMap[] =
    {
        {STATE_DoorAlarm_Boot,          Door_Boot},
        {STATE_DoorAlarm_FrontLeft,     Door_FrontLeft},
        {STATE_DoorAlarm_FrontRight,    Door_FrontRight},
        {STATE_DoorAlarm_RearLeft,      Door_RearLeft},
        {STATE_DoorAlarm_RearRight,     Door_RearRight},
//        {STATE_DoorState_Hood,          Door_Hood},
        {0,0},
    };

    if(SetState(doorMap,m_doorAlarm,key,value) > 0)
    {
        emit doorAlarmChanged(m_doorAlarm);
    }
}

void Car::frontRadarDistanceADecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setFrontRadarDistanceA(val);
}

void Car::frontRadarDistanceBDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setFrontRadarDistanceB(val);
}

void Car::frontRadarDistanceCDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setFrontRadarDistanceC(val);
}

void Car::frontRadarDistanceDDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setFrontRadarDistanceD(val);
}

void Car::rearRadarDistanceADecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setRearRadarDistanceA(val);
}

void Car::rearRadarDistanceBDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setRearRadarDistanceB(val);
}

void Car::rearRadarDistanceCDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setRearRadarDistanceC(val);
}

void Car::rearRadarDistanceDDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setRearRadarDistanceD(val);
}

void Car::gpsDirctionDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setGpsDirction(val);
}

void Car::gpsSpeedDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setGpsSpeed(val);
}

void Car::gpsSatellitesDecoder(const QString &key, const QString &value)
{
    int val = value.toInt();
    setGpsSatellites(val);
}

void Car::gpsLongitudeDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setGpsLongitude(val);
}

void Car::gpsLatitudeDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setGpsLatitude(val);
}

void Car::gpsAltitudeDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setGpsAltitude(val);
}

void Car::radioFrequencyDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setRadioFrequency(val);
}

void Car::radioBandDecoder(const QString &key, const QString &value)
{
    if("AM" == value)
    {
        setRadioBand(Band_AM);
    } else {
        setRadioBand(Band_FM);
    }

}

void Car::amplifierSourceDecoder(const QString &key, const QString &value)
{
    int val = value.toInt();
    setAmplifierSource(val);
}

void Car::amplifierVolumeDecoder(const QString &key, const QString &value)
{
    int val = value.toInt();
    setAmplifierVolume(val);
}

void Car::batteryVoltageDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setBatteryVoltage(val);
}

void Car::powerVoltageDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setPowerVoltage(val);
}

void Car::inputVoltageADecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setInputVoltageA(val);
}

void Car::inputVoltageBDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setInputVoltageB(val);
}

void Car::inputVoltageCDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setInputVoltageC(val);
}

void Car::inputVoltageDDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setInputVoltageD(val);
}

void Car::relayStateDecoder(const QString &key, const QString &value)
{
    static const KeyMaskMapItem relayMap[] =
    {
        {STATE_Relay_A, Relay_A},
        {STATE_Relay_B, Relay_B},
        {STATE_Relay_C, Relay_C},
        {STATE_Relay_D, Relay_D},
        {STATE_Relay_E, Relay_E},
        {STATE_Relay_F, Relay_F},
        {STATE_Relay_G, Relay_G},
        {STATE_Relay_H, Relay_H},
        {0,0},
    };

    if(SetState(relayMap, m_relayState, key, value) > 0)
    {
        emit relayStateChanged(m_relayState);
    }
}

void Car::chipVoltageDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setChipVoltage(val);
}

void Car::chipTemperatureDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setChipTemperature(val);
}

void Car::journeyDistanceDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setJourneyDistance(val);
}

void Car::trip1SpeedDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setTrip1Speed(val);
}

void Car::trip1OilWareDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setTrip1OilWare(val);
}

void Car::trip1MileageDecoder(const QString &key, const QString &value)
{
    int val = value.toInt();
    setTrip1Mileage(val);
}

void Car::trip2SpeedDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setTrip2Speed(val);
}

void Car::trip2OilWareDecoder(const QString &key, const QString &value)
{
    float val = value.toFloat();
    setTrip2OilWare(val);
}

void Car::trip2MileageDecoder(const QString &key, const QString &value)
{
    int val = value.toInt();
    setTrip2Mileage(val);
}

void Car::totalMileageDecoder(const QString &key, const QString &value)
{
    // 总里程协议盒送过来的好像是乘以10之后的
    unsigned int val = value.toInt() / 10;
    setTotalMileage(val);
}

void Car::vinDecoder(const QString &key, const QString &value)
{
    setVin(value);
}

