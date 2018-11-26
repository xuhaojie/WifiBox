#ifndef __MEDIALIBRARY_H__
#define __MEDIALIBRARY_H__

#include <QObject>
#include <QQuickItem>
#include <qmap.h>
typedef uint MediaID;
typedef uint CollectionID;
struct Media{

    QString file;
    QString title;
    MediaID id;
};

struct Collection{
    typedef QList<MediaID> MediaList;
    MediaList mediaList;
    QString title;
    QString cover;
    CollectionID id;
};
typedef QList<Collection> CollectionList;

class MediaLibrary : public QObject
{
    Q_OBJECT
//    Q_ENUMS(GenerateAlgorithm)
    // Q_PROPERTY(float rev READ getRev WRITE setRev NOTIFY revChanged)
    // Q_PROPERTY(float speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    //Q_PROPERTY(float rev READ getRev WRITE setRev)
    //Q_PROPERTY(float speed READ getSpeed WRITE setSpeed)

    //Q_PROPERTY(float Speed)


public:
    explicit MediaLibrary(QObject *parent = 0);
    ~MediaLibrary();


    Q_INVOKABLE int addDirectory(const QString &path,const QStringList &filter);
    Q_INVOKABLE void clear(void);
    MediaID addMedia(const QString &fileName);
    MediaID findMedia(const QString &fileName);
    bool getMedia(Media& media,MediaID id);


    CollectionID addCollection(Collection &Collection);
    CollectionID findCollection(const QString &title);
    bool getCollection(Collection& collection,CollectionID id);

    bool getCollectionList(CollectionList& collectionList);
//    Q_INVOKABLE GenerateAlgorithm algorithm() const;
//    Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm);

signals:
    //void speedChanged(float value);
    //void revChanged(float value);

public slots:
    //void start();
    //void stop();

    //void onDataChanged(const QString& key, const QString& value);


protected:

    typedef QMap<MediaID,Media> MediaMap;
    typedef QMap<CollectionID,Collection> CollectionMap;
    int getFileList(const QString& path,const QStringList &filter);



    bool readMediaInfo(const QString &fileName);

    MediaMap m_mediaMap;
    CollectionMap m_collectionMap;
private:


};

#endif // __MEDIALIBRARY_H__
