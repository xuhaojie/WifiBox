import QtQuick 2.0

Image {
    id:meter
    property alias background: meter.source;
    property alias foreground: bar.source;
    property real value: 0
    property real minValue : 0
    property real maxValue : 100
    property int  direction: 0
    clip: true
    Item{
        id:cliper
        x:0
        y:0
        width:meter.width
        height:meter.height
        clip: true
        Image{
            id:bar
            x:0
            y:0
            width:meter.width
            height:meter.height
            fillMode: Image.PreserveAspectFit
        }

    }
    function update(){
        var range = meter.maxValue - meter.minValue;
        var position = range > 0 ?  (value - minValue) / range : 0
        switch(direction){
        case 1: // up
            position = 1.0 - position;
            cliper.y = position * meter.height
            bar.y = -position * meter.height
            cliper.height = meter.height
            cliper.width = meter.width
            break;
        case 3: // down
            cliper.height = position * meter.height
            cliper.width = meter.width
            break;
        case 2: // left
            position = 1.0 - position;
            cliper.x = position * meter.height
            bar.x = -position * meter.height
            cliper.height = meter.height
            cliper.width = meter.width
            break;
        default: // right
            cliper.height = meter.height
            cliper.width = position * meter.width
            break;
        }
    }
    onValueChanged: update()
    Component.onCompleted: {
        update();
    }
}


/*
    ProgressIndicator{
        width: 128
        height: 128
        background: "images/air-bag-0.png"
        foreground: "images/air-bag-1.png"
        direction: 2
        minValue: 0
        maxValue: 100
        value: 50
    }
*/
