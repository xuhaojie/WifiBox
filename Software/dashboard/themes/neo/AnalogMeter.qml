import QtQuick 2.0

Image {
    id:meter
    property alias background: meter.source;
    property alias hand: hand.source;
    property real value: 0
    property real minValue : 0
    property real maxValue : 100
    property real startAngle : 0
    property real stopAngle : 360
    Image{
        id:hand
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }
    function update(){
        var valueRange = meter.maxValue - meter.minValue;
        var angleRange = stopAngle - startAngle;
        if(valueRange > 0) {
            var angle =  startAngle + (value - minValue) * angleRange / valueRange;
            if(angleRange >0){
                if(angle > stopAngle) angle = stopAngle
                else if(angle < startAngle) angle = startAngle
            } else {
                if(angle < stopAngle) angle = stopAngle
                else if(angle > startAngle) angle = startAngle
            }
            hand.rotation = angle
        }
    }
    onValueChanged: update()
    Component.onCompleted: {
        update();
    }
}
