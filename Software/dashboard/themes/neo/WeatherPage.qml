import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4
import QtQuick 2.6
import QtQuick.Controls 2.0

import "ajax.js" as Ajax
Item{
    id: dialog
    anchors.fill: parent
    property string city: "深圳"
    property string weather: ""
    property string airQuality: ""
    property real temperature: 0
    property string tips: undefined
    property variant forecast: []

    function fetchWeather(ct){
        Ajax.get("http://wthrcdn.etouch.cn/weather_mini?city=" + ct,
            function(result, json){
                dialog.temperature = json.data.wendu
                dialog.tips = json.data.ganmao
                dialog.airQuality = json.data.aqi
                dialog.forecast = json.data.forecast
                dialog.weather = dialog.forecast[0].type
            }
        );
    }

    function fetchCity()
    {
        Ajax.get("http://int.dpool.sina.com.cn/iplookup/iplookup.php?format=json",
            function(result, json){
                if(json.city !== undefined && json.city.length > 0)
                {
                    dialog.city = json.city
                }
            }
        );
    }
    Component.onCompleted: {
        var ct = appState.get("App.City");
        if(ct !== undefined){
            city = ct;
        }
    }
    onCityChanged: {
        fetchWeather(dialog.city)
        appState.set("App.City", dialog.city)
    }
    //定时器
    Timer{
        id: timer
        interval: 1000 //间隔(单位毫秒):1000毫秒=1秒
        running: true
        repeat: true
        onTriggered:{
            if(dialog.city.length < 1){
                dialog.fetchCity()
                timer.interval = 3000
            } else {
                if(dialog.weather.length < 1) {
                    dialog.fetchWeather(dialog.city);
                } else {
                     if(timer.interval < 300000){
                        timer.interval = 300000
                     } else {
                        dialog.fetchWeather(dialog.city);
                     }
                }
            }
        }
    }


    // 测试用ajax 获取 json 数据    更复杂的ajax调用请查看 qml/network/ 相关示例4
/*
"{
    "desc":"OK",
    "status":1000,"
    data":
        {
            "aqi":"81",
            "city":"深圳"
            "wendu":"19",
            "ganmao":"各项气象条件适宜，无明显降温过程，发生感冒机率较低。",
            "forecast":[
                {"fengxiang":"无持续风向","fengli":"微风级","high":"高温 22℃","type":"多云","low":"低温 16℃","date":"3日星期五"},
                {"fengxiang":"无持续风向","fengli":"微风级","high":"高温 23℃","type":"多云","low":"低温 18℃","date":"4日星期六"},
                {"fengxiang":"无持续风向","fengli":"微风级","high":"高温 25℃","type":"阴","low":"低温 18℃","date":"5日星期天"},
                {"fengxiang":"无持续风向","fengli":"微风级","high":"高温 25℃","type":"小雨","low":"低温 16℃","date":"6日星期一"},
                {"fengxiang":"无持续风向","fengli":"微风级","high":"高温 22℃","type":"小雨","low":"低温 16℃","date":"7日星期二"}],
            "yesterday":{"fl":"5-6级","fx":"东北风","high":"高温 23℃","type":"多云","low":"低温 15℃","date":"2日星期四"},

        }
    }"
*/
    Row{
        id:today
        anchors.left: dialog.left
        anchors.top: dialog.top
        width:dialog.width
        height:dialog.height / 3

        Item{
            width: parent.width / 3
            height: parent.height
            Row{
                width: parent.width
                height: parent.height / 2
                Image{
                    width: parent.width/2
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "images/weather/" + dialog.weather + ".png"
                }
                Text{
                    width: parent.width / 2
                    height: parent.height
                    color:"white"
                    font.pixelSize: height*0.4
                    horizontalAlignment:Text.AlignHCenter
                    text: dialog.weather
                }
            }

            Text{
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height * 2 / 3
                color:"white"
                font.pixelSize: height*0.8
                text: dialog.temperature + "℃"
                wrapMode: Text.WordWrap
            }

        }
        Column{
            width: parent.width * 2 / 3
            height: parent.height * 0.75
            Text{
                height: parent.height * 0.25
                color:"lightblue"
                font.pixelSize: height*0.8
                text: "当前城市: " + dialog.city
            }
            Text{
                height: parent.height * 0.25
                color:"lightblue"
                font.pixelSize: height*0.8
                text: "空气质量: " + dialog.airQuality
            }
            Text{
                width:parent.width
                height: parent.height * 0.5

                color:"lightblue"
                font.pixelSize: height*0.4
                text: "感冒指数: " +  dialog.tips
                wrapMode: Text.WordWrap
            }
        }
    }

    Row{
        anchors.left: dialog.left
        anchors.top: today.bottom
        anchors.bottom: dialog.bottom
        width:dialog.width
        Repeater{
            model:5
            Item{
                width:parent.width / 5
                height:parent.height
                //color:"transparent"
                //border.color: "white"
                //border.width: 1

                Column{
                    anchors.fill: parent
                    //spacing: parent.height / 12
                    Item{
                        height: parent.height / 6
                    }
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: parent.height / 6
                        color:"white"
                        font.pixelSize: height*0.4
                        text:index==0 ? "今天" : dialog.forecast[index].date
                    }
                    Image{
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: parent.height / 6
                        fillMode: Image.PreserveAspectFit
                        source: "images/weather/" + dialog.forecast[index].type + ".png"
                    }
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: parent.height / 6
                        color:"white"
                        font.pixelSize: height*0.4
                        text: dialog.forecast[index].low.substring(3,6) + " ~ " + dialog.forecast[index].high.substring(3,6)
                    }

                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: parent.height / 6
                        color:"white"
                        font.pixelSize: height*0.4
                        text: dialog.forecast[index].fengli
                    }

                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: parent.height / 6
                        color:"white"
                        font.pixelSize: height*0.4
                        text: dialog.forecast[index].fengxiang
                    }

                }

            }
        }
    }

}

