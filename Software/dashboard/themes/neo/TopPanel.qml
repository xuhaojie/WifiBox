import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
//import "ajax.js" as Ajax

Item {
    id: topPanel
        Image {
            id: homeButton
            anchors.left: parent.left
            anchors.bottom:  parent.bottom
            width: parent.height
            height: parent.height
            source: "images/home.svg"
            MouseArea{
               anchors.fill: parent
               onClicked:{
                   pageSwitcher.switchTo(0);
                   appState.set("App.CurrentView", pageSwitcher.currentPageIndex)
               }
            }
        }

        Text {
            id:temperature;
            anchors.left:  homeButton.right
            width: parent.width / 8;
            height: parent.height
            //text: weatherPage.forecast[0].type + " " +  weatherPage.temperature + "℃"
            text: weatherPage.temperature + "℃"
            color:"#FFFFFF";
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.height*0.6
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    pageSwitcher.switchTo(5);
                    appState.set("App.CurrentView", pageSwitcher.currentPageIndex)
                }
            }
        }
/*
        Text {
            id:temperature;
            anchors.left:  parent.left
            width: parent.width / 8;
            height: parent.height
            text: weatherPage.city + " " + weatherPage.forecast[0].type + " " +  weatherPage.temperature + "℃"
            color:"#FFFFFF";
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.height*0.6
            MouseArea{
                anchors.fill: parent
                onClicked: { win.switchTo(weatherPage)}
            }
        }
*/
        Text {
            id:mediaInfo;
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            height: parent.heigh
            text:mediaPage.title;
//            textFormat: Text.PlainText
            color:"#00CFCF";
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.height*0.6
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    pageSwitcher.switchTo(1);
                    appState.set("App.CurrentView", pageSwitcher.currentPageIndex)
                }
            }
        }

        //显示
        Text{
           id: textDateTime
           anchors.right: parent.right
           width: parent.width / 8;
           height: parent.height
           text: currentDateTime();
           clip:true
           color:"#FFFFFF";
           horizontalAlignment: Text.AlignRight;
           verticalAlignment: Text.AlignVCenter
           font.pixelSize: parent.height*0.6

           MouseArea{
               anchors.fill: textDateTime
               onClicked:{
                   pageSwitcher.switchTo(4);
                   appState.set("App.CurrentView", pageSwitcher.currentPageIndex)
               }
           }

           //定时器
           Timer{
               id: timeTimer
               running: true
               interval: 3000 //间隔(单位毫秒):1000毫秒=1秒
               repeat: true
               onTriggered:{
                   textDateTime.text = currentDateTime()
               }
           }
        }

/*
    Rectangle{
        id:progressBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 3;
        //color: "#7F000000"
        color: "#001F1F"
        property int progressPos : 0
        Connections{
            target: mediaPage
            onPositionChanged: {
                progressBar.progressPos = mediaPage.duration > 0 ? (width * mediaPage.position / mediaPage.duration) : 0
            }
        }
        Rectangle{
            x:0
            y:0
            width: parent.progressPos
            height:parent.height
            color:"#007F7F"
        }
    }
*/
    //当前日期时间
    function currentDateTime(){
        return Qt.formatDateTime(new Date(), "hh:mm");
    }
/*
        function getWeather(ct){
           // 中华万年历的当天及预告天气接口（可用）
           Ajax.get("http://wthrcdn.etouch.cn/weather_mini?city=" + ct,
               function(result, json){
                   //{"desc":"OK","status":1000,"data":{"wendu":"22","ganmao":"风较大，较易发生感冒，注意防护。","forecast":[{"fengxiang":"北风","fengli":"5-6级","high":"高温 24℃","type":"晴","low":"低温 11℃","date":"3日星期六"},{"fengxiang":"北风","fengli":"4-5级","high":"高温 19℃","type":"晴","low":"低温 8℃","date":"4日星期日"},{"fengxiang":"无持续风向","fengli":"微风","high":"高温 21℃","type":"晴","low":"低温 9℃","date":"5日星期一"},{"fengxiang":"无持续风向","fengli":"微风","high":"高温 21℃","type":"多云","low":"低温 10℃","date":"6日星期二"},{"fengxiang":"无持续风向","fengli":"微风","high":"高温 24℃","type":"晴","low":"低温 12℃","date":"7日星期三"},{"fengxiang":"无持续风向","fengli":"微风","high":"高温 23℃","type":"晴","low":"低温 11℃","date":"8日星期四"}],"yesterday":{"fl":"微风","fx":"无持续风向","high":"高温 23℃","type":"晴","low":"低温 12℃","date":"2日星期五"},"aqi":"59","city":"北京"}}
                   var city = json.data.city;
                   var temp = json.data.wendu;
                   var type = json.data.forecast[0].type;
                   temprature.text = city + " " + type + " " +  temp + "°C" ;
               }
           );
        }



       function getCity()
       {

           var http = new XMLHttpRequest()
           var url = "http://int.dpool.sina.com.cn/iplookup/iplookup.php";

           http.onreadystatechange = function() { // Call a function when the state changes.
                if (http.readyState == 4) {
                    if (http.status == 200) {
                        var strs= new Array(); //定义一数组
                        strs=http.responseText.split("\t"); //字符分割

                        if(strs.length >= 6)
                        {
                            console.log(strs[5])
                            getWeather(strs[5])
                        } else {
                            console.log("error: " + http.status)
                        }
                    }
                }
           }
           http.open("GET", url, true);
           http.send(null);

       }

       Component.onCompleted: {
           getCity();
           weatherTimer.start();

       }


       //定时器
       Timer{
           id: weatherTimer
           interval: 600000 //间隔(单位毫秒):1000毫秒=1秒
           repeat: true //重复

           onTriggered:{
               //getCity();
           }
       }
*/
}
