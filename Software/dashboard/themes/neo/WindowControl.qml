import QtQuick 2.0

Row {
    id:windowControl
    property variant windowTitles: ["ALL","左前窗","左后窗","右前窗","右后窗"]
    property variant windowIcons: ["images/cardoor/all.png","images/cardoor/front-left.png","images/cardoor/rear-left.png","images/cardoor/front-right.png","images/cardoor/rear-right.png"]
    property variant windowNames: ["OneKey","FrontLeft","RearLeft","FrontRight","RearRight"]

    Repeater{

        model: 5

        Column{
            width: parent.width / 5
            height: parent.height
            Image {
                width: parent.width
                height: parent.height / 2
                source:windowControl.windowIcons[index]
            }
            Text {
                width: parent.width
                height: parent.height / 8
                text: windowControl.windowTitles[index]
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: height* 0.4
                color:"white"
            }
            ImageButton {
                width: parent.width
                height: parent.height / 8
                normalImage: "images/up.png"
                horizontalAlignment: Text.AlignHCenter
                onPressed: {
                    var cmd = "Button.Window." + windowNames[index] + "=1"
                    car.sendCommand(cmd);
                }
                onReleased: {
                    var cmd = "Button.Window." + windowNames[index] + "=0"
                    car.sendCommand(cmd);
                }
            }
            ImageButton {
                width: parent.width
                height: parent.height / 8
                normalImage: "images/down.png"
                horizontalAlignment: Text.AlignHCenter
                onPressed: {
                    var cmd = "Button.Window." + windowNames[index] + "=2"
                    car.sendCommand(cmd);
                }
                onReleased: {
                    var cmd = "Button.Window." + windowNames[index] + "=0"
                    car.sendCommand(cmd);
                }
            }
        }
    }
}
