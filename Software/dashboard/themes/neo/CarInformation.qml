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


import QtQuick 2.6
import QtQuick.Controls 2.0

// Dashboards are typically in a landscape orientation, so we need to ensure
// our height is never greater than our width.
Item {
    id: container
    x:0
    y:0
    width:1920
    height:980
    anchors.fill:parent
    AutoResize {
        fixedAspectRatio: true
        //accordingToX: true
    }

    Item{
        x:150
        y:260
        width:500
        height:400
        Item{
            x:0
            y:0
            width:500
            height:400
            Rectangle{
                x:16
                y:35
                width:468
                height:150
                radius: 10
                color: "transparent"
                border.color: "#7F003FF0"
                border.width:3
                Text{
                    x:32
                    y:40
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"统计里程:" + car.trip1Mileage
                }
                Text{
                    x:32
                    y:85
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"平均速度:" + Math.round(car.trip1Speed)
                }
                Text{
                    x:232
                    y:85
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"平均油耗:" + car.trip1OilWare.toFixed(1)
                }
            }
            Text{
                x:40
                y:18
                width:455
                height:55
                color:"#FF00FFFF"
                font.pixelSize:32
                text:"统计里程1"
            }

            Rectangle{
                x:16
                y:225
                width:468
                height:150
                radius: 10
                color: "transparent"
                border.color: "#7F003FF0"
                border.width:3
                Text{
                    x:32
                    y:40
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"统计里程:" + car.trip2Mileage
                }
                Text{
                    x:32
                    y:85
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"平均速度:" + Math.round(car.trip2Speed)
                }
                Text{
                    x:232
                    y:85
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"平均油耗:" + car.trip2OilWare.toFixed(1)
                }
            }
            Text{
                x:40
                y:208
                width:455
                height:55
                color:"#FF00FFFF"
                font.pixelSize:32
                text:"统计里程2"
            }

        }
    }

    Item{
        x:1370
        y:260
        width:500
        height:400
        Item{
            x:0
            y:0
            width:500
            height:400
            Rectangle{
                x:16
                y:35
                width:468
                height:150
                radius: 10
                color: "transparent"
                border.color: "#7F003FF0"
                border.width:3
                Text{
                    x:32
                    y:40
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"车架号:" + car.vin
                }


                Text{
                    x:32
                    y:85
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"电瓶电压:" + car.batteryVoltage.toFixed(1)
                }
                Text{
                    x:232
                    y:85
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"总里程:" + car.totalMileage
                }
            }
            Text{
                x:40
                y:18
                width:455
                height:55
                color:"#FF00FFFF"
                font.pixelSize:32
                text:"车辆信息"
            }

            Rectangle{
                x:16
                y:225
                width:468
                height:150
                radius: 10
                color: "transparent"
                border.color: "#7F003FF0"
                border.width:3
                Text{
                    x:32
                    y:40
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"输入电压:" + car.powerVoltage.toFixed(1)
                }
                Text{
                    x:232
                    y:40
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"芯片电压:" + car.chipVoltage.toFixed(1)
                }

                Text{
                    x:32
                    y:85
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"固件版本:1.00"
                }

                Text{
                    x:232
                    y:85
                    width:200
                    height:35
                    color:"#FFE9E9E9"
                    font.pixelSize:28
                    text:"芯片温度:" + car.chipTemperature.toFixed(1)
                }

            }
            Text{
                x:40
                y:208
                width:455
                height:55
                color:"#FF00FFFF"
                font.pixelSize:32
                text:"协议盒信息"
            }
        }
    }
}

