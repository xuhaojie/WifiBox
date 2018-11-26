import QtQuick 2.11
import car.autopard.com 1.0
Item {
    id: doorPanel

    //color: "#343434"
    //Item{
    //    anchors.fill: parent
        /*
        Text{
            id:hoodLabel
            anchors.top:parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.height / 16
            color: (car.doorAlarm & Car.Door_Hood) ? "red":"gray"
            text:"引擎盖"
        }

        Text{
            id:frontLeftLabel
            anchors.left:images.left
            anchors.top:hoodLabel.bottom
            font.pixelSize: parent.height / 16
            color:  (car.doorAlarm & Car.Door_FrontLeft) ? "red":"gray"
            text:"左前门"
        }

        Text{

            id:frontRightLabel
            anchors.right:images.right
            anchors.top:hoodLabel.bottom
            font.pixelSize: parent.height / 16
            color: (car.doorAlarm & Car.Door_FrontRight) ? "red":"gray"
            text:"右前门"horizontalCenter
        }
        */
        Item{
            id:images
            //anchors.top:hoodLabel.bottom
            //anchors.bottom:bootLabel.top
            anchors.centerIn: parent
            width:parent.width *0.8
            height:parent.height *0.8
            Image{
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "images/cardoor/car.png"

            }
            Image{
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "images/cardoor/front-left.png"
                visible: (car.doorAlarm & Car.Door_FrontLeft) ? true:false
            }
            Image{
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "images/cardoor/front-right.png"
                visible: (car.doorAlarm & Car.Door_FrontRight) ? true:false
            }
            Image{
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "images/cardoor/rear-left.png"
                visible: (car.doorAlarm & Car.Door_RearLeft) ? true:false

            }
            Image{
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "images/cardoor/rear-right.png"
                visible: (car.doorAlarm & Car.Door_RearRight) ? true:false
            }
            Image{
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "images/cardoor/hood.png"
                visible: (car.doorAlarm & Car.Door_Hood) ? true:false

            }
            Image{
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "images/cardoor/boot.png"
                visible: (car.doorAlarm & Car.Door_Boot) ? true:false
            }
        }
        /*
        Text{

            id:rearLeftLabel
            anchors.left:images.left
            anchors.bottom:bootLabel.top
            font.pixelSize: parent.height / 16
            color: (car.doorAlarm & Car.Door_RearLeft) ? "red" : "gray"
            text:"左后门"
        }

        Text{

            id:rearRightLabel
            anchors.right:images.right
            anchors.bottom:bootLabel.top
            font.pixelSize: parent.height / 16
            color:(car.doorAlarm & Car.Door_RearRight) ? "red":"gray"
            text: "右后门"
        }

        Text{
            id:bootLabel
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:images.bottom
            anchors.bottom:parent.bottom
            font.pixelSize: parent.height / 16
            color: (car.doorAlarm & Car.Door_Boot) ? "red":"gray"
            text:"后备箱"
        }
        */

    //}
}
