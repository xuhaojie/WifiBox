import QtQuick 2.0

Rectangle {
    id: dialog
    property int life : 0
    property bool show : false
    property bool animation : false

    function fadeOut(obj, duration) {
        visibleChangeOut.target = obj;
        visibleChangeOut.duration = duration;
        opticyChangeOut.target = obj
        opticyChangeOut.duration = duration;
        scaleChangeOut.target = obj
        scaleChangeOut.duration = duration;

        visibleChangeOut.start();
        opticyChangeOut.start();
        scaleChangeOut.start()
    }

    function fadeIn(obj, duration) {
        visibleChangeIn.target = obj
        visibleChangeIn.duration = duration;
        opticyChangeIn.target = obj
        opticyChangeIn.duration = duration;
        scaleChangeIn.target = obj
        scaleChangeIn.duration = duration;

        visibleChangeIn.start();
        opticyChangeIn.start();
        scaleChangeIn.start()
    }

    onShowChanged: {
        if(show) {
            timer.stop()
            if(dialog.visible == false)
            {
                if(animation) fadeIn(dialog, 250)
                else dialog.visible = true;
            }

        } else {
            if(life > 0) timer.restart();
        }
    }

    Timer{
        id:timer
        interval: dialog.life
        repeat: false
        onTriggered: {
            if(animation) fadeOut(dialog, 250)
            else dialog.visible = false;
        }
    }

    NumberAnimation {
        id:visibleChangeIn
        from:0
        to: 1.0
        property: "visible"
    }

    NumberAnimation {
        id:opticyChangeIn
        from:0
        to: 1.0
        property: "opacity"
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id:scaleChangeIn
        from:0
        to:1
        property: "scale"
        easing.type: Easing.InOutQuad
    }
    NumberAnimation {
        id:visibleChangeOut
        from:1.0
        to: 0
        property: "visible"
    }
    NumberAnimation {
        id:opticyChangeOut
        to: 0
        property: "opacity"
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id:scaleChangeOut
        to:0
        property: "scale"
        easing.type: Easing.InOutQuad
    }
}
