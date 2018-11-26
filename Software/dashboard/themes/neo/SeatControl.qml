import QtQuick 2.0

Item {
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
                        //
                        ImageButton {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width:parent.width*0.8
                            height:parent.height*0.8
                            fillMode: Image.PreserveAspectFit
                            normalImage: "images/tilt-front.png"
                            onClicked: {
                            }
                        }
                    }
                    Item{
                        width : parent.width / 3
                        height: parent.height / 3
                        ImageButton {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width:parent.width*0.8
                            height:parent.height*0.8
                            fillMode: Image.PreserveAspectFit
                            normalImage: "images/up.png"
                            onClicked: {
                            }
                        }
                    }
                    Item{
                        width : parent.width / 3
                        height: parent.height / 3
                        //
                        ImageButton {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width:parent.width*0.8
                            height:parent.height*0.8
                            fillMode: Image.PreserveAspectFit
                            normalImage: "images/tilt-back.png"
                            onClicked: {
                            }
                        }
                    }
                    Item{
                        width : parent.width / 3
                        height: parent.height / 3
                        ImageButton {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width:parent.width*0.8
                            height:parent.height*0.8
                            fillMode: Image.PreserveAspectFit
                            normalImage: "images/left.png"
                            onClicked: {
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
                        ImageButton {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width:parent.width*0.8
                            height:parent.height*0.8
                            fillMode: Image.PreserveAspectFit
                            normalImage: "images/right.png"
                            onClicked: {
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
                        ImageButton {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width:parent.width*0.8
                            height:parent.height*0.8
                            fillMode: Image.PreserveAspectFit
                            normalImage: "images/down.png"
                            onClicked: {
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
