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

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
//#include <QtWebEngine/QtWebEngine>
#include <QTime>
#include <QQuickView>
#include <QDir>
#include <QQmlContext>
#include <QStandardPaths>

#include "car.h"
#include "playlistmodel.h"
#include "collectionmodel.h"
#include "medialibrary.h"
#include "lyric.h"
#include "setting.h"

#include <carstategenerator.h>
#include "notificationclient.h"
#include "onlineinfoprovider.h"
#include "qDebug2Logcat.h"
#include "lyric.h"
#include "mymediaplayer.h"
#include "CircularProgress.h"
#include "WaveProgress.h"
#include "keymapper.h"

#if defined(Q_OS_ANDROID)
    #include <QtAndroid>
    #include <QtAndroidExtras/QAndroidJniObject>
    #include <QtAndroidExtras/QAndroidJniEnvironment>
#endif
QString GetLocalStorageDbFile(const QString& dbName){
    QQuickView view;
    QString storagePath = view.engine()->offlineStoragePath();
    storagePath += "/Databases";

    QDir dir(storagePath);

    bool endLoop = false;
    QString databaseFile;
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::Readable);
    for(int i = 0; i < list.size() && !endLoop; i++)
    {
        QFileInfo file = list.at(i);
        if(file.fileName().endsWith(".ini"))
        {
            QFile ini(file.absoluteFilePath());
            if (!ini.open(QIODevice::ReadOnly | QIODevice::Text))
                continue;

            while(!ini.atEnd())
            {
                QString line = ini.readLine();
                if(line.contains(dbName)) //probably could be better
                {
                    databaseFile= file.absoluteFilePath().replace(".ini", ".sqlite");
                    //printf("Database file:%s\n",databaseFile);
                    endLoop = true;
                }
            }

            ini.close();Q_INVOKABLE
        }
    }
    return databaseFile;
}

