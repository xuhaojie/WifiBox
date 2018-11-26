import QtQuick 2.0
import QtQuick.Controls 2.0

Item{
    id: naviSetup

    //color: "#343434"
    Grid{
        anchors.fill: parent
        rows:2
        rowSpacing: 20;
        columns: 3
        columnSpacing: 40;

        Text{
            text: "地图选择"
            color: "white"
        }

        ComboBox {
            id: mapSeletctor
            model: ["高德地图", "百度地图"]
            property bool settingLoaded: false
            function updateSetting()
            {
                appState.set("Navi.MapIndex",mapSeletctor.currentIndex);
                console.log(mapSeletctor.currentIndex);
            }
            onCurrentIndexChanged: {
                if(settingLoaded == true) updateSetting()
            }
            Component.onCompleted: {
                var index = appState.get("Navi.MapIndex");
                if(index !== undefined){
                    mapSeletctor.currentIndex = index;
                }
                settingLoaded = true
            }
        }
    }
}
