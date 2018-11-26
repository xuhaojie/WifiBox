import QtQuick 2.0

Item {
    id: launchPage
    //color: "#343434"
    Grid{
        id:grid
        anchors.centerIn: parent
        width:parent.width*0.8
        height:parent.height*0.8
        rows:2
        rowSpacing: 20;
        columns: 3
        columnSpacing: 40;
        Item{
            width : grid.width / grid.columns
            height: grid.height / grid.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/autonav.png"
                    onClicked: {
                        // 启动高德 ，测试通过
                        notificationClient.launchApp("com.autonavi.amapauto")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("高德地图车机版")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }



        Item{
            width : grid.width / grid.columns
            height: grid.height / grid.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/baidumap.png"
                    onClicked: {
                        // 启动百度地图 ，测试通过
                        notificationClient.launchApp("com.baidu.BaiduMap.pad")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("百度地图HD")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }

        Item{
            width : grid.width / grid.columns
            height: grid.height / grid.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/contact.png"
                    onClicked: {
                        // 查看联系人，测试通过
                        notificationClient.callIntent("android.intent.action.VIEW","content://contacts/people")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("联系人")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : grid.width / grid.columns
            height: grid.height / grid.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/autonav.png"
                    onClicked: {
                        // 启动高德 ，测试通过
                        notificationClient.launchApp("com.autonavi.minimap")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("高德地图")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }

        Item{
            width : grid.width / grid.columns
            height: grid.height / grid.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/baidumap.png"
                    onClicked: {
                        // 启动百度地图 ，测试通过
                        notificationClient.launchApp("com.baidu.BaiduMap")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("百度地图")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
        Item{
            width : grid.width / grid.columns
            height: grid.height / grid.rows
            Column{
                anchors.fill: parent
                width:parent.width*0.8
                height:parent.height*0.8
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/phone.png"
                    onClicked: {
                        // 拨打电话，测试通过
                        notificationClient.callIntent("android.intent.action.DIAL","tel:")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("拨号")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
/*
        Item{
            width : grid.width / grid.columns
            height: grid.height / grid.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/simulate.png"
                    onClicked: {
                        // 百度地图，测试通过
                        notificationClient.callIntent("android.intent.action.VIEW","baidumap://map/newsassistant")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("高德地图")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }

        Item{
            width : grid.width / grid.columns
            height: grid.height / grid.rows
            Column{
                anchors.fill: parent
                ImageButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:parent.width*0.8
                    height:parent.height*0.8
                    fillMode: Image.PreserveAspectFit
                    normalImage: "images/simulate.png"
                    onClicked: {
                        // 百度地图，测试通过
                        notificationClient.callIntent("android.intent.action.VIEW","androidamap://navi?")
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("高德地图")
                    font.pixelSize: parent.height / 8
                    color:"white"
                }
            }
        }
*/
    }
}
