import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.LocalStorage 2.0
import QtQuick.Controls.Styles 1.1
import QtQuick 2.11
import QtQuick.Controls 2.0
import QtMultimedia 5.11
import QtGraphicalEffects 1.0
import dataModel 1.0
import car.autopard.com 1.0

// Dashboards are typically in a landscape orientation, so we need to ensure
// our height is never greater than our width.
Item {
    id: player
    anchors.fill: parent
    clip:true
    property string mediaTitle: mediaPlayer.metaData.title !== undefined ? mediaPlayer.metaData.title : ""
    property int loopMode: 0
    property int shuffleMode: 0
    property bool playing: false
    property real progress: 0.0
    property real lineProgress: 0
    property alias position: mediaPlayer.position
    property alias duration: mediaPlayer.duration
    property bool fullScreen: false
    property string title: "未播放"
    property MediaPlayer  multimediaPlayer: mediaPlayer

    function getTimeString(msTime)
    {
        var time = new Date();
        time.setTime(msTime); //转换成时间格式
        var timeString = Qt.formatTime(time,"mm:ss");
        if(msTime > 3600000)
        {
            var hour = Math.floor(msTime / 3600000);
            timeString =  hour.toString()+ ":" + timeString;
        }
        return timeString;
   }

    function changeCover(index) {
        if(index>=0){
            var cover = collectionModel.getCover(index);
            if(cover.length < 1) cover = "images/default-cover.png"
            cover.rotation = 0;
            coverAnimator.from = 0;
            coverAnimator.to = 360;
            coverAnimator.running = false;
            //coverAnimator.restart();
            collectionCover.source = cover
            collectionLabel.text = collectionModel.getTitle(index);
        }
    }

    function play(index) {
        player.title =  playlistModel.getTitle(index)
        timerCollectionPlay.stop();
        playlist.currentIndex = index;
        mediaPlayer.stop();
        mediaPlayer.source = "file://" + playlistModel.getFile(index);
        console.log(mediaPlayer.source);
        mediaPlayer.play();
        lyricModel.search(mediaPlayer.source);
        coverAnimator.start();
        timerLyric.start()
        appState.set("Player.PlaylistIndex",index);
        appState.set("Player.Playing",true);
    }

    function playPause() {
        if(mediaPlayer.status == MediaPlayer.NoMedia){
            var index = playlist.currentIndex
            if(-1 === index) index = 0;
            play(index);
        } else {
            if (mediaPlayer.playbackState === MediaPlayer.PlayingState) {
                mediaPlayer.pause();
                timerLyric.stop()
                coverAnimator.running = false;
                coverAnimator.from = cover.rotation;
                coverAnimator.to = coverAnimator.from + 360;
                appState.set("Player.Playing",false);
            } else {
                mediaPlayer.play();
                timerLyric.start()
                coverAnimator.running = true;
                appState.set("Player.Playing",true);
            }
        }
    }

    function getPrev(current, count) {
        return shuffleMode ?  Math.random()*(count+1) - 1 : current - 1;
    }

    function prev() {
        var count = playlist.count;
        var index = getPrev(playlist.currentIndex,count);
        switch (loopMode) {
        case 0: // noloopsetting
            if(index <= 0) prevCollection();
            else play(index);
            break;
        case 1: // loopCollection
            if(index < 0) prevCollection();
            else play(index);
            break;
        case 2: // loopCollection
            if(index >= count) index = 0;
            play(index);
            break;
        case 3: // loopOne
            index = playlist.currentIndex;
            if(index >= 0) play(index);
            break;
        }
    }

    function getNext(current, count) {
        return shuffleMode ? (Math.random()*count+1) + 1 : current + 1;
    }

    function next(force) {
        var count = playlist.count;
        var index = getNext(playlist.currentIndex,count);

        switch (loopMode){
        case 0: // noloop
            if(index >= count) nextCollection(force);
            else play(index);
            break;
        case 1:  // loopAll
            if(index >= count) nextCollection();
            else play(index);
            break;
        case 2: // loopCollection
            if(index >= count) index = 0;
            play(index);
            break;
        case 3: // loopOne
            index = playlist.currentIndex;
            if(index >=0) play(index);
            break;
        }
    }

    function prevCollection() {
        var count = collections.count;
        var index = getPrev(collections.currentIndex, count)
        if(index < 0) index = count - 1;
        collections.change(index);
        timerCollectionPlay.restart();
    }

    function nextCollection(force) {
        var count = collections.count;
        var index = getNext(collections.currentIndex, count)
        if(index >= count){
            if(1 == loopMode || force !== undefined) index = 0;
            else{
                setFullScreen(false);
                return
            }
        }
        collections.change(index);
        timerCollectionPlay.restart();
    }

    function changeCollection() {
        var coverIndex = collections.currentIndex;
        changeCover(coverIndex);
        var cid = collectionModel.getID(coverIndex);
        playlistModel.changeCollection(cid);
        appState.set("Player.CollectionIndex",coverIndex);
        playlist.currentIndex = -1;
    }
    function getRootView() {
        var p = videoWindow;
        while(p != undefined){
            if(p.parent)  p = p.parent;
            else return p.children[0];
        }
    }
    function setFullScreen(fullScreen){
        if(fullScreen === true){
            var rootView = getRootView();
            if(videoWindow.parent !== rootView) videoWindow.parent = rootView;
        } else {
            videoWindow.parent = coverArea;
        }
    }

    onFullScreenChanged: {
        setFullScreen(fullScreen)
    }

    Component.onCompleted: {
        var collectionIndex = appState.get("Player.CollectionIndex");
        if(collectionIndex !== undefined){
            collections.currentIndex = collectionIndex;
            changeCover(collectionIndex);
            collectionLabel.text = collectionModel.getTitle(collectionIndex);
        }
        var playlistIndex = appState.get("Player.PlaylistIndex");
        if(playlistIndex !== undefined) playlist.currentIndex = playlistIndex;

        var shuffle = appState.get("Player.Shuffle");
        if(shuffle !== undefined) player.shuffleMode = shuffle;

        var loop = appState.get("Player.Loop");
        if(loop !== undefined) player.loopMode = loop;
        timerCollectionPlay.stop()
        var lyricFolder = appSetting.get("LyricPath");
        if (lyricFolder.length > 0){
            lyricModel.setLyricPath(lyricFolder);
        }

    }

    Timer{
        id: timerCollectionPlay
        interval: 1000
        repeat: false
        onTriggered:{
             player.play(0);
        }
    }

    Timer{
        id: timerLyric
        interval: 200
        repeat: true
        running:false
        onTriggered:{
            var value = mediaPlayer.position
            lyricModel.seek(value)
            var index= lyricModel.currentIndex //lyricModel.getIndex(value);
            player.lineProgress = lyricModel.getPercent(value);
            singleLineLyric.progress = player.lineProgress

        }
    }

    MediaPlayer {
        id: mediaPlayer
        autoLoad: true
        autoPlay: true
        property string innerTitle: mediaPlayer.metaData.title === undefined ? "" : mediaPlayer.metaData.title

        onInnerTitleChanged: {
            var artist = mediaPlayer.metaData.contributingArtist !== undefined ?  mediaPlayer.metaData.contributingArtist : mediaPlayer.metaData.albumArtist
            if(artist === undefined){
                artist = mediaPlayer.metaData.author !== undefined ? mediaPlayer.metaData.author : undefined
            }
            player.title = artist !== undefined ? artist + " - " + innerTitle : innerTitle
            notificationClient.notification = player.title
        }

        onPlaybackStateChanged: {
            player.playing =  (mediaPlayer.playbackState === MediaPlayer.PlayingState);
        }

    }


    Item  {
        id: playlistArea
        x:0
        y:0
        width:parent.width / 2
        anchors.top:parent.top
        anchors.bottom: parent.bottom
        height:parent.height
        clip: true
        Behavior on x {PropertyAnimation{duration:250}}

        CoverFlow {
            id:collections
            x:0
            y:0
            width:parent.width
            height:parent.height / 3
            visible: true;
            interactive: true;
            model: collectionModel;
        }

        Connections{
            target: collections
            onCurrentIndexChanged: {
                changeCollection();
                timerCollectionPlay.restart();
            }
        }

        Text{
            id:collectionLabel
            anchors.bottom: collections.bottom
            anchors.horizontalCenter: collections.horizontalCenter
            color:"#073acf";
            topPadding: 2;
            leftPadding: 4;
            fontSizeMode: Text.Fit;
            horizontalAlignment: Text.horizontalCenter
            verticalAlignment: Text.Top
            minimumPixelSize: 12;
            font.pixelSize: Math.round(collections.height / 8)
        }

        ListView {
            id: playlist
            anchors.top: collections.bottom
            width: playlistArea.width;
            height: playlistArea.height * 2 / 3;
            clip: true
            highlightMoveDuration: 250
            highlightResizeDuration: 250
            highlight: Rectangle { color: "transparent"; border.color: "lightblue"; border.width: 2; }
            model: playlistModel;
            focus: true
            delegate: Component {
                id:listdelegate
                Item{
                    id:delegateitem
                    width: playlist.width
                    height:Math.round(playlist.height / 10)
                    Text{

                        id: titleText;
                        text:title;
                        color:"#7f7f7f";
                        //topPadding: 2
                        verticalAlignment: Text.Center
                        leftPadding: 4
                        fontSizeMode: Text.Fit;
                        font.pixelSize: Math.round(delegateitem.height * 0.75)
                    }

                    states: State {
                        name: "Current"
                        when: delegateitem.ListView.isCurrentItem
                        //PropertyChanges { target: artistText; color:"#00ffff";}
                        PropertyChanges { target: titleText;  color:"#ffffff";}
                    }

                    MouseArea {
                        anchors.fill: parent;
                        onClicked: {
                            player.play(index)
                        }
                    }
                }
            }
            Connections {
                target: mediaPlayer
                onStopped: {
                    if (mediaPlayer.status == MediaPlayer.EndOfMedia) {
                        coverAnimator.running = false;
                        player.next();
                    }
                }
            }
        }
    }

    Item {
        id:musicArea
        anchors.left: playlistArea.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: player.width / 2
        clip:true
        function toggleMusicArea(){
            if(musicArea.width < player.width)
            {
                 //musicArea.anchors.left = player.left
                 //musicArea.anchors.top = player.top
                 musicArea.width =  player.width
                 musicArea.height = player.height
                playlistArea.x = -player.width/2
            } else {
                 //musicArea.anchors.left = playlistArea.right
                 //musicArea.anchors.top = player.top
                 musicArea.width =  player.width / 2
                 musicArea.height = player.height
                playlistArea.x = 0
            }
        }

        Item {
            id: coverArea
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: parent.height *3 /  4

            MouseArea{
               anchors.fill: parent
               onClicked:{
                   if(multiLineLyric.visible){
                       multiLineLyric.visible = false;
                       cover.visible = true
                   }else{
                       multiLineLyric.visible = true;
                       cover.visible = false
                   }
               }
            }

            RotationAnimator {
                id: coverAnimator
                target: cover
                from: 0
                to: 360
                duration: 30000
                loops: Animation.Infinite
                running: false
            }

            Rectangle{
                id: collectionCoverRect
                anchors.fill: parent
                color: "white"
                visible: false

                Image {
                    id: collectionCover
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: "images/default-cover.png"
                    sourceSize: Qt.size(parent.width, parent.height)
                    smooth: true
                }
            }

            Image {
                id: coverMask
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "images/cd.png"
                sourceSize: Qt.size(parent.width, parent.height)
                smooth: true
                visible: false
            }

            OpacityMask {
                id: cover
                anchors.fill: parent
                source: collectionCoverRect
                maskSource: coverMask
            }

            MultilineLyric {
                id: multiLineLyric
                visible: false
                anchors.left: coverArea.left
                anchors.top: coverArea.top
                anchors.bottom: coverArea.bottom
                width: coverArea.width
                clip: true
                pathItemCount: 9
                preferredHighlightBegin: 0.5;
                preferredHighlightEnd: 0.5;
                //highlight: Rectangle { color: "transparent"; border.color: "lightblue"; border.width: 2; }
                interactive: false
                currentIndex: lyricModel.currentIndex
                model:lyricModel
            }

            Rectangle {
                id: videoWindow
                anchors.fill: parent
                //show: mediaPlayer.hasVideo
                visible: mediaPlayer.hasVideo
                color: "black"
                VideoOutput {
                    id: videoOutput
                    anchors.fill: parent
                    source: mediaPlayer
                }

                MouseArea
                {
                   anchors.fill: parent
                   onClicked: {
                       if(mediaPlayer.playbackState == MediaPlayer.PlayingState){
                           player.fullScreen = !player.fullScreen
                       }
                   }
                }
            }
        }

        Item{
            id:progressArea
            anchors.left: coverArea.left
            anchors.right:coverArea.right
            anchors.top:coverArea.bottom
            height: parent.height*0.125
            //anchors.bottom:controlArea.top

            Slider {
                id: progressSlider
                anchors.bottom: progressArea.bottom
                anchors.left: progressArea.left
                width :progressArea.width
                height: progressArea.height*0.5
                to: mediaPlayer.duration
                property bool sync: false

                background: Rectangle {
                    x: progressSlider.leftPadding
                    y: progressSlider.topPadding + progressSlider.availableHeight / 2 - height / 2
                    implicitWidth: 200
                    implicitHeight: 6
                    width: progressSlider.availableWidth
                    height: implicitHeight
                    radius: 2
                    color: "#bdbebf"

                    Rectangle {
                        width: progressSlider.visualPosition * parent.width
                        height: parent.height
                        color: mediaPlayer.playing ? "#21be2f" : "#61be2b"
                        radius: 3
                    }
                }
        /*
                handle: Rectangle {
                    x: progressSlider.leftPadding + progressSlider.visualPosition * (progressSlider.availableWidth - width)
                    y: progressSlider.topPadding + progressSlider.availableHeight / 2 - height / 2
                    implicitWidth: progressSlider.width / 24
                    implicitHeight: progressSlider.width / 24
                    radius: progressSlider.width / 12
                    color: progressSlider.pressed ? "#f0f0f0" : "#f6f6f6"
                    border.color: "#bdbebf"
                }
        */

                Connections{
                    target: mediaPlayer
                    onPositionChanged:{
                        progressSlider.sync = true;
                        var value = mediaPlayer.position
                        progressSlider.value = value
                        mediaPositionLable.text = getTimeString(value);
                        lyricModel.seek(value);
                        progressSlider.sync = false;
                    }
                }

                onValueChanged: {
                    if(mediaPlayer.seekable && !sync) {
                        mediaPositionLable.text = getTimeString(value);
                       /////// lyricModel.findIndex(value);
                        mediaPlayer.seek(value);
                    }

                }
            }

            Text{
                id: mediaPositionLable
                anchors.top: progressArea.top
                anchors.left: progressArea.left
                text: "00:00";
                color: "white"
                //fontSizeMode: Text.VerticalFit;
                minimumPixelSize: 12;
                font.pixelSize: Math.round(progressArea.height / 3)
            }

            Text{
                id: mediaDurationLable
                anchors.top: progressArea.top
                anchors.right: progressArea.right
                text: getTimeString(mediaPlayer.duration);
                color: "white"
                //fontSizeMode: Text.VerticalFit;
                minimumPixelSize: 12;
                font.pixelSize: Math.round(progressArea.height / 3)

            }
        }

        Item
        {
            id:controlArea
            anchors.left: coverArea.left
            anchors.right: coverArea.right
            anchors.top: progressArea.bottom
            anchors.bottom: parent.bottom

            Row
            {
                id: mediaPanel
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                width:parent.width * 0.8
                height:parent.height * 0.8
                Item {
                    width: mediaPanel.width / 3
                    height: mediaPanel.height
                    ImageButton {
                        anchors.centerIn: parent
                        width: parent.width *0.8
                        height: parent.height *0.8
                        normalImage: playlistArea.x === 0 ? "images/left.png":"images/right.png"
                        onClicked: {
                            musicArea.toggleMusicArea();
                        }
                    }
                }
                //topPadding: mediaPanel.height / 12
                //bottomPadding: mediaPanel.height / 12

/*
                Item {
                    width: mediaPanel.width / 6
                    height: mediaPanel.height
                    ImageButton {
                        id: prevButton
                        anchors.centerIn: parent
                        width: parent.width *0.8
                        height: parent.height *0.8
                        normalImage: "images/prev.png"
                        onClicked: {
                            player.prev();
                        }
                    }
                }

                Item {
                    width: mediaPanel.width / 6
                    height: mediaPanel.height
                    ImageButton {
                        id: playButton
                        anchors.centerIn: parent
                        width: parent.width *0.8
                        height: parent.height *0.8
                        normalImage: "images/play.png"
                        onClicked: {
                            player.playPause()
                        }
                        Connections {
                            target: mediaPlayer
                            onPlaybackStateChanged : {
                                if (player.playing) playButton.normalImage = "images/pause.png"
                                else playButton.normalImage = "images/play.png"
                            }
                        }
                    }
                }

                Item {
                    width: mediaPanel.width / 6
                    height: mediaPanel.height
                    ImageButton {
                        id: nextButton
                        anchors.centerIn: parent
                        width: parent.width *0.8
                        height: parent.height *0.8
                        normalImage: "images/next.png"
                        onClicked: {
                            player.next(true);
                        }
                    }
                }
*/
                Item {
                    anchors.top: parent.top
                    width: mediaPanel.width / 3
                    height: mediaPanel.height
                    ImageIndicator {
                        anchors.centerIn: parent
                        width: parent.width * 0.8
                        height: parent.height *0.8
                        value:player.loopMode
                        images: ["images/loop_no.png","images/loop_all.png","images/loop_collection.png","images/loop_one.png"]

                        onClicked: {
                            var loop = player.loopMode + 1;
                            if( loop >= images.length) loop = 0
                            player.loopMode = loop
                            appState.set("Player.Loop",loop)
                        }
                    }
                }

                Item {
                    width: mediaPanel.width / 3
                    height: mediaPanel.height
                    ImageIndicator {
                        anchors.centerIn: parent
                        width: parent.width *0.8
                        height: parent.height *0.8
                        value: player.shuffleMode
                        images: ["images/shuffle_off.png" , "images/shuffle_on.png"]
                        onClicked: {
                            var shuffle = player.shuffleMode + 1;
                            if( shuffle >= images.length) shuffle = 0
                            player.shuffleMode = shuffle
                            appState.set("Player.Shuffle",shuffle)
                        }
                    }
                }
            }
        }

    }
/*
    SinglelineLyric{
        id:single
//        visible: false
        width: parent.width
        height:parent.height / 10
        anchors.bottom: parent.bottom
        progress: plyer.lineProgress
        text: lyricModel.currentText

    }
*/
}


