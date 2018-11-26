#include "carstategenerator.h"
CarStateGenerator::CarStateGenerator(QObject *parent) : QThread(parent)
  ,m_car(0)
  ,m_tick(0)
{

}

void CarStateGenerator::SetTarget(Car *pCar)
{
    m_car = pCar;
}



void CarStateGenerator::run()
{
    while(true)
    {
        if ( QThread::currentThread()->isInterruptionRequested() ) {
            return;
        }
        simulate();
        m_tick++;
        usleep(20000);
    }
}

void CarStateGenerator::simulate()
{

    if(0 != m_car)
    {
        Car& car = *m_car;
        //char Buffer[4096];
        // 速度
        static float Speed = 0.0f;
        Speed += 0.1f;
        if(Speed > 140.0f)
        {
            Speed = 0.0f;
        }
        car.setVin("LDC0123456789ABCD");
        car.setTotalMileage(123456 +float(500+Speed/2.5f));

        car.setSpeed(Speed);

        car.setTrip1Speed(Speed/2.5f);
        car.setTrip2Speed(Speed/3.0f);

        car.setTrip1Mileage(float(500+Speed/2.5f));
        car.setTrip2Mileage(float(500+Speed/3.5f));
        car.setBatteryVoltage(float(12.0 + Speed / 100.0));

        // 引擎转速
        static int  RPM = 0;
        RPM+=10;
        if(RPM > 7000)
        {
            RPM = 0;

        }

        car.setRev(RPM);

        car.setOilWare(30.0f*RPM/7000.0f);
        car.setTrip1OilWare(40.0f*RPM/6000.0f);
        car.setTrip2OilWare(40.0f*RPM/6000.0f);

        static int Direction = 0;
        Direction++;
        if(Direction > 360)
        {
            Direction = 0;
        }
        car.setGpsDirction(Direction);

        car.setGpsDirction(60 + Speed);


        static unsigned int Tick = 0;
        const unsigned int CurTick = m_tick;
        if(CurTick - Tick < 300)
        {
            return;
        }
        else
        {
            Tick = CurTick;
        }



        // 室外温度
        static int OutsideTemperature = 0;
        OutsideTemperature++;
        if(OutsideTemperature >= 42)
        {
            OutsideTemperature = 0;
        }
        car.setOutsideTemperature(OutsideTemperature);

        // 水温
        static int WaterTemperature = 0;
        WaterTemperature++;
        if(WaterTemperature >= 130)
        {
            WaterTemperature = 0;
        }
        car.setWaterTemperature(WaterTemperature);
        car.setOilTemperature(WaterTemperature / 2);

        // 油量
        static int OilMass = 0;
        --OilMass;

        if(OilMass < 0)
        {
            OilMass = 100;
        }

        car.setFuelLevel(OilMass);

        car.setCruisingRange(OilMass*740/100);

        // 档位
        static int Gear = 0;
        Gear++;
        if(Gear > 5)
        {
            Gear = 0;
        }
        car.setGear(Gear);


        // 档位Snow
        static int GearProfile = 0;
        GearProfile++;
        if(GearProfile > 4)
        {
            GearProfile = 0;
        }
        car.setGearProfile(GearProfile);

        // 档位模式
        static int GearMode = 0;
        GearMode++;
        if(GearMode > 2)
        {
            GearMode = 0;
        }
        car.setGearMode(GearMode);

        // 巡航模式
        static int CruiseMode = 0;
        CruiseMode++;
        if(CruiseMode > 2)
        {
            CruiseMode = 0;
        }
        //SetCarState(m_piEnvironment, STATE_Car_CruisingMode, CruiseMode);

        // 巡航速度
        static float CruiseSpeed = 0.0f;

        CruiseSpeed += 0.1f;
        if(CruiseSpeed > 140.0f)
        {
            CruiseSpeed = 0.0f;
        }


        // 指示灯状态
        static int Lamp = 0;
        Lamp++;
        if(Lamp > 1)
        {
            Lamp = 0;
        }

        unsigned int state = car.getLampState();
        if(Lamp)
        {
            state |= Car::Lamp_Left
                    | Car::Lamp_Right
                    | Car::Lamp_DippedBeam
                    | Car::Lamp_HighBeam
                    | Car::Lamp_FrontFog
                    | Car::Lamp_RearFog;
        }
        else
        {
            state &= ~(Car::Lamp_Left
                       | Car::Lamp_Right
                       | Car::Lamp_DippedBeam
                       | Car::Lamp_HighBeam
                       | Car::Lamp_FrontFog
                       | Car::Lamp_RearFog);
        }
        car.setLampState(state);

        state = car.getAlarmState();
        if(Lamp)
        {
            state |= Car::Alarm_Warning
                    | Car::Alarm_Brake
                    | Car::Alarm_ABS
                    | Car::Alarm_ESP
                    | Car::Alarm_SeatBelt
                    | Car::Alarm_Engine
                    | Car::Alarm_AirBag
                    | Car::Alarm_AirBag2
                    | Car::Alarm_Stop
                    | Car::Alarm_MotorOil
                    | Car::Alarm_LowFuel
                    | Car::Alarm_Battery;

        }
        else
        {
            state &= ~(Car::Alarm_Warning
                       | Car::Alarm_Brake
                       | Car::Alarm_ABS
                       | Car::Alarm_ESP
                       | Car::Alarm_SeatBelt
                       | Car::Alarm_Engine
                       | Car::Alarm_AirBag
                       | Car::Alarm_AirBag2
                       | Car::Alarm_Stop
                       | Car::Alarm_MotorOil
                       | Car::Alarm_LowFuel
                       | Car::Alarm_Battery);
        }
        car.setAlarmState(state);


        // 收音机波段
        //const char* BandNameMap[6] = {"","FM","FM","","FM","AM"};
        static int RadioBand = 0;
        ++RadioBand;
        if(RadioBand > 5)
        {
            RadioBand = 0;
        }
        car.setRadioBand(RadioBand);

        // 收音机频率
        static float  Frequency = 87.5;
        Frequency += 0.1f;
        if(Frequency > 108.0f)
        {
            Frequency = 87.5;
        }
        car.setRadioFrequency(Frequency);

        static int GpsSatellites = 0;

        if(++GpsSatellites > 12)
        {
            GpsSatellites = 0;
        }
        car.setGpsSatellites(GpsSatellites);


        const char* SourceNameMap[7] = {"Radio","CD","CDC","AUX1","AUX2","BT","USB"};
        // RD4音源
        static int AudioSource = 0;
        AudioSource++;
        if(AudioSource >= sizeof(SourceNameMap)/sizeof(SourceNameMap[0]))
        {
            AudioSource = 0;
        }
        car.setAmplifierSource(AudioSource);

        car.setAmplifierVolume(30*OilMass/100);
/*
        static int rcWheelValueDelta = 1;
        static int rcWheelValue = 0;
        rcWheelValue += rcWheelValueDelta;
        if(rcWheelValue > 64)
        {
            rcWheelValue = 63;
            rcWheelValueDelta = -1;
        }
        else if(rcWheelValue < 0)
        {
            rcWheelValue = 0;
            rcWheelValueDelta = 1;
        }
        car.setRcWheelState(rcWheelValue);

        static int rcButtonState = 0;
        if(rcButtonState)
        {
            car.setButtonState(Car::Button_Audio_Next);
        }
        else
        {
            car.setButtonState(Car::Button_Audio_Prev);
        }
        rcButtonState = 1 - rcButtonState;
*/
        // 车门状态
        static int Door = 0;
        Door++;
        if(Door > 1)
        {
            Door = 0;
        }
        state = car.getDoorState();
        if(Door)
        {
            state |= Car::Door_Hood
                    | Car::Door_FrontLeft
                    | Car::Door_FrontRight
                    | Car::Door_RearLeft
                    | Car::Door_RearRight
                    | Car::Door_Boot;
        }
        else
        {
            state &= ~(Car::Door_Hood
                       | Car::Door_FrontLeft
                       | Car::Door_FrontRight
                       | Car::Door_RearLeft
                       | Car::Door_RearRight
                       | Car::Door_Boot);
        }
        car.setDoorAlarm(state);
        car.setDoorState(state);

    }

}
