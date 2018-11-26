#include "medialibrary.h"
#include <QTimerEvent>
#include <QDateTime>
#include <unistd.h>
#include <QDir>
#include <QFileInfo>
MediaLibrary::MediaLibrary(QObject *parent)
    : QObject(parent)

{
   // connect(&m_dataSource, SIGNAL(dataChanged(QString,QString)), this, SLOT(onDataChanged(QString,QString)));
}

MediaLibrary::~MediaLibrary()
{

}

bool MediaLibrary::readMediaInfo(const QString& fileName)
{
    bool bResult = false;

    return   bResult;
}

MediaID MediaLibrary::addMedia(const QString &fileName)
{
///    printf("Add media %s\n",fileName.toStdString().data());
    // 	TagLib::File* File =  f.create(pMediaInfo->FileName.c_str());
    QString coverPath = "images/cover/";
    QString defaultCover = "images/default-cover.png";
    if(findMedia(fileName))
    {
        return 0;
    }

    MediaID id = m_mediaMap.count()+1;
    Media media;
    QFileInfo fi(fileName);
    media.title = fi.fileName();
    media.file = fileName;
    media.id = id;

    m_mediaMap.insert(id, media);
    return id;

}

MediaID MediaLibrary::findMedia(const QString &fileName)
{
    MediaMap::Iterator it = m_mediaMap.begin();
    while(it != m_mediaMap.end())
    {
        Media& media = it.value();
        if(media.file == fileName) {
            return it.key();
        }
        it++;
    }
    return 0;

}

bool MediaLibrary::getMedia(Media &media, MediaID id)
{
    MediaMap::iterator it = m_mediaMap.find(id);
    if(it != m_mediaMap.end())
    {
        media = it.value();
        return true;
    }
    return false;
}

CollectionID MediaLibrary::addCollection(Collection &collection)
{
    CollectionID id = m_collectionMap.count()+1;

    collection.id = id;

    m_collectionMap.insert(id, collection);
//    printf("Add collection %s\n",collection.title.toStdString().data());
    return id;
}

CollectionID MediaLibrary::findCollection(const QString &title)
{
    CollectionMap::Iterator it = m_collectionMap.begin();
    while(it != m_collectionMap.end())
    {
        Collection& collection = it.value();
        if(collection.title == title) {
            return it.key();
        }
        it++;
    }
    return 0;
}

bool MediaLibrary::getCollection(Collection &collection, CollectionID id)
{
    CollectionMap::iterator it = m_collectionMap.find(id);
    if(it != m_collectionMap.end())
    {
        collection = it.value();
        return true;
    }
    return false;
}

bool MediaLibrary::getCollectionList(CollectionList &collectionList)
{
    CollectionMap::Iterator it = m_collectionMap.begin();
    while(it != m_collectionMap.end())
    {
        collectionList.append(it.value());
        it++;
    }
    return true;
}


int MediaLibrary::addDirectory(const QString& path,const QStringList &filter)
{
    return getFileList(path, filter);
}

void MediaLibrary::clear(void)
{

    m_mediaMap.clear();
    m_collectionMap.clear();
}

int MediaLibrary::getFileList(const QString & path, const QStringList &filter)
{

    int fileCount = 0;
    int dirCount = 0;
    QDir dir(path);
/*
    QStringList filters;
    filters << "*.mp3" << "*.flac";
    dir.setNameFilters(filters);
*/
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    Collection collection;

    collection.title = dir.dirName();
    QString coverFile =  path + "/cover.jpg";
    QFile file(coverFile);
    if (file.exists()){
       collection.cover = "file://" + coverFile;
    }
    else
    {
        QString coverFile = path + "/" + collection.title + ".jpg";
        QFile file(coverFile);
        if (file.exists()){
           collection.cover = "file://" + coverFile;
        }
    }

    for(int i=0; i < file_list.size(); ++i)
    {
        const QFileInfo& file_info = file_list.at(i);
        QString suffix = file_info.suffix();

        QStringList::const_iterator  it = filter.begin();
        while(it != filter.end())
        {
           if(QString::compare(suffix, *it, Qt::CaseInsensitive) == 0)
           {
               const QString& absolute_file_path = file_info.absoluteFilePath();
               MediaID mediaId = addMedia(absolute_file_path);
               if(mediaId){
                   collection.mediaList.append(mediaId);
               }
           }
           ++it;
        }
    }
    if(collection.mediaList.count())
    {
        addCollection(collection);
    }



    fileCount = collection.mediaList.count();
    dirCount = folder_list.size();

    for(int i = 0; i != dirCount; i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         fileCount += getFileList(name,filter);

    }
    return fileCount;

}



/*
void Car::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == m_nSpeedTimer)
    {
        emit speedChanged(m_speed);
    }
    else
    {
        QObject::timerEvent(e);
    }
}
*/


