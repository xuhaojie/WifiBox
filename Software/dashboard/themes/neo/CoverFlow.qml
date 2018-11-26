import QtQuick 2.0
PathView {
    id: pathView;
    interactive: true;
    pathItemCount: 4;
    preferredHighlightBegin: 0.375;
    preferredHighlightEnd: 0.625;
    highlightRangeMode: PathView.StrictlyEnforceRange;
    focus: true;
    Keys.onLeftPressed: decrementCurrentIndex();
    Keys.onRightPressed: incrementCurrentIndex();
    antialiasing: true;

    path:Path {
        startX: 0;
        startY: pathView.height/20 + pathView.height /6;
        PathAttribute { name: "zOrder"; value: 0 }
        PathAttribute { name: "itemAlpha"; value: 0.5 }
        PathAttribute { name: "itemScale"; value: 0.8 }
        PathAttribute { name: "itemRotation"; value: 90 }

        PathLine {
            x: pathView.width*0.375;
            y: pathView.height/10;
        }

        PathAttribute { name: "zOrder"; value: 10 }
        PathAttribute { name: "itemAlpha"; value: 1.0 }
        PathAttribute { name: "itemScale"; value: 2.0 }
        PathAttribute { name: "itemRotation"; value: 0 }

        PathLine {
            x: pathView.width;
            y: pathView.height/20 +  pathView.height /6;
        }
        PathAttribute { name: "zOrder"; value: 0 }
        PathAttribute { name: "itemAlpha"; value: 0.5 }
        PathAttribute { name: "itemScale"; value: 0.8 }
        PathAttribute { name: "itemRotation"; value: -75 }
    }


    delegate: Component {
        id: rectDelegate;
        Item {
            antialiasing: true;
            id: wrapper;
            z: PathView.zOrder;
            opacity: PathView.itemAlpha;
            scale: PathView.itemScale;
            property real rotationAngle: PathView.itemRotation
            Rectangle {
                antialiasing: true;
                width: pathView.width / 8;
                height: pathView.height / 3;
                smooth: true;
                clip:true
                color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
                border.width: 1;
                border.color: wrapper.PathView.isCurrentItem ? "lightgreen" : "lightgray";
                Image {
                    antialiasing: true;
                    anchors.fill: parent;
                    source: cover.length > 1 ? cover: "images/default-cover.png"
                }

                Text {
                    antialiasing: true;
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: pathView.height / 32;
                    text: title;
                    horizontalAlignment: Text.horizontalCenter
                    color: wrapper.PathView.isCurrentItem ? "darkblue" : "black";
                }

            }

            transform: Rotation { origin.x: 0; origin.y: 0; axis { x: 0; y: 1; z: 0 }  angle: rotationAngle}
        }
    }

    MouseArea {
        anchors.fill: pathView
        onClicked: {
            if(mouse.x < pathView.width / 3)
            {
                prev();
            } else if(mouse.x > pathView.width * 2 / 3){
                next();
            }
        }
    }


    function next() {
        var i = currentIndex + 1;
        if(i >= pathView.count){
            i= 0
        }
        pathView.currentIndex = i;
    }

    function prev() {
        var i = currentIndex - 1;
        if(i < 0){
            i= pathView.count - 1;
        }
        pathView.currentIndex = i;
    }

    function change(index) {
        var  count = pathView.count;
        if(index < 0){
            index = count - 1;
        }else if(index >= count){
            index = 0;
        }
        pathView.currentIndex = index;
    }
}
