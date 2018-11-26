TEMPLATE = app
TARGET = dashboard
INCLUDEPATH += .


QT += quick
QT += sql
QT += svg
QT += multimedia multimediawidgets
QT += network
android {
    QT += androidextras
}

#webengine

SOURCES += \
    main.cpp \
    car.cpp \
    datasource.cpp \
    medialibrary.cpp \
    playlistmodel.cpp \
    collectionmodel.cpp \
    setting.cpp \
    carstategenerator.cpp \
    notificationclient.cpp \
    onlineinfoprovider.cpp \
    qDebug2Logcat.cpp \
    zlib/adler32.c \
    zlib/compress.c \
    zlib/crc32.c \
    zlib/deflate.c \
    zlib/inffast.c \
    zlib/inflate.c \
    zlib/inftrees.c \
    zlib/trees.c \
    zlib/uncompr.c \
    zlib/zutil.c \
    zlib/gzclose.c \
    zlib/gzlib.c \
    zlib/gzread.c \
    zlib/gzwrite.c \
    zlib/infback.c \
    lyric.cpp \
    krcdecryptor.cpp \
    mymediaplayer.cpp \
    CircularProgress.cpp \
    WaveProgress.cpp \
    keymapper.cpp


RESOURCES += \
    dashboard.qrc

OTHER_FILES += \
    qml/dashboard.qml

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols/extras/dashboard
INSTALLS += target

HEADERS += \
    car.h \
    datasource.h \
    medialibrary.h \
    playlistmodel.h \
    collectionmodel.h \
    setting.h \
    statename.h \
    carstategenerator.h \
    notificationclient.h \
    onlineinfoprovider.h \
    qDebug2Logcat.h \
    decodekrc.h \
    zlib/deflate.h \
    zlib/infblock.h \
    zlib/infcodes.h \
    zlib/inffast.h \
    zlib/inffixed.h \
    zlib/inftrees.h \
    zlib/infutil.h \
    zlib/trees.h \
    zlib/zconf.h \
    zlib/zlib.h \
    zlib/zutil.h \
    zlib/crc32.h \
    zlib/gzguts.h \
    zlib/inflate.h \
    lyric.h \
    krcdecryptor.h \
    mymediaplay.h \
    mymediaplayer.h \
    CircularProgress.h \
    WaveProgress.h \
    keymapper.h


DISTFILES += \
    android/AndroidManifest.xml \
    android/res/drawable/icon.png \
    android/src/com/autopard/dashboard/notification/NotificationClient.java \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/res/drawable/icon.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/drawable-xhdpi/icon.png \
    android/res/drawable-xxhdpi/icon.png

#DEFINES += TAGLIB_STATIC=1


#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/android/lib/libssl.so \
        $$PWD/android/lib/libcrypto.so
}
