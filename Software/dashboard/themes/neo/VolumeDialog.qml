import QtQuick 2.0

Item {
    id:volumeDialog
    Image{
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height / 2
        width: height
        source:"images/volume.svg"
    }

    Rectangle{
        id:progressBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: parent.height / 2
        //color: "#7F000000"
        color: "#7F00003F"
        border.color: "#FFFFFFFF"
        border.width: 3
        Rectangle{
            x:0
            y:0
            width: car.amplifierVolume / 30 * parent.width
            height: parent.height
            color:"#0081d6"
            border.width: 3
            border.color: "#7FFFFFFF"
        }
        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            color:"white"
            font.pixelSize:height*0.8
            text: car.amplifierVolume
        }
    }
}
