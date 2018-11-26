import QtQuick 2.11

Item {
    id: deviceSetup
    //color: "#343434"
    Grid{
        anchors.fill: parent
        rows:5
        rowSpacing: 20;
        columns: 2
        columnSpacing: 40;
        Text{
            text: "继电器A名称"
            color: "white"
            font.pixelSize: deviceSetup.height/20
        }
        Text{
            text: "Relay A"
            color: "white"
            font.pixelSize: deviceSetup.height/20
        }

        Text{
            text: "继电器B名称"
            color: "white"
            font.pixelSize: deviceSetup.height/20
        }
        Text{
            text: "Relay B"
            color: "white"
            font.pixelSize: deviceSetup.height/20
        }


        Text{
            text: "继电器C名称"
            color: "white"
            font.pixelSize: deviceSetup.height/20
        }
        Text{
            text: "Relay C"
            color: "white"
            font.pixelSize: deviceSetup.height/20
        }

        Text{
            text: "继电器D名称"
            color: "white"
            font.pixelSize: deviceSetup.height/20
        }
        Text{
            text: "Relay D"
            color: "white"
            font.pixelSize: deviceSetup.height/20
        }

        Text{
            text: "协议盒电源锁定"
            color: "white"
            font.pixelSize: deviceSetup.height/20
        }

        SwitchButton
        {
            id: demoModeButton
            height: deviceSetup.height/16
            onClicked:
            {

                //appSetting.set("App.DemoMode",demoModeButton.checked);

            }
        }

    }
    Component.onCompleted: {
        //var demoMode = appSetting.get("App.DemoMode");
        //demoModeButton.checked = demoMode
    }
}
