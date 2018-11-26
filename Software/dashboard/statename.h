#pragma once
//=================================================================================================
//
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// 车辆状态
//-------------------------------------------------------------------------------------------------

#define DEFINE_NAME(PREFIX,OBJ,A) static const char* PREFIX##_##OBJ##_##A = (#OBJ"."#A)
#define DEFINE_NAME2(PREFIX,OBJ,A,B) static const char* PREFIX##_##OBJ##_##A##_##B = (#OBJ"."#A"."#B)
#define DEFINE_NAME3(PREFIX,OBJ,A,B,C) static const char* PREFIX##_##OBJ##_##A##_##B##_##C = (#OBJ"."#A"."#B"."#C)
#define DEFINE_NAME4(PREFIX,OBJ,A,B,C,D) static const char* PREFIX##_##OBJ##_##A##_##B##_##C##_##D = (#OBJ"."#A"."#B"."#C"."#D)


//-------------------------------------------------------------------------------------------------
// 车辆信息
DEFINE_NAME(STATE, Car, VIN);
// 当前车速
DEFINE_NAME(STATE, Car, Speed);
// 当前引擎转速
DEFINE_NAME(STATE, Car, Rev);
// 续航距离
DEFINE_NAME(STATE, Car, CruisingRange);
// 定速巡航速度
DEFINE_NAME(STATE, Car, CruisingSpeed);
// 定速巡航模式
DEFINE_NAME(STATE, Car, CruisingMode);
// 燃料余量 0-100
// 适配协议盒错误
//DEFINE_NAME(STATE, Car, FuelLevel);
DEFINE_NAME(STATE, Car, FeulLevel);
// 当前档位，如1、2、3、4
DEFINE_NAME(STATE, Car, Gear);
// 档位模式 N R M等
DEFINE_NAME(STATE, Car, GearMode);
// 档位风格 雪地模式 运动模式等
DEFINE_NAME(STATE, Car, GearProfile);
// 当前油耗
DEFINE_NAME(STATE, Car, OilWare);
// 当前水温
DEFINE_NAME(STATE, Car, WaterTemp);
// 当前油温
DEFINE_NAME(STATE, Car, OilTemp);

// 当前外部温度
DEFINE_NAME(STATE, Car, OutsideTemp);

// 旅程距离？
DEFINE_NAME(STATE, Car, JourneyDistance);
// 总里程
DEFINE_NAME(STATE, Car, TotalMileage);

DEFINE_NAME2(STATE, Car, Trip1, Speed);
DEFINE_NAME2(STATE, Car, Trip1, OilWare);
DEFINE_NAME2(STATE, Car, Trip1, Mileage);

DEFINE_NAME2(STATE, Car, Trip2, Speed);
DEFINE_NAME2(STATE, Car, Trip2, OilWare);
DEFINE_NAME2(STATE, Car, Trip2, Mileage);

DEFINE_NAME2(STATE, Line, State, Acc);
DEFINE_NAME2(STATE, Line, State, Reverse);

DEFINE_NAME2(STATE, Button, Audio, Source); //On/Off
DEFINE_NAME2(STATE, Button, Audio, VolumeDown); //On/Off
DEFINE_NAME2(STATE, Button, Audio, VolumeUp); //On/Off
DEFINE_NAME2(STATE, Button, Audio, Prev); //On/Off
DEFINE_NAME2(STATE, Button, Audio, Next); //On/Off
DEFINE_NAME2(STATE, Button, Audio, Mute); //On/Off
DEFINE_NAME2(STATE, Button, Audio, Wheel); //On/Off

// 车窗
DEFINE_NAME2(STATE, Button, Window, FrontLeft); //Up/Down
DEFINE_NAME2(STATE, Button, Window, FrontRight);
DEFINE_NAME2(STATE, Button, Window, RearLeft);
DEFINE_NAME2(STATE, Button, Window, RearRight);

// 中控锁
DEFINE_NAME(STATE, Button, CenterLock);

// 侧后视镜
DEFINE_NAME2(STATE, Button, WingMirror, Left);  //Up/Down/Left/Right
DEFINE_NAME2(STATE, Button, WingMirror, Right); //Up/Down/Left/Right

// 空调
DEFINE_NAME(STATE, Button, AcPower);  //On/Off
DEFINE_NAME(STATE, Button, AcTemp); //Up/Down/Left/Right

