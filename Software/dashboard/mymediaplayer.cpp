#include "mymediaplayer.h"

void MyMediaPlayer::play()
{
    qDebug()<<"play...";
    QMediaPlayer::setMedia(QUrl::fromLocalFile(m_filName));
    QMediaPlayer::play();
    QString strTitle = QMediaPlayer::metaData("Title").toString();
    QString strSize= QMediaPlayer::metaData("Size").toString();
    qDebug()<<"title: " + strTitle + "size: "+ strSize;
}

MyMediaPlayer::MyMediaPlayer(QObject* parent, Flags flags): QMediaPlayer(parent, flags)
{
    connect(this, SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(OnMetaDataAvailableChanged(bool)));
}

void MyMediaPlayer::setVideoSurface(QAbstractVideoSurface* surface)
{
    qDebug() << "Changing surface";
    m_surface = surface;
    setVideoOutput(m_surface);
}

QAbstractVideoSurface* MyMediaPlayer::getVideoSurface()
{
    return m_surface;
}

void MyMediaPlayer::OnMetaDataAvailableChanged(bool available)
{
    // 数据显示
    qDebug() << "OnMetaDataAvailableChanged";
    if(available){
        foreach(QString str,availableMetaData()){
            qDebug()<<str<<"   :"<<metaData(str).toString().toUtf8().data();
        }
        //playlist->setCurrentIndex(++count);
    }
}

QString MyMediaPlayer::fileName() const
{
    return m_filName;
}

void MyMediaPlayer::setFileName(const QString &fileName)
{
    m_filName = fileName;
}

