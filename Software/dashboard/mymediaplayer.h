#ifndef MYMEDIAPLAYER_H
#define MYMEDIAPLAYER_H
#include <QMediaPlayer>
#include <QAbstractVideoSurface>

class MyMediaPlayer: public QMediaPlayer
{
Q_OBJECT
public:
    Q_PROPERTY(QAbstractVideoSurface* videoSurface READ getVideoSurface WRITE setVideoSurface )
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName)
    Q_INVOKABLE void play();
public:
    MyMediaPlayer(QObject * parent = 0, Flags flags = 0);

    QString fileName() const;
    void setFileName(const QString &);

public slots:

    void setVideoSurface(QAbstractVideoSurface* surface);
    QAbstractVideoSurface* getVideoSurface();
    void OnMetaDataAvailableChanged(bool available);

private:
    QAbstractVideoSurface* m_surface;
    QString m_filName;
};
#endif // MYMEDIAPLAYER_H