void keep_screen_on(bool on) {
#if defined(Q_OS_ANDROID)

  QtAndroid::runOnAndroidThread([on]{
    QAndroidJniObject activity = QtAndroid::androidActivity();
    if (activity.isValid()) {
      QAndroidJniObject window =
          activity.callObjectMethod("getWindow", "()Landroid/view/Window;");

      if (window.isValid()) {
        const int FLAG_KEEP_SCREEN_ON = 128;
        if (on) {
          window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
        } else {
          window.callMethod<void>("clearFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
        }
      }
    }
    QAndroidJniEnvironment env;
    if (env->ExceptionCheck()) {
      env->ExceptionClear();
    }
  });
#endif
}

int main(int argc, char *argv[])
{

    // http://stackoverflow.com/questions/27982443/qnetworkaccessmanager-crash-related-to-ssl
    qunsetenv("OPENSSL_CONF");
    installLogcatMessageHandler("Dashboard");

    QString path =  QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    // QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation); //QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first();
    //settings = new QSettings(path.append("/todo1-2-3.ini"), QSettings::IniFormat);
    const QString stettingFileName = path + "/dashboard.setting";
    const QString stateFileName = path + "/dashboard.state";
    QGuiApplication app(argc, argv);
    app.setApplicationName("Dashboard");
    app.setOrganizationName("www.autopard.com");

    //将字体文件名传给addApplicationFont,得到字体的Id
    int fontId = QFontDatabase::addApplicationFont(":/fonts/msyh.ttf");
    //将字体Id传给applicationFontFamilies,得到一个QStringList,其中的第一个元素为新添加字体的family
    QString msyh = QFontDatabase::applicationFontFamilies ( fontId ).at(0);
    QFont font(msyh,16);
    //将此字体设为QApplication的默认字体
    app.setFont(font);

    qmlRegisterType<Lyric>("dataModel", 1, 0, "LyricModel");
//    QtWebEngine::initialize();



//    qmlRegisterType<MediaLibrary>("car.autopard.com", 1, 0, "MediaLibrary");

    qmlRegisterType<Car>("car.autopard.com", 1, 0, "Car");
    qmlRegisterType<CircularProgress>("circularProgress.autopard.com", 1, 0, "CircularProgress");
    qmlRegisterType<WaveProgress>("waveProgress.autopard.com", 1, 0, "WaveProgress");

    //QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    //app.setFont(QFont("DejaVu Sans"));

    OnlineInfoProvider onlineInfoProvider;
    qmlRegisterType<Car>("car.autopard.com", 1, 0, "OnlineInfoProvider");

//    QString databaseFile = GetLocalStorageDbFile("MediaDB");
    Setting setting;
    if(!setting.load(stettingFileName))
    {
        QString audioPath =QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
        setting.set("AudioPath",audioPath);
        setting.set("LyricPath",audioPath);

        QStringList mediaPaths;
        static int CruiseMode = 0;
        CruiseMode++;
        if(CruiseMode > 2)
        {
            CruiseMode = 0;
        }
        //SetCarState(m_piEnvironment, STATE_Car_CruisingMode, CruiseMode);
        //mediaPaths.append("/media/hodge/Data/Audio/FLAC/孙燕姿FLAC");
        setting.set("AudioPaths",mediaPaths);
        setting.set("LyricPaths",mediaPaths);

        QString videoPath =QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
        setting.set("VideoPath",videoPath);

        mediaPaths.clear();
        //mediaPaths.append("/media/hodge/Data/100ANV01");
        setting.set("VideoPaths",mediaPaths);

        QStringList filter;
        filter << "mp3";
        filter << "flac";
        setting.set("AudioFilter",filter);

        filter.clear();
        filter << "mp4";
        filter << "mkv";
        filter << "avi";
        setting.set("VideoFilter",filter);
    }

    Setting state;
    if(!state.load(stateFileName))
    {

    }
    MediaLibrary mediaLibrary;

    QString audioPath = setting.get("AudioPath").toString();
    QStringList filter = setting.get("AudioFilter").toStringList();
    mediaLibrary.addDirectory(audioPath,filter);

    mediaLibrary.addDirectory(audioPath,filter);

    filter = setting.get("VideoFilter").toStringList();

    QString videoPath = setting.get("VideoPath").toString();
    mediaLibrary.addDirectory(videoPath,filter);


    QStringList paths = setting.get("AudioPaths").toStringList();
    QStringList::const_iterator it = paths.begin();
    while(it != paths.end())
    {
        mediaLibrary.addDirectory(*it,filter);
        ++it;
    }

    paths = setting.get("VideoPaths").toStringList();
    it = paths.begin();
    while(it != paths.end())
    {
        mediaLibrary.addDirectory(*it,filter);
        ++it;
    }

    //    QQmlApplicationEngine engine;
    //    QQmlContext *ctxt = engine.rootContext();

    QQuickView view;
    Car car;
    car.start();

    CarStateGenerator carStateGen(&view);
    carStateGen.SetTarget(&car);

    PlaylistModel playlistModel;

    CollectionMode collectionModel;

    Lyric lyricModel;

    collectionModel.setMediaLibrary(&mediaLibrary);
    playlistModel.setMediaLibrary(&mediaLibrary);
    playlistModel.changeCollection(1);

    QQmlContext *ctxt = view.rootContext();
    NotificationClient *notificationClient = new NotificationClient(&view);
    ctxt->setContextProperty("playlistModel", &playlistModel);
    ctxt->setContextProperty("collectionModel", &collectionModel);
    ctxt->setContextProperty("mediaLibrary", &mediaLibrary);
    ctxt->setContextProperty("appSetting", &setting);
    ctxt->setContextProperty("appState", &state);
    ctxt->setContextProperty("car", &car);
    ctxt->setContextProperty("playlistModel", &playlistModel);
    ctxt->setContextProperty("collectionModel", &collectionModel);
    ctxt->setContextProperty("mediaLibrary", &mediaLibrary);
    ctxt->setContextProperty("notificationClient", notificationClient);
    ctxt->setContextProperty("onlineInfoProvider", &onlineInfoProvider);
    ctxt->setContextProperty("lyricModel", &lyricModel);
    ctxt->setContextProperty("simulator", &carStateGen);


    MyMediaPlayer* player = new MyMediaPlayer();

    ctxt->setContextProperty("mymediaplayer", player);



/*
    engine.load(QUrl("qrc:/themes/neo/main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;
*/
    QObject::connect(ctxt->engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));
    view.setSource(QUrl(QStringLiteral("qrc:/themes/neo/main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    KeyMapper keyMapper(&view);
    keyMapper.Init(&car);

/*

    bool demoMode = setting.get("App.DemoMode").toBool();
    if(demoMode)
    {
        carStateGen.start();
    }
*/
#ifdef QT_DEBUG
    // Debug版本用窗口模式
    view.setMinimumSize(QSize(800,480));
    view.resize(800,480);
    //view.resize(1280,720);
    view.show();
#else
    // Release版本全屏
    view.showFullScreen();
#endif
    keep_screen_on(true);
    int result =  app.exec();
    keep_screen_on(false);

    carStateGen.quit();
    carStateGen.terminate();
    carStateGen.wait();

    setting.save(stettingFileName);
    state.save(stateFileName);
    return result;
}



