#ifndef __COLLECTIONMODEL_H__
#define __COLLECTIONMODEL_H__

#include <QObject>
#include <QAbstractListModel>
#include "medialibrary.h"


class CollectionMode : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(CollectionRoles)
public:

    enum CollectionRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        CoverRole
    };

    CollectionMode(QObject *parent = 0);
    void setMediaLibrary(MediaLibrary* pLibrary);
    void add(const Collection &collection);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void clear();
    Q_INVOKABLE int getID(const int index);
    Q_INVOKABLE QString getCover(const int index);
    Q_INVOKABLE QString getTitle(const int index);
    Q_INVOKABLE Collection getCollection(int index);
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    MediaLibrary* m_pMediaLibrary;
    CollectionList m_collections;

};

#endif // __COLLECTIONMODEL_H__