// 车辆ABS告警
DEFINE_NAME(STATE, Alarm, ABS);
// 车辆主气囊告警
DEFINE_NAME(STATE, Alarm, AirBag);
// 车辆辅气囊告警
DEFINE_NAME(STATE, Alarm, AirBag2);
// 车辆蓄电池告警
DEFINE_NAME(STATE, Alarm, Battery);
// 车辆刹车池告警
DEFINE_NAME(STATE, Alarm, Brake);
// 车辆Caution告警
DEFINE_NAME(STATE, Alarm, Caution);
// 车辆车门告警
DEFINE_NAME(STATE, Alarm, Door);
// 车辆ESP告警
DEFINE_NAME(STATE, Alarm, ESP);
// 车辆引擎告警
DEFINE_NAME(STATE, Alarm, Engine);
// 燃料不足告警
// 适配协议盒错误
//DEFINE_NAME(STATE, Alarm, LowFuel);
DEFINE_NAME(STATE, Alarm, LowFeul);

// 机油告警
DEFINE_NAME(STATE, Alarm, MotorOil);
// 安全带告警
DEFINE_NAME(STATE, Alarm, SeatBelt);
// STOP告警
DEFINE_NAME(STATE, Alarm, Stop);
// Warning告警
DEFINE_NAME(STATE, Alarm, Warning);

// 机舱盖未关告警
DEFINE_NAME(STATE, DoorAlarm ,Hood);
// 左前门未关告警
DEFINE_NAME(STATE, DoorAlarm, FrontLeft);
// 右前门未关告警
DEFINE_NAME(STATE, DoorAlarm, FrontRight);
// 左后门未关告警
DEFINE_NAME(STATE, DoorAlarm, RearLeft);
// 右后门未关告警
DEFINE_NAME(STATE, DoorAlarm, RearRight);
// 后备箱未关告警
DEFINE_NAME(STATE, DoorAlarm, Boot);

// 左前门状态
DEFINE_NAME(STATE, DoorState, FrontLeft);
// 右前门状态
DEFINE_NAME(STATE, DoorState, FrontRight);
// 左后门状态
DEFINE_NAME(STATE, DoorState, RearLeft);
// 右后门状态
DEFINE_NAME(STATE, DoorState, RearRight);
// 后备箱状态
DEFINE_NAME(STATE, DoorState, Boot);

// 雷达
DEFINE_NAME(STATE, Radar, FrontA);
// 雷达
DEFINE_NAME(STATE, Radar, FrontB);
// 雷达
DEFINE_NAME(STATE, Radar, FrontC);
// 雷达
DEFINE_NAME(STATE, Radar, FrontD);

// 雷达
DEFINE_NAME(STATE, Radar, RearA);
// 雷达
DEFINE_NAME(STATE, Radar, RearB);
// 雷达
DEFINE_NAME(STATE, Radar, RearC);
// 雷达
DEFINE_NAME(STATE, Radar, RearD);


// GPS方向
DEFINE_NAME(STATE, Gps, Direction);
// GPS速度
DEFINE_NAME(STATE, Gps, Speed);
// GPS卫星数量
DEFINE_NAME(STATE, Gps, Satellites);
// GPS经度
DEFINE_NAME(STATE, Gps, Longitude);
// GPS纬度
DEFINE_NAME(STATE, Gps, Latitude);
// GPS海拔
DEFINE_NAME(STATE, Gps, Altitude);



// 仪表盘背光灯状态
DEFINE_NAME(STATE, Lamp, DashBoard);
// 近光灯灯状态
DEFINE_NAME(STATE, Lamp, DippedBeam);
// 前雾灯状态
DEFINE_NAME(STATE, Lamp, FrontFog);
// 远光灯状态
DEFINE_NAME(STATE, Lamp, HighBeam);
// 后雾灯状态
DEFINE_NAME(STATE, Lamp, RearFog);
// 倒车灯状态
DEFINE_NAME(STATE, Lamp, Reversing);
// 右转向灯状态
DEFINE_NAME(STATE, Lamp, Right);
// 左转向灯状态
DEFINE_NAME(STATE, Lamp, Left);


// 收音机频率
DEFINE_NAME(STATE, Radio, Frequency);
// 收音机波段
DEFINE_NAME(STATE, Radio, Band);

// 音响信号源
DEFINE_NAME(STATE, Amplifier, Source);
// 音响音量
DEFINE_NAME(STATE, Amplifier, Volume);

// 电池电压
DEFINE_NAME(STATE, Battery, Voltage);

// 方向盘控制
DEFINE_NAME(STATE, AudioControler, Next);
DEFINE_NAME(STATE, AudioControler, Prev);
DEFINE_NAME(STATE, AudioControler, Wheel);

//-------------------------------------------------------------------------------------------------
// 媒体信息

