import QtQuick 2.0
import car.autopard.com 1.0
Item{
    id:panel
//    color: "black"
    opacity: 0.5
//    radius: 5
//    border.color: "white"
//    border.width: 2
    //clip:true
    Row {
        anchors.centerIn: parent
        ImageIndicator{
            width: panel.width / 6
            height: panel.height
            value: car.lampState & Car.Lamp_Left ? 1:0
            images : ["images/left-lamp-0.svg","images/left-lamp-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 6
            height: panel.height
            value: car.lampState & Car.Lamp_FrontFog ? 1:0
            images : ["images/front-fog-lamp-0.svg", "images/front-fog-lamp-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 6
            height: panel.height
            value: car.lampState & Car.Lamp_DippedBeam ? 1:0
            images : ["images/dipped-headlight-0.svg","images/dipped-headlight-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 6
            height: panel.height
            value: car.lampState & Car.Lamp_HighBeam ? 1:0
            images : ["images/high-beam-0.svg" , "images/high-beam-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 6
            height: panel.height
            value: car.lampState & Car.Lamp_RearFog ? 1:0
            images : ["images/rear-fog-lamp-0.svg", "images/rear-fog-lamp-1.svg"]
        }
        ImageIndicator{
            width: panel.width / 6
            height: panel.height
            value: car.lampState & Car.Lamp_Right ? 1:0
            images : ["images/right-lamp-0.svg","images/right-lamp-1.svg"]
        }
    }
}
