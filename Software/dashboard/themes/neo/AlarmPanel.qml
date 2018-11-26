import QtQuick 2.0
import car.autopard.com 1.0
Item{
    id:panel
//    color: "black"
    opacity: 0.5
//    radius: 5
//    border.color: "white"car.
//    border.width: 2
    //clip:true
    Row {
        anchors.centerIn: parent
        ImageIndicator{
            width: panel.width / 9
            height: panel.height
            images : ["images/abs-0.svg" , "images/abs-1.svg"]
            value: car.alarmState & Car.Alarm_ABS ? 1:0
        }
        ImageIndicator{
            width: panel.width / 9
            height: panel.height
            value: car.alarmState & Car.Alarm_AirBag ? 1:0
            images : ["images/air-bag-0.svg" , "images/air-bag-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 9
            height: panel.height
            value: car.alarmState & Car.Alarm_Battery ? 1:0
            images : ["images/battery-0.svg" , "images/battery-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 9
            height: panel.height
            value: car.alarmState & Car.Alarm_Brake ? 1:0
            images : ["images/handbrake-0.svg" , "images/handbrake-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 9
            height: panel.height
            value: car.alarmState & Car.Alarm_Warning ? 1:0
            images : ["images/warning-0.svg" , "images/warning-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 9
            height: panel.height
            value: car.alarmState & Car.Alarm_Engine ? 1:0
            images : ["images/engine-0.svg" , "images/engine-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 9
            height: panel.height
            value: car.alarmState & Car.Alarm_LowFuel ? 1:0
            images : ["images/fuel-0.svg" , "images/fuel-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 9
            height: panel.height
            value: car.alarmState & Car.Alarm_MotorOil ? 1:0
            images : ["images/motoroil-0.svg" , "images/motoroil-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 9
            height: panel.height
            value: car.alarmState & Car.Alarm_SeatBelt ? 1:0
            images : ["images/sate-belt-0.svg", "images/sate-belt-1.svg"]
        }
    }
}
