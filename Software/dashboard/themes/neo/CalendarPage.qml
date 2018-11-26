import QtQuick 2.11
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4
import QtQuick 2.6
import QtQuick.Controls 2.0

import "ajax.js" as Ajax
Item{
    id: dialog

    Calendar {
        anchors.fill: parent
        locale: Qt.locale("zh_CN")
        //minimumDate: new Date(2017, 0, 1)
        //maximumDate: new Date(2018, 0, 1)
    }
}
