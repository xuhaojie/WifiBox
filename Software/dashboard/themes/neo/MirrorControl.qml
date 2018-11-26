import QtQuick 2.0

Item {
    property variant mirrorNames: ["Button.WingMirror.Left","Button.WingMirror.Right"]

    Row{
        anchors.fill: parent

        Repeater{
            model: 2
            Item{
                width : parent.width / 2
                height: parent.height
                Grid{
                    anchors.centerIn: parent
                    width : parent.width / 2
                    height: parent.height / 2
                    rows: 3
                    columns: 3
                    Item{
                        width : parent.width / 3
                        height: parent.height / 3
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
                                    car.sendCommand(mirrorNames[index] + "=2")
                                }
                                onReleased:{
                                    car.sendCommand(mirrorNames[index] + "=0")
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
                                    car.sendCommand(mirrorNames[index] + "=3")
                                }
                                onReleased:{
                                    car.sendCommand(mirrorNames[index] + "=0")
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
                                    car.sendCommand(mirrorNames[index] + "=4")
                                }
                                onReleased:{
                                    car.sendCommand(mirrorNames[index] + "=0")
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
                                normalImage: "images/down.png"
                                onPressed: {
                                    car.sendCommand(mirrorNames[index] + "=1")
                                }
                                onReleased:{
                                    car.sendCommand(mirrorNames[index] + "=0")
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
                    }
                }

            }
        }

    }
}
