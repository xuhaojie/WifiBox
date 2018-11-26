import QtQuick 2.11
import QtQuick.Controls 2.0

Item
{
    id: mediaSetup
    property string audioFolder;
    property string videoFolder;
    property string lyricFolder;
    //color: "#343434"
    Grid{
        anchors.top: parent.top
        anchors.left : parent.left
        anchors.right : parent.right
        height: parent.height - 120;
        rows:3
        rowSpacing: 20;
        columns: 3
        columnSpacing: 40;

        Text{
            text: "Audio path"
            color: "white"
            font.pixelSize: mediaSetup.height/20
        }

        Text{
            text: audioFolder
            font.pixelSize: mediaSetup.height/20
            color: "white"
        }

        Button
        {
            id: btn_add
            anchors.right: mediaSetup.right
            height: mediaSetup.height / 20
            text: "Browse"
            onClicked:
            {
                audioFolderBrowser.folder = "file://" + audioFolder;
                audioFolderBrowser.show();
            }
            Connections {
                target: audioFolderBrowser
                onFolderSelected: {
                    var path = folder;
                    var prefix = "file://"
                    var pos = path.indexOf(prefix)
                    if(pos >= 0)
                    {
                        pos = prefix.length;
                        path = path.substring(pos)
                    }
                    mediaSetup.audioFolder = path;
                    appSetting.set("AudioPath",path.toString());
                }
            }
        }

        Text{
            text: "Video path"
            font.pixelSize: mediaSetup.height/20
            color: "white"
        }

        Text{
            color: "white"
            font.pixelSize: mediaSetup.height/20
            text: videoFolder
        }

        Button
        {
            id: videoBrowsepath
            anchors.right: mediaSetup.right
            text: "Browse"
            height: mediaSetup.height / 20
            onClicked:
            {
                videoFolderBrowser.folder = "file://" + videoFolder;
                videoFolderBrowser.show();
            }
            Connections {
                target: videoFolderBrowser
                onFolderSelected: {
                    var path = folder;
                    var prefix = "file://"
                    var pos = path.indexOf(prefix)
                    if(pos >= 0)
                    {
                        pos = prefix.length;
                        path = path.substring(pos)
                    }
                    mediaSetup.videoFolder = path;
                    appSetting.set("VideoPath",path.toString());
                }
            }
        }

        Text{
            text: "Lyric path"
            font.pixelSize: mediaSetup.height/20
            color: "white"
        }

        Text{
            color: "white"
            font.pixelSize: mediaSetup.height/20
            text: lyricFolder
        }

        Button
        {
            id: lyricBrowsepath
            anchors.right: mediaSetup.right
            text: "Browse"
            height: mediaSetup.height / 20
            onClicked:
            {
                lyricFolderBrowser.folder = "file://" + lyricFolder;
                lyricFolderBrowser.show();
            }
            Connections {
                target: lyricFolderBrowser
                onFolderSelected: {
                    var path = folder;
                    var prefix = "file://"
                    var pos = path.indexOf(prefix)
                    if(pos >= 0)
                    {
                        pos = prefix.length;
                        path = path.substring(pos)
                    }
                    mediaSetup.lyricFolder = path;
                    appSetting.set("LyricPath",path.toString());
                }
            }
        }

    }

    FolderBrowser {
        id: audioFolderBrowser
        anchors.fill:parent
        folder:"file:///"
    }

    FolderBrowser {
        id: videoFolderBrowser
        anchors.fill:parent
        folder:"file:///"
    }

    FolderBrowser {
        id: lyricFolderBrowser
        anchors.fill:parent
        folder:"file:///"
    }

    Component.onCompleted: {
        audioFolder = appSetting.get("AudioPath");
        if (audioFolder.length < 1){
            audioFolder = "files:///"
        }
        videoFolder = appSetting.get("VideoPath");
        if (videoFolder.length < 1){
            videoFolder = "files:///"
        }

        lyricFolder = appSetting.get("LyricPath");
        if (lyricFolder.length < 1){
            lyricFolder = "files:///"
        }
    }


}


