import QtQuick 2.0
import QtQuick.Controls 2.0
import car.autopard.com 1.0
Column {
    Grid{
        anchors.top: parent.top
        width : parent.width
        height: parent.height / 3
        rows: 2
        columns: 3
        Item{
            width : parent.width / parent.columns
            height: parent.height / parent.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/source.png"
                    onPressed: {
                        car.sendCommand("Button.Audio.Source=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Audio.Source=0")
                    }

                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("音源")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / parent.columns
            height: parent.height / parent.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/prev.png"
                    onPressed: {
                        car.sendCommand("Button.Audio.Prev=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Audio.Prev=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("上一曲")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / parent.columns
            height: parent.height / parent.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/next.png"
                    onPressed: {
                        car.sendCommand("Button.Audio.Next=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Audio.Next=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("下一曲")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / parent.columns
            height: parent.height / parent.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/volume-down.png"
                    onPressed: {
                        car.sendCommand("Button.Audio.VolumeDown=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Audio.VolumeDown=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("音量-")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / parent.columns
            height: parent.height / parent.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/volume-up.png"
                    onPressed: {
                        car.sendCommand("Button.Audio.VolumeUp=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Audio.VolumeUp=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("音量+")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / parent.columns
            height: parent.height / parent.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/mute-1.png"
                    onPressed: {
                        car.sendCommand("Button.Audio.Mute=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Audio.Mute=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("静音")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
    }

    Grid{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        width : parent.width / 2
        height: parent.height / 2
        rows: 3
        columns: 3
        Item{
            width : parent.width / 3
            height: parent.height / 3
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/simulate.png"
                    onPressed: {
                        car.sendCommand("Button.Setup.Mode=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Setup.Mode=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("MODE")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / 3
            height: parent.height / 3
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/up.png"
                    onPressed: {
                        car.sendCommand("Button.Setup.Up=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Setup.Up=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("UP")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / 3
            height: parent.height / 3
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/simulate.png"
                    onPressed: {
                        car.sendCommand("Button.Setup.Esc=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Setup.Esc=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("ESC")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / 3
            height: parent.height / 3
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/left.png"
                    onPressed: {
                        car.sendCommand("Button.Setup.Left=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Setup.Left=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("LEFT")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / 3
            height: parent.height / 3
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/simulate.png"
                    onPressed: {
                        car.sendCommand("Button.Setup.Ok=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Setup.Ok=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("OK")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / 3
            height: parent.height / 3
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/right.png"
                    onPressed: {
                        car.sendCommand("Button.Setup.Right=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Setup.Right=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("RIGHT")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / 3
            height: parent.height / 3
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/simulate.png"
                    onPressed: {
                        car.sendCommand("Button.Setup.Dark=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Setup.Dark=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("DARK")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / 3
            height: parent.height / 3
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFitsetup
                    normalImage: "images/down.png"
                    onPressed: {
                        car.sendCommand("Button.Setup.Down=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Setup.Down=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("DOWD")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : parent.width / 3
            height: parent.height / 3
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/simulate.png"
                    onPressed: {
                        car.sendCommand("Button.Setup.Menu=1")
                    }
                    onReleased: {
                        car.sendCommand("Button.Setup.Menu=0")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("MENU")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
    }

}
