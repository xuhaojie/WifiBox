/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.LocalStorage 2.0
import QtQuick.Dialogs 1.0

import QtQuick 2.6
import QtQuick.Controls 2.0

// Dashboards are typically in a landscape orientation, so we need to ensure
// our height is never greater than our width.

TabView {
    anchors.centerIn: parent
    id: setupPage
    tabPosition: Qt.BottomEdge
    style: TabViewStyle {
        frameOverlap: 1
        tab: Rectangle {
            //color: styleData.selected ? "steelblue" :"lightsteelblue"
            color: "transparent"
            border.color:  "steelblue"
            implicitWidth: text.width*1.2
            implicitHeight: text.height*1.2
            radius: 2
            Text {
                id: text
                anchors.centerIn: parent
                text: styleData.title
                font.pixelSize:setupPage.height /16
                color: styleData.selected ? "white" : "gray"
            }
        }
        //frame: Rectangle { color: "transparent"; border.color: "lightsteelblue"; border.width: 1 }
        frame: Item {}
    }

    Tab {
        title: "音响"
        AudioControl{
            anchors.fill: parent
        }
    }

    Tab {
        title: "车窗"
        WindowControl{
            anchors.fill: parent
        }
    }
    Tab {
        title: "后视镜"
        MirrorControl{
            anchors.fill: parent
        }
    }
    Tab {
        title: "继电器"
        RelayControl{
            anchors.fill: parent
        }
    }
    Tab {
        title: "座椅"
        SeatControl{
            anchors.fill: parent
        }
    }
    Tab {
        title: "空调"
    }
}


