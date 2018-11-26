import QtQuick 2.0
import car.autopard.com 1.0
Item {
    Text {
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        color:"white"
        font.pixelSize:height*0.8

        text: (car.radioBand == Car.Band_AM) ? ("AM " + car.radioFrequency.toFixed(1) + " KHz" ) : ("FM " + car.radioFrequency.toFixed(1) + " MHz")

    }
}

