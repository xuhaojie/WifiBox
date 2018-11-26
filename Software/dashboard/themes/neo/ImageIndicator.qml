//Import the declarative plugins
import QtQuick 2.11

//Implementation of the Button control.
Image {
    id: indicator
    property int value: 0
    property variant images: []
    signal clicked
    source : images[0]
    onValueChanged: {
        source = images[value]
    }
/*
    Component.onCompleted: {
        source= images[0]
    }
*/
    fillMode: Image.PreserveAspectFit
    MouseArea{
        anchors.fill:parent
        onClicked: { indicator.clicked();}
    }
}