// 媒体标题
DEFINE_NAME(STATE, Media, Title);
// 媒体艺术家
DEFINE_NAME(STATE, Media, Artist);
// 媒体
DEFINE_NAME(STATE, Media, Genre);
DEFINE_NAME(STATE, Media, Copyright);
// 媒体专辑
DEFINE_NAME(STATE, Media, Album);
DEFINE_NAME(STATE, Media, TrackNumber);
DEFINE_NAME(STATE, Media, Description);
DEFINE_NAME(STATE, Media, Rating);
DEFINE_NAME(STATE, Media, Date);
DEFINE_NAME(STATE, Media, Setting);
DEFINE_NAME(STATE, Media, URL);
DEFINE_NAME(STATE, Media, Language);
DEFINE_NAME(STATE, Media, NowPlaying);
DEFINE_NAME(STATE, Media, Publisher);
DEFINE_NAME(STATE, Media, EncodedBy);
DEFINE_NAME(STATE, Media, ArtworkURL);
DEFINE_NAME(STATE, Media, TrackID);

DEFINE_NAME(STATE, Media, Duration);
DEFINE_NAME(STATE, Media, ElapsedTime);

DEFINE_NAME(STATE, Media, File);

// 继电器
DEFINE_NAME(STATE, Relay, A);
DEFINE_NAME(STATE, Relay, B);
DEFINE_NAME(STATE, Relay, C);
DEFINE_NAME(STATE, Relay, D);

DEFINE_NAME(STATE, Relay, E);
DEFINE_NAME(STATE, Relay, F);
DEFINE_NAME(STATE, Relay, G);
DEFINE_NAME(STATE, Relay, H);

DEFINE_NAME2(STATE, Decoder, Chip,Voltage);
DEFINE_NAME2(STATE, Decoder, Chip,Temperature);

DEFINE_NAME2(STATE, Input, Voltage, A);
DEFINE_NAME2(STATE, Input, Voltage, B);
DEFINE_NAME2(STATE, Input, Voltage, C);
DEFINE_NAME2(STATE, Input, Voltage, D);

DEFINE_NAME(STATE, Power, Voltage);

DEFINE_NAME2(STATE, Device, Power, Lock);  //On/Off

DEFINE_NAME2(CONTROL, Button, Setup, Left); //On/Off
DEFINE_NAME2(CONTROL, Button, Setup, Right); //On/Off
DEFINE_NAME2(CONTROL, Button, Setup, Up); //On/Off
DEFINE_NAME2(CONTROL, Button, Setup, Down); //On/Off
DEFINE_NAME2(CONTROL, Button, Setup, Menu); //On/Off
DEFINE_NAME2(CONTROL, Button, Setup, Esc); //On/Off
DEFINE_NAME2(CONTROL, Button, Setup, Ok); //On/Off
DEFINE_NAME2(CONTROL, Button, Setup, Dark); //On/Off
DEFINE_NAME2(CONTROL, Button, Setup, Mode); //On/Off
DEFINE_NAME2(CONTROL, Button, Setup, DisplayMode); //On/Off

DEFINE_NAME2(CONTROL, Button, Audio, Source); //On/Off
DEFINE_NAME2(CONTROL, Button, Audio, VolumeDown); //On/Off
DEFINE_NAME2(CONTROL, Button, Audio, VolumeUp); //On/Off
DEFINE_NAME2(CONTROL, Button, Audio, Prev); //On/Off
DEFINE_NAME2(CONTROL, Button, Audio, Next); //On/Off
DEFINE_NAME2(CONTROL, Button, Audio, Mute); //On/Off

// 车窗
DEFINE_NAME2(CONTROL, Button, Window, FrontLeft); //Up/Down
DEFINE_NAME2(CONTROL, Button, Window, FrontRight);
DEFINE_NAME2(CONTROL, Button, Window, RearLeft);
DEFINE_NAME2(CONTROL, Button, Window, RearRight);
DEFINE_NAME2(CONTROL, Button, Window, OneKey);
// 中控锁
DEFINE_NAME(CONTROL, Button, CenterLock);

// 侧后视镜
DEFINE_NAME2(CONTROL, Button, WingMirror, Left);  //Up/Down/Left/Right
DEFINE_NAME2(CONTROL, Button, WingMirror, Right); //Up/Down/Left/Right
DEFINE_NAME2(CONTROL, Button, WingMirror, OneKey); //Up/Down/Left/Right

// 空调
DEFINE_NAME2(CONTROL, Button, Ac, Power);  //On/Off
DEFINE_NAME2(CONTROL, Button, Ac, Temp);

// 继电器
DEFINE_NAME(CONTROL, Relay, A);
DEFINE_NAME(CONTROL, Relay, B);
DEFINE_NAME(CONTROL, Relay, C);
DEFINE_NAME(CONTROL, Relay, D);

DEFINE_NAME(CONTROL, Relay, E);
DEFINE_NAME(CONTROL, Relay, F);
DEFINE_NAME(CONTROL, Relay, G);
DEFINE_NAME(CONTROL, Relay, H);

DEFINE_NAME2(CONTROL, Device, Power, Lock);  //On/Off

