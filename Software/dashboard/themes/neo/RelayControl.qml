import QtQuick 2.0
import car.autopard.com 1.0
Row {
    id:relayControl
    property variant relayTitle: ["Relay A","Relay B","Relay C","Relay D"]
    property variant relayNames: ["Relay.A","Relay.B","Relay.C","Relay.D"]
    property variant relayMask: [Car.Relay_A, Car.Relay_B, Car.Relay_C, Car.Relay_D]
    Repeater{
        model: 4
        Column{
            width: parent.width / 4
            height: parent.height
            ImageIndicator {
                width: parent.width
                height: parent.height / 2
                value: (car.relayState & relayControl.relayMask[index]) ? 1:0
                images: ["images/relay-0.png" , "images/relay-1.png"]
                onClicked: {
                    if(value >0){
                        car.sendCommand(relayNames[index] + "=0")
                    }else{
                        car.sendCommand(relayNames[index] + "=1")
                    }

                }
            }
            Text {
                width: parent.width
                height: parent.height / 8
                text: relayControl.relayTitle[index]
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: height* 0.4
                color:"white"
            }
            Text {
                width: parent.width
                height: parent.height / 8
                text: qsTr("ON")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: height* 0.8
                color:"white"
                MouseArea{
                    anchors.fill: parent
                    onClicked: { car.sendCommand(relayNames[index] + "=1") }
                }
            }
            Text {
                width: parent.width
                height: parent.height / 8
                text: qsTr("OFF")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: height* 0.8
                color:"white"
                MouseArea{
                    anchors.fill: parent
                    onClicked: { car.sendCommand(relayNames[index] + "=0") }
                }
            }
        }
    }
}
