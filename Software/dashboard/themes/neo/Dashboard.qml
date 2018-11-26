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
import QtQuick 2.11
import QtQuick.Controls 2.0
import car.autopard.com 1.0
import circularProgress.autopard.com 1.0
import waveProgress.autopard.com 1.0
//text: qsTr( "Back" );

Item {
    id: homePage
    x:0
    y:0
    width:1920
    height:1080
    AutoResize {
        //fixedAspectRatio: true
        //accordingToX: true
    }

    /*
    SpriteSequence {
        id: sprite
        width: 64
        height: 64
        interpolate: false
        goalSprite: ""

        Sprite {
            name: "idle"
            source: "images/factory-idle.png"
            frameCount: 4
            frameDuration: 200
        }
    }
    */
    FontLoader { id: arialBlack; source:"qrc:/fonts/Arial Black.ttf" }

    WaveProgress{
        id: batteryMeter
        x: 0
        y: 440
        width: 240
        height: 240
        startColor: '#0f00ff00';
        stopColor: '#7f00ff00';
        strokeColor: '#7f4682B4';
        strokeWidth: width / 24;
        minValue: 0
        maxValue: 160
        targetValue: 10*car.batteryVoltage.toFixed(1)
        Text{
            id:voltageText
            anchors.centerIn: parent
            color:"#ffffff"
            text: car.batteryVoltage.toFixed(1)
            font.pixelSize:48
            horizontalAlignment: Text.AlignHCenter
            //<TextIndicator x="300" y="250" width="210" height="160" value-id="Car.Speed" default-value="---" font-size="150" font-name="Quartz Regular" text-align="3" text-color="#FF04DCFF"/>
        }
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:voltageText.bottom
            width: 64
            height: 64
            source: "images/battery-voltage.svg"
        }
    }

    WaveProgress{
        id: waterMeter
        x: 240
        y: 440
        width: 240
        height: 240
        startColor: '#0f0000ff';
        stopColor: '#7f0000ff';
        strokeColor: '#7f4682B4';
        strokeWidth: width / 24;
        minValue: 0
        maxValue: 120
        targetValue: car.waterTemperature
        Text{
            id:waterText
            anchors.centerIn: parent
            color:"#ffffff"
            text: car.waterTemperature
            font.pixelSize:48
            horizontalAlignment: Text.AlignHCenter
        }
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:waterText.bottom
            width: 64
            height: 64
            source: "images/water-temp.svg"
        }
    }

    CircularProgress{
        id: revMeter
        x: 60
        y: 60
        width: 360
        height: 360
        basicColor: "#3f4682B4"
        startColor: "blue"
        stopColor: "red"

        value: car.rev //car.waterTemperature
        minValue: 0
        maxValue: 7000
        strokeWidth: width / 10

        Text{
            id:revText
            anchors.centerIn: parent
            color:"#ffffff"
            text: car.rev
            font.pixelSize:72
            horizontalAlignment: Text.AlignHCenter
        }
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:revText.bottom
            width: 64
            height: 64
            source: "images/rev.svg"
        }
    }
/*
    CircularProgress{
        id: revMeter2
        x: 540
        y: 0
        width: 840
        height: 840
        basicColor: "#7f3f3f3f"
        startColor: "blue"
        stopColor: "red"
        startAngle: 115
        stopAngle: 230
        value: car.rev //car.waterTemperature
        minValue: 0
        maxValue: 7000
        //backStrokeWidth: width / 20
        //frontStrokeWidth: width / 20

    }
*/
    AnalogMeter {
        id: analogMeter
        x: 540
        y: 0
        width: 840
        height: 840
        fillMode: Image.PreserveAspectFit
        background: "images/meter-bg.svg"
        hand:"images/meter-hand.svg"
        value: car.rev
        maxValue: 7000
        startAngle: -115
        stopAngle: 115

        Image {
            id: logo
            x: 340
            y: 160
            width: 163
            height: 166
            source: "images/logo.png"
        }

        Text{
            id:speedText
            x:315
            y:320
            width:210
            height:160
            color:"#ffffff"
            text: Math.floor(car.speed).toString()
            font.pixelSize:150
            horizontalAlignment: Text.AlignHCenter
        }

        ImageIndicator {
            x:275
            y:480
            width:290
            height:65
            images: ["images/gear-0.svg" , "images/gear-1.svg", "images/gear-2.svg", "images/gear-3.svg", "images/gear-4.svg", "images/gear-5.svg"]
            value: car.gear
        }

        Text{
            property variant name_map: ["M","N"]
            x:390
            y:540
            width:48
            height:96
            text:name_map[car.gearMode]
            font.pixelSize:96
            font.family: arialBlack.name
            color: "#00ffff"
        }
    }


    CircularProgress{
        id: oilwareMeter
        x: 1500
        y: 60
        width: 360
        height: 360
        basicColor: "#3f4682B4"
        startColor: "blue"
        stopColor: "red"
        value: car.oilWare.toFixed(1)
        minValue: 0
        maxValue: 30
        strokeWidth: width / 10

        counterClockwise: true
        Text{
            id:oilwareMeterText
            anchors.centerIn: parent
            color:"#ffffff"
            text: car.oilWare.toFixed(1)
            font.pixelSize:72
            horizontalAlignment: Text.AlignHCenter
        }
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:oilwareMeterText.bottom
            width: 64
            height: 64
            source: "images/oil-ware.svg"
        }
    }

    WaveProgress{
        id: oilMeter
        x: 1440
        y: 440
        width: 240
        height: 240
        startColor: '#0fffff00';
        stopColor: '#7fffff00';
        strokeColor: '#7f4682B4';
        strokeWidth: width / 24;
        targetValue:car.fuelLevel
        Text{
            id:oilText
            anchors.centerIn: parent
            color:"#ffffff"
            text: car.fuelLevel.toString()
            font.pixelSize:48
            horizontalAlignment: Text.AlignHCenter
        }
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:oilText.bottom
            width: 64
            height: 64
            source: "images/fuel-level.svg"
        }
    }

    WaveProgress{
        id: temperatureMeter
        x: 1680
        y: 440
        width: 240
        height: 240
        startColor: '#0fff0000';
        stopColor: '#7fff0000';
        strokeColor: '#7f4682B4';
        strokeWidth: width / 24;
        targetValue:car.outsideTemperature
        minValue: -10
        maxValue: 50
        Text{
            id:temperatureText
            anchors.centerIn: parent
            color:"#ffffff"
            text: car.outsideTemperature
            font.pixelSize:48
            horizontalAlignment: Text.AlignHCenter
        }
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:temperatureText.bottom
            width: 64
            height: 64
            source: "images/air-temp.svg"
        }
    }



}


