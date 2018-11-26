import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id:lyric
    clip:true
    property real progress: 0
    property string text
    Text{
        id:lyricText
        text:lyric.text
        anchors.left : parent.left
        anchors.top : parent.top
        height:parent.height
        font.pixelSize: parent.height*0.8
        color: "gray"
    }

    Item{
        id:rect
        visible: false
        anchors.left : parent.left
        anchors.top : parent.top
        height:parent.height
        width:lyricText.width

        clip:true
        Rectangle{
            anchors.left : parent.left
            anchors.top : parent.top
            height:parent.height
            width:progress*lyricText.width
            //width:lyricText.width
            //color: "#0081d6"
            gradient: Gradient {
                GradientStop { position: 0.0; color: "red" }
                GradientStop { position: 0.67; color: "orange" }
                GradientStop { position: 1.0; color: "yellow" }
            }
        }
    }

    OpacityMask {
        id: cover
        anchors.left : parent.left
        anchors.top : parent.top
        height:parent.height
        width:lyricText.width
        clip:true
        source: rect
        maskSource: lyricText
    }
}
