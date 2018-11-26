import QtQuick 2.7
import QtQuick.Controls 2.0

Item {
    id: pageSwitcher
    property Item currentPage: null
    property int animationDuration: 250
    property variant pages: []
    property int currentPageIndex: 0
    property bool changing:false;

    function nextView()
    {
        var index = currentPageIndex
        index++
        if(index >= pages.length)
        {
            index = 0;
        }
        switchTo(index)
    }

    function prevView()
    {
        var index = currentPageIndex
        index--
        if(index < 0)
        {
            index = pages.length - 1;
        }
        switchTo(index)
    }

    function fadeOut(obj, duration) {
        visibleChangeOut.target = obj;
        visibleChangeOut.duration = duration;
        opticyChangeOut.target = obj
        opticyChangeOut.duration = duration;
        yChangeOut.target = obj
        yChangeOut.duration = duration;
        scaleChangeOut.target = obj
        scaleChangeOut.duration = duration;

        visibleChangeOut.start();
        opticyChangeOut.start();
        yChangeOut.start()
        scaleChangeOut.start()
    }

    function fadeIn(obj, duration) {
        visibleChangeIn.target = obj
        visibleChangeIn.duration = duration;
        opticyChangeIn.target = obj
        opticyChangeIn.duration = duration;
        yChangeIn.target = obj
        yChangeIn.duration = duration;
        scaleChangeIn.target = obj
        scaleChangeIn.duration = duration;

        visibleChangeIn.start();
        opticyChangeIn.start();
        yChangeIn.start()
        scaleChangeIn.start()
    }

    function switchTo(index) {
        if(index <0 || index >= pages.length) return;
        if(currentPageIndex !== index && ! changing) {
            changing = true;
            var nextPage = pages[index];
            if(currentPageIndex >= 0) {
                var currentPage = pages[currentPageIndex];
                fadeOut(currentPage, animationDuration);
            }
            fadeIn(nextPage, animationDuration);
            currentPageIndex = index;
        }
    }

    NumberAnimation {
        id:visibleChangeIn
        from:0
        to: 1.0
        property: "visible"
        onStopped:
        {
            changing = false;
        }
    }

    NumberAnimation {
        id:opticyChangeIn
        from:0
        to: 1.0
        property: "opacity"
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id:yChangeIn
        from: -pageSwitcher.height
        to: 0
        property: "y"
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
        id:yChangeOut
        to: pageSwitcher.height
        property: "y"
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id:scaleChangeOut
        to:0
        property: "scale"
        easing.type: Easing.InOutQuad
    }
}
