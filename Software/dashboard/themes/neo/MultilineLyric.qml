import QtQuick 2.0

PathView {
    id: lyric
    //clip: true
    preferredHighlightBegin: 0.33
    preferredHighlightEnd: 0.33
    //highlight: Rectangle { color: "transparent"; border.color: "lightblue"; border.width: 2; }
    interactive: false

    pathItemCount: 4;
    highlightRangeMode: PathView.StrictlyEnforceRange;
    path:Path {
        startX: lyric.width/2;
        startY: 0;
        PathAttribute { name: "zOrder"; value: 0 }
        PathAttribute { name: "itemAlpha"; value: 0.5 }
        PathAttribute { name: "itemScale"; value: 0.8 }
        PathLine {
            x: lyric.width/2;
            y: lyric.height/3;
        }
        PathAttribute { name: "zOrder"; value: 10 }
        PathAttribute { name: "itemAlpha"; value: 1.0 }
        PathAttribute { name: "itemScale"; value: 1.0}

        PathLine {
            x: lyric.width/2;
            y: lyric.height;
        }
        PathAttribute { name: "zOrder"; value: 5 }
        PathAttribute { name: "itemAlpha"; value: 0.5 }
        PathAttribute { name: "itemScale"; value: 0.8 }
    }

    delegate: Component {
        id: rectDelegate;
        Item {
            id: wrapper;

            z: PathView.zOrder;
            opacity: PathView.itemAlpha;
            scale: PathView.itemScale;

            Text {
                id:lyricText
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                height:lyric.height / pathItemCount
                font.pixelSize: height * 0.8;
                //font.bold: parent.PathView.isCurrentItem
                text: textLine == undefined ? "" : textLine;
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: parent.PathView.isCurrentItem ? "#CFCFCF":"#7F7F7F"
            }
            Text {
                anchors.left : lyricText.left
                anchors.top : lyricText.top
                height: lyricText.height
                font.pixelSize: lyricText.font.pixelSize;
                //font.bold: lyric.font.bold
                verticalAlignment: Text.AlignVCenter
                text: lyricText.text;
                color: "#04DCFF"
                clip: true
                width: lyricText.width * mediaPage.lineProgress
                visible: parent.PathView.isCurrentItem
            }

            /*
            Text {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: lyric.height / 4;
                font.bold: parent.PathView.isCurrentIt
                text: textLine;
                horizontalAlignment: Text.AlignHCenter
                color: "#04DCFF"
                clip: true
                width:wrapper.width
            }
            */




            //transform: Rotation { origin.x: 0; origin.y: 0; axis { x: 0; y: 1; z: 0 }  angle: rotationAngle}
        }
    }
}
