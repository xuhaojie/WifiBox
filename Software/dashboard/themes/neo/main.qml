import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import car.autopard.com 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.11
//import dataModel 1.0
import car.autopard.com 1.0
import circularProgress.autopard.com 1.0
import QtQuick.Particles 2.0


Rectangle {
    id: win
    anchors.fill: parent
    width: 1920
    height: 1080
    visible: true
    focus: true
    color:"black"
    function prevView(){
        pageSwitcher.prevView();
        appState.set("App.CurrentView", pageSwitcher.currentPageIndex)
    }
    function nextView(){
        pageSwitcher.nextView();
        appState.set("App.CurrentView", pageSwitcher.currentPageIndex)
    }
    Keys.enabled: true;
    //处理按键的ESC消息
    Keys.onPressed: {
        switch(event.key){
        case Qt.Key_Escape:
            Qt.quit();
            break;
        case Qt.Key_Left:
        case Qt.Key_PageUp:
            prevView();
            break;
        case Qt.Key_Right:
        case Qt.Key_PageDown:
            nextView();
            break;
        case Qt.Key_MediaPrevious:
            mediaPage.prev();
            break;
        case Qt.Key_MediaNext:
            mediaPage.next(true);
            break;
        case Qt.Key_MediaTogglePlayPause:
            onClicked: mediaPage.playPause()
            break;
        case Qt.Key_Enter:
        case Qt.Key_Home:
            pageSwitcher.switchTo(0);
            break;
        default:
            return;
        }
    }


/*
    LyricModel {
        id: lm
        onCurrentIndexChanged: {
            lyric.currentIndex = currentIndex;
        }
    }
*/

    TopPanel {
        id: topPanel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height / 9
    }

    PageSwitcher {
        id: pageSwitcher
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: topPanel.bottom
        height: parent.height * 6 / 9
        //pages: [homePage, mediaPage, informationPage, controlPage, setupPage, lanuchPage, calendarPage, weatherPage]
        pages: [dashboardPage, mediaPage, informationPage, setupPage,calendarPage, weatherPage, lanuchPage]
        layer.enabled: true
        layer.smooth: true
        Rectangle {
            id: root
            x:0
            y:0
            width: parent.width
            height: parent.height
            color: "black"

            ParticleSystem {
                id: particles
                anchors.fill: parent

                ImageParticle {                       // 这次我们在系统中创建了2种图像粒子，并进行分组以用在不同的位置上
                    id: smoke
                    system: particles
                    anchors.fill: parent
                    groups: ["A", "B"]
                    source: "qrc:///particleresources/glowdot.png"
                    colorVariation: 0
                    color: "#00111111"                // 灰色
                }
                ImageParticle {
                    id: flame
                    anchors.fill: parent
                    system: particles
                    groups: ["C", "D"]
                    source: "qrc:///particleresources/glowdot.png"
                    colorVariation: 0.1
                    color: "#001fcfff"                // 橘红
                }

                Emitter {                            // 我们先取C组橘红粒子来创建底部的火焰
                    id: fire
                    system: particles
                    group: "C"

                    y: parent.height
                    width: parent.width

                    emitRate: 150
                    lifeSpan: 3500

                    acceleration: PointDirection {y: -17; xVariation: 3 }  // 使粒子向上漂移，并能够轻微地左右摆动
                    velocity: PointDirection { xVariation: 3}

                    size: 24
                    sizeVariation: 8
                    endSize: 4
                }

                TrailEmitter {                       // TrailEmitter类似Emitter，但是用来创建跟随粒子
                    id: fireSmoke
                    group: "B"                       // 本身粒子种类
                    system: particles
                    follow: "C"                      // 跟随粒子种类
                    width: root.width
                    height: root.height - 68         // 使下方火焰区域内不会出现烟雾

                    emitRatePerParticle: 1           // 跟随粒子发射的比率
                    lifeSpan: 2000

                    velocity: PointDirection {y:-17*6; yVariation: -17; xVariation: 3}
                    acceleration: PointDirection {xVariation: 3}

                    size: 36
                    sizeVariation: 8
                    endSize: 16
                }

                TrailEmitter {               // 串起的火苗
                    id: fireballFlame
                    anchors.fill: parent
                    system: particles
                    group: "D"
                    follow: "E"

                    emitRatePerParticle: 120  // 由于这里的跟随粒子没有定义速度与加速度，因此在出现后就被固定了。但我们依然可以靠产生和消逝实现动画
                    lifeSpan: 180             // 因此这里的生命周期特别短，如果要实现一长条火焰，可以增大这个数值
                    emitWidth: TrailEmitter.ParticleSize
                    emitHeight: TrailEmitter.ParticleSize
                    emitShape: EllipseShape{}   // 设置跟随区域

                    size: 16
                    sizeVariation: 4
                    endSize: 4
                }

                TrailEmitter {
                    id: fireballSmoke
                    anchors.fill: parent
                    system: particles
                    group: "A"
                    follow: "E"

                    emitRatePerParticle: 64
                    lifeSpan: 2400                         // 由于烟雾需要有自己的运动轨迹，因此生命周期较火苗更长
                    emitWidth: TrailEmitter.ParticleSize
                    emitHeight: TrailEmitter.ParticleSize
                    emitShape: EllipseShape{}

                    velocity: PointDirection {yVariation: 16; xVariation: 16}  // 刚产生的烟雾向下运行，随之慢慢向上升腾
                    acceleration: PointDirection {y: -16}

                    size: 24
                    sizeVariation: 8
                    endSize: 8
                }

                Emitter {                       // 注意这个Emitter所用的例子组"E"是不存在的，所以实际上它只是一个引导A和D的框架。如果想要清楚地看出这段代码的工作状态，大家可以自己创建一个绿色的图像粒子，并命名群组为E。
                    id: balls
                    system: particles
                    group: "E"

                    y: parent.height
                    width: parent.width

                    emitRate: 1
                    lifeSpan: 7000

                    velocity: PointDirection {y:-27*4*2; xVariation: 6*6}    // 向上的速度以及向下的加速度
                    acceleration: PointDirection {y: 27*2; xVariation: 6*6}  // 使火焰得以腾起，然后下落消失

                    size: 8
                    sizeVariation: 4
                }

                Turbulence {                                // 最后，为烟雾加上一点气流效果，就像它被风吹着一样，这样带来更好的效果
                    anchors.fill: parent
                    groups: ["A","B"]
                    strength: 32
                    system: particles
                }
            }
        }



        Dashboard {
            id: dashboardPage
            x:0
            y:0
            width: parent.width
            height: parent.height
            visible:true
        }

        CarInformation {
            id: informationPage
            x:0
            y:0
            width: parent.width
            height: parent.height
            visible: false
        }

        CarControl {
            id: controlPage
            x:0
            y:0
            width: parent.width
            height: parent.height
            visible:false
         }

        MediaPage {
            id: mediaPage
            x:0
            y:0
            width: parent.width
            height: parent.height
            visible:false
        }

        Setup {
            id: setupPage
            x:0
            y:0
            width: parent.width
            height: parent.height
            visible:false
        }

        LanuchPage {
            id: lanuchPage
            x:0
            y:0
            width: parent.width
            height: parent.height
            visible: false
        }

        CalendarPage{
            id:calendarPage
            anchors.top: topPanel.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: win.width / 2
            height: win.height / 2
            visible:false
            z:999
        }

        WeatherPage {
            id:weatherPage
            anchors.top: topPanel.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: win.width / 2
            height: win.height / 2
            visible:false
            z:10001
        }
    }

    ShaderEffect {
        id: shadow
        anchors.left: pageSwitcher.left
        anchors.right: pageSwitcher.right
        anchors.top: pageSwitcher.bottom
        anchors.bottom: parent.bottom

        property variant source: pageSwitcher;
        property size sourceSize: Qt.size(1 / pageSwitcher.width, 1 / pageSwitcher.height);

        fragmentShader: "
            varying highp vec2 qt_TexCoord0;
            uniform lowp sampler2D source;
            uniform lowp vec2 sourceSize;
            uniform lowp float qt_Opacity;
            void main() {
                lowp vec2 tc = qt_TexCoord0 * vec2(1, -1) + vec2(0, 1);
                lowp vec4 col = 0.25 * (texture2D(source, tc + sourceSize)
                                        + texture2D(source, tc- sourceSize)
                                        + texture2D(source, tc + sourceSize * vec2(1, -1))
                                        + texture2D(source, tc + sourceSize * vec2(-1, 1))
                                       );
                gl_FragColor = col * qt_Opacity * (1.0 - qt_TexCoord0.y) * 0.2;
            }"

        SinglelineLyric{
            id:singleLineLyric
    //        visible: false
            anchors.left:parent.left
            anchors.top: parent.top
            width: parent.width
            height:parent.height / 3

            progress: mediaPage.lineProgress
            text: lyricModel.currentText
        }

    }

    Image {
        id: bottomPanel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: parent.height * 2   / 9
        //color: "blue"
        source: "images/bottom-panel.png"

        Item{
            width:parent.height / 2
            height:parent.height / 2
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            Image {
                anchors.centerIn: parent
                width:parent.height
                height:parent.height
                source: "images/prev-view.svg"
                MouseArea{
                   anchors.fill: parent
                   onClicked:prevView()
                }
            }
        }


        Item{
            anchors.right: mediaProgress.left
            anchors.verticalCenter: mediaProgress.verticalCenter
            width:parent.width / 5
            height:parent.height / 2
            ImageButton {
                anchors.centerIn: parent
                width:parent.height
                height:parent.height
                normalImage: "images/prev.svg"
                onClicked: mediaPage.prev();
            }

        }

        CircularProgress{
            id: mediaProgress
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            width:parent.width / 5
            height:parent.height * 0.75
            basicColor: "#7f4682B4"
            startColor: "#ffffffff"
            stopColor: "#ffffffff"
            value: mediaPage.duration > 0 ? (100 * mediaPage.position / mediaPage.duration) : 0
            //backStrokeWidth: width / 40
            //frontStrokeWidth: width / 40
            ImageButton {
                id: playButton
                anchors.centerIn: parent
                width:parent.height*0.75
                height:parent.height*0.75
                normalImage: "images/play.svg"
                onClicked: mediaPage.playPause()
                Connections {
                    target: mediaPage.multimediaPlayer
                    onPlaybackStateChanged : {
                        if (mediaPage.playing) playButton.normalImage = "images/pause.svg"
                        else playButton.normalImage = "images/play.svg"
                    }
                }
            }
        }

        Item{
            anchors.left: mediaProgress.right
            anchors.verticalCenter: mediaProgress.verticalCenter
            width:parent.width / 5
            height:parent.height / 2
            ImageButton {
                anchors.centerIn: parent
                width:parent.height
                height:parent.height
                normalImage: "images/next.svg"
                onClicked: {
                    mediaPage.next(true);
                }
            }

        }

        Item{
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width:parent.height / 2
            height:parent.height / 2
            Image {
                anchors.centerIn: parent
                width:parent.height
                height:parent.height
                source: "images/next-view.svg"
                MouseArea{
                    anchors.fill: parent
                    onClicked: nextView()
                }
            }
        }
    }


    Component.onCompleted: {
        var pageIndex = appState.get("App.CurrentView");
        pageSwitcher.switchTo(pageIndex);
    }

    AutoHideDialog
    {
        id: radioDialog
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width / 2
        height: parent.height / 8
        visible:false
        z:10001
        animation: true
        property bool initialized: false
        life: 1000
        radius: 10
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#7f00001f" }
            GradientStop { position: 0.25; color: "#ff00003f" }
            GradientStop { position: 0.75; color: "#ff00003f" }
            GradientStop { position: 1.0; color: "#7f00001f" }
        }
        border.color: "#7FFFFFFF"
        border.width: 3
        Connections{
            target: car
            onRadioFrequencyChanged:{
                if(!radioDialog.initialized){
                    radioDialog.initialized = true
                }else{
                    radioDialog.show = true
                    radioDialog.show = false
                }
            }
        }

       // visible: car.alarmState > 0 ? true : false
        RadioDialog{
            anchors.fill: parent
        }
    }

    AutoHideDialog
    {
        id: volumeDialog
        anchors.centerIn: parent
        width: parent.width / 3
        height: parent.height / 4
        visible: false
        z: 10001
        animation: true
        property bool initialized: false
        life: 1000
        radius: 10
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#7f00001f" }
            GradientStop { position: 0.25; color: "#ff00003f" }
            GradientStop { position: 0.75; color: "#ff00003f" }
            GradientStop { position: 1.0; color: "#7f00001f" }
        }
        border.color: "#7F7F7F7F"
        border.width: 5
        color: "#00000000"
        Connections{
            target: car
            onAmplifierVolumeChanged:{
                if(!volumeDialog.initialized){
                    volumeDialog.initialized = true
                }else{
                    volumeDialog.show = true
                    volumeDialog.show = false
                }
            }
        }

       // visible: car.alarmState > 0 ? true : false
        VolumeDialog{
            //anchors.fill: parent
            anchors.centerIn: parent
            width: parent.width*0.8
            height: parent.height*0.8
        }
    }

    AutoHideDialog
    {
        id: lampDialog
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: win.width / 2
        height: win.height / 8
        z:10000
        life: 1000
        animation: true
        visible:false
        radius: 10
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#7F000000" }
            GradientStop { position: 0.25; color: "#FF000000" }
            GradientStop { position: 0.75; color: "#FF000000" }
            GradientStop { position: 1.0; color: "#7F000000" }
        }
        border.color: "#7FFFFFFF"
        border.width: 3
        Connections{
            target: car
            onLampStateChanged:{
                if(car.lampState > 0) {
                    lampDialog.show = true
                    lampDialog.show = false
                }
            }
        }

        LampPanel{
            anchors.fill: parent
        }
    }

    AutoHideDialog
    {
        id: alarmDialog
        anchors.top: lampDialog.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: win.width / 2
        height: win.height / 8
        visible:false
        z:10002
        animation: true
        life: 2000
        radius: 10
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#7f00001f" }
            GradientStop { position: 0.25; color: "#ff00003f" }
            GradientStop { position: 0.75; color: "#ff00003f" }
            GradientStop { position: 1.0; color: "#7f00001f" }
        }
        border.color: "#7FFFFF7F"
        border.width: 3

        Connections{
            target: car
            onAlarmStateChanged:{
                if(car.alarmState > 0){
                    alarmDialog.show = true
                    alarmDialog.show = false
                }
            }
        }

        AlarmPanel{
            anchors.fill: parent
        }
    }

    AutoHideDialog
    {
        id: doorDialog
        anchors.top: alarmDialog.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: win.width / 4
        height: win.height / 2
        visible:false
        z:10001
        animation: true
        life: 1000
        radius: 10
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#7f00001f" }
            GradientStop { position: 0.25; color: "#ff00003f" }
            GradientStop { position: 0.75; color: "#ff00003f" }
            GradientStop { position: 1.0; color: "#7f00001f" }
        }
        border.color: "#FF00FFFF"
        border.width: 3

        Connections{
            target: car
            onDoorAlarmChanged:{
                if(car.doorAlarm > 0) doorDialog.show = true
                else doorDialog.show = false
            }
        }

       // visible: car.alarmState > 0 ? true : false
        DoorPanel{
            anchors.fill: parent
        }
    }

}
