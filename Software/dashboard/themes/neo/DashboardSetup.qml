import QtQuick 2.11
import QtQuick.Controls 2.0

Item
{
    id: dashboardSetup
    //color: "#343434"
    Grid{
        anchors.fill: parent
        rows:2
        rowSpacing: 20;
        columns: 2
        columnSpacing: 40;
        Text{
            text: "演示模式"
            color: "white"
            font.pixelSize: dashboardSetup.height/20
        }

        SwitchButton
        {
            id: demoModeButton
            height: dashboardSetup.height/16
            onClicked:{
                var demoMode = demoModeButton.checked;
                if(demoMode) simulator.start()
                else
                {
                    simulator.quit();
                    simulator.terminate();

                }
            }
        }
        Text{
            text: "城市"
            color: "white"
            font.pixelSize: dashboardSetup.height/20
        }
        TextInput{
            color: "white"
            font.pixelSize: dashboardSetup.height/20
            text: "深圳"; font.capitalization: Font.AllLowercase
            onAccepted:  {
                if(text.length < 1) {
                    text = "未知"
                }

                appSetting.set("App.City",text);
                weatherPage.city = text
                focus = false
            }
            Component.onCompleted: {
                var city = appState.get("App.City");
                if(city !== undefined){
                    text = city;
                }
            }
        }

    }
    Component.onCompleted: {
        var demoMode = appSetting.get("App.DemoMode");
        demoModeButton.checked = demoMode
        //if(demoMode) simulator.start()
        //else simulator.stop()
    }
}


