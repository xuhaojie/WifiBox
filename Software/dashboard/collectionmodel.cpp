#include "collectionmodel.h"



CollectionMode::CollectionMode(QObject *parent)
    : QAbstractListModel(parent)
{
    m_pMediaLibrary = 0;
}

void CollectionMode::setMediaLibrary(MediaLibrary *pLibrary){
    m_pMediaLibrary = pLibrary;
    m_pMediaLibrary->getCollectionList(m_collections);
}

void CollectionMode::add(const Collection &collection)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_collections << collection;
    endInsertRows();
}

int CollectionMode::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_collections.count();
}

QVariant CollectionMode::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() >= m_collections.count())
        return QVariant();

    const Collection &collection = m_collections[index.row()];
    if (role == TitleRole)
        return collection.title;
    else if (role == IdRole)
        return collection.id;
    else if (role == CoverRole)
        return collection.cover;
    return QVariant();
}

void CollectionMode::clear()
{
    //this->m_animals.clear();
    //清除rows 界面将不显示
    beginRemoveRows(QModelIndex(), 0, m_collections.size()-1);
    //清空动态数组
    m_collections.clear();
    endRemoveRows();
    //end
}

int CollectionMode::getID(const int index)
{

    if (index < 0 || index  >= m_collections.count())
        return 0;
    return m_collections[index].id;
}

QString CollectionMode::getCover(const int index)
{

    if (index < 0 || index  >= m_collections.count())
        return QString();
    return m_collections[index].cover;
}

QString CollectionMode::getTitle(const int index)
{
    if (index < 0 || index  >= m_collections.count())
        return QString();
    return m_collections[index].title;
}

Collection CollectionMode::getCollection(int index)
{
    if (index < 0 || index  >= m_collections.count())
        return Collection();
    return m_collections[index];
}

QHash<int, QByteArray> CollectionMode::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[IdRole] = "cid";
    roles[CoverRole] = "cover";
    return roles;
}

