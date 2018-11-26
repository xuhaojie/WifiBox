import QtQuick 2.0

Item {

    ImageButton {
        anchors.centerIn: parent
        width:parent.width / 4
        height:parent.height / 4
        normalImage: "images/exit.png"
        onClicked: {
            Qt.quit();
        }
    }
}
