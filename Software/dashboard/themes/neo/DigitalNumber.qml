import QtQuick 2.0

Item {
    id: panel
    property int value: 0
    property variant images: []
    property int digis: 1
    Row{
        anchors.fill: parent
        layoutDirection: Qt.RightToLeft
        Repeater{
            anchors.centerIn: parent
            model:digis
            Image
            {
                width:panel.width / digis
                height:panel.height
                source: images[Math.floor((value / Math.pow(10,index)))% 10]
            }
        }
    }
}
