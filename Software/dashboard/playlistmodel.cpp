/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
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
#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_pMediaLibrary = 0;
}

void PlaylistModel::add(const Media &media)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_medias << media;
    endInsertRows();
}

int PlaylistModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_medias.count();
}

QVariant PlaylistModel::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() >= m_medias.count())
        return QVariant();

    const Media &media = m_medias[index.row()];
    if (role == TitleRole)
        return media.title;
    else if (role == FileRole)
        return media.file;
    return QVariant();
}

void PlaylistModel::clear()
{
    //this->m_animals.clear();
    //清除rows 界面将不显示
    beginRemoveRows(QModelIndex(), 0, m_medias.size());
    //清空动态数组
    m_medias.clear();
    endRemoveRows();
    //end
}

void PlaylistModel::changeCollection(uint id)
{
    //清除rows 界面将不显示
    beginRemoveRows(QModelIndex(), 0, m_medias.size());
    //清空动态数组
    m_medias.clear();
    endRemoveRows();
    if(m_pMediaLibrary)
    {
        Collection collection;

        m_pMediaLibrary->getCollection(collection, id);
        Collection::MediaList& mediaList = collection.mediaList;
        const int count = mediaList.count();
        beginInsertRows(QModelIndex(), 0, count-1);
        Collection::MediaList::Iterator it = mediaList.begin();
        while(it != mediaList.end())
        {
            Media media;
            m_pMediaLibrary->getMedia(media, *it);
            m_medias << media;
            ++it;
        }
        endInsertRows();
    }
}

QString PlaylistModel::getFile(const int index)
{

    if (index < 0 || index  >= m_medias.count())
        return 0;
    return m_medias[index].file;
}


QString PlaylistModel::getTitle(const int index)
{

    if (index < 0 || index  >= m_medias.count())
        return 0;
    return m_medias[index].title;
}



QHash<int, QByteArray> PlaylistModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[FileRole] = "file";
    return roles;
}


