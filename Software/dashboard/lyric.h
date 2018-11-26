#ifndef LYRIC_H
#define LYRIC_H
#include <QAbstractListModel>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QVector>
#include <QMap>
#include <QObject>
#include <QList>
#include "krcdecryptor.h"

class LyricItem{
public:
    int start;
    int duration;
    QString text;
};

typedef QList<LyricItem> LyricItemList;
template<class T>
int findIndex(const T & list, int pos)
{
    int index = 0;
    int count = list.count();
    for(int t=count - 1;t > 0 ; t--) {
        if(list.value(t).start <= pos){
            index = t;
            break;
        }
    }
    return index;
}

class LyricLine : public LyricItem{
public:
    LyricItemList SubitemList;

    int getCount()const {
        return SubitemList.count();
    }
    int getIndex(int pos) const {
        return findIndex<LyricItemList>(SubitemList,pos);
    }

    float getPercent(qint64 pos) const // pos 为行内相对标
    {
        if(SubitemList.count() > 0){
            int index = findIndex(SubitemList,pos);
            const LyricItem &item = SubitemList.value(index);
            const int duiration = item.duration;
            const int start = item.start;
            const int delta = pos - start;
            float percent = (float)index/(SubitemList.count());
            if(delta > 0) percent += (float(delta) / float(duiration)) / float(SubitemList.count());
            return percent;

        }else {
            return 1.0f;
        }

    }
};

class Lyric : public QAbstractListModel {
    Q_OBJECT
public:
    explicit Lyric(QObject *parent = 0);
    int currentIndex() const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE bool search(QString path);
    //Q_INVOKABLE int findIndex(int position);
    Q_INVOKABLE int seek(int position);
    Q_INVOKABLE void clear(){
        lyricLines.clear();
    }

    Q_INVOKABLE int getCount() const{
        return lyricLines.count();
    }

    Q_INVOKABLE int getIndex(int pos) const
    {
        return findIndex<LyricLineList>(lyricLines,pos);
    }
    Q_INVOKABLE QString getText(int index) const
    {
        if(index >= 0 && index < lyricLines.count())
        {
            return lyricLines.at(index).text;
        }
        return QString();
    }
    Q_INVOKABLE LyricLine getLine(int index) const
    {
        return lyricLines.at(index);
    }
    Q_INVOKABLE float getPercent(int pos) const // pos 为歌词时标
    {
        // 找到行
        int index = findIndex(lyricLines,pos);
        if(index >=0 && index < lyricLines.count())
        {
            const LyricLine& line = lyricLines.value(index);
            float percent = line.getPercent(pos - line.start);
            return percent;
        }
        return 0;
    }

    Q_INVOKABLE bool load(const QString& fileName)
    {
        bool result = false;
        lyricLines.clear();
        QByteArray Data;
        QFileInfo fileinfo(fileName);
        if (fileinfo.exists() && fileinfo.isReadable()){
            QFile file(fileName);
            if(file.open(QIODevice::ReadOnly))
            {
                QByteArray fileData =  file.readAll();

                if(fileinfo.suffix() == "lrc") {
                    result = parseLrc(fileData);
                } else if(fileinfo.suffix() == "krc") {
                    QByteArray data;
                    if(DecryptKrc(fileData,data)) {
                        result = parseKrc(data);
                    }
                }
                file.close();
            }
        }

        m_currentIndex = 0;
        emit currentIndexChanged();
        if(result) {
            m_currentText = lyricLines.value(0).text;
            emit currentTextChanged();
        }else{
            m_currentText.clear();
            emit currentTextChanged();

        }
        return result;
    }

    Q_PROPERTY(int currentIndex READ currentIndex WRITE setcurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QString currentText READ getCurrentText NOTIFY currentTextChanged)
    Q_PROPERTY(float progress READ getProgress NOTIFY progressChanged)
    void setcurrentIndex(const int & i);

    Q_INVOKABLE void setLyricPath(QString path)
    {
        m_lyricPath = path;
    }
    enum lyricRoles {
        timeRole = Qt::UserRole + 1,
        textRole,
        progressRole,
    };

    int getProgress();
    QString getCurrentText();
signals:
    void currentIndexChanged();
    void progressChanged();
    void currentTextChanged();
public slots:

private:
    QHash<int, QByteArray> roleNames() const;
    void clearData();

    int m_currentIndex;
    float m_currentLineProgress;
    QString m_currentText;
    QString m_lyricPath;

    bool ParseKrcLine(LyricLine &line, const QString & strLine)
    {
        const int lineStartTagIndex = strLine.indexOf('[');
        const int lineEndTagIndex = strLine.indexOf(']');

        // 判断是否包含可能的时标
        if(lineStartTagIndex != 0 || lineEndTagIndex < 0 ||  lineStartTagIndex >= lineEndTagIndex) {
            return false;
        }

        // 时标部分
        QString strLineTimePart = strLine.mid(1,lineEndTagIndex - 1);

        // 歌词部分
        QString strLineStringPart = strLine.mid(lineEndTagIndex + 1);
        if(strLineStringPart.length() <1 ){
            return false;
        }

        // 查找时标
        const int lineTimeMarkTagIndex = strLineTimePart.indexOf(',');
        if(lineTimeMarkTagIndex < 2 ) {
            return false;
        }

        QString strStartTime = strLineTimePart.mid(0,lineTimeMarkTagIndex);
        QStringList itemList= strLineStringPart.split('<');

        line.start = strStartTime.toInt();
        line.duration = 0;
        line.SubitemList.clear();
        line.text.clear();

        foreach (QString lrcitem, itemList)
        {
            if(lrcitem.length() < 1){
                continue;
            }
            ParseKrcItem(line,lrcitem);
        }
        if(lyricLines.size() > 0) {
            beginInsertRows(QModelIndex(), lyricLines.size(), lyricLines.size()+1);
            lyricLines.append(line);
            endInsertRows();
        } else {
            beginInsertRows(QModelIndex(), 0, 0);
            lyricLines.append(line);
            endInsertRows();
        }
        return true;
    }
    bool ParseKrcItem(LyricLine &line, const QString & string)
    {

        QStringList itemStringList = string.split('>');
        if(itemStringList.count() != 2) {
            return false;
        }
        QStringList itemTimeStringList = itemStringList.first().split(',');
        if(itemTimeStringList.count() != 3){
            return false;
        }
        LyricItem item;
        item.start = QString(itemTimeStringList.first()).toInt();
        item.duration = QString(itemTimeStringList.value(1)).toInt();
        item.text = itemStringList.last();;
        line.duration += item.duration;
        line.text.append(item.text);
        line.SubitemList.append(item);
        return true;
    }
    bool parseKrc(const QByteArray &KlcData)
    {
        QStringList list=QString(KlcData).split("\n");
        LyricLine line;
        foreach (QString linestr, list)
        {
            QString strLine = linestr.remove("\r");
            ParseKrcLine(line,strLine);
        }
        line.start = line.start + line.duration;
        line.duration = 99999999;
        line.text="";


        beginInsertRows(QModelIndex(), 0, lyricLines.size()-1);
        lyricLines.append(line);
        endInsertRows();
        return true;
    }

    bool parseLrc(const QByteArray &KlcData) {
        QStringList list=QString(KlcData).split("\n");

        foreach (QString linestr, list)
        {
            QString strLine = linestr.remove("\r");
            const int lineStartTagIndex = strLine.indexOf('[');
            const int lineEndTagIndex = strLine.indexOf(']');

            // 判断是否包含可能的时标
            if(lineStartTagIndex != 0 || lineEndTagIndex < 0 ||  lineStartTagIndex >= lineEndTagIndex) {
                continue;
            }

            // 时标部分
            QString strLineTimePart = strLine.mid(1,lineEndTagIndex - 1);

            // 歌词部分
            QString strLineStringPart = strLine.mid(lineEndTagIndex + 1);
            if(strLineStringPart.length() <1 ){
                continue;
            }

            int m = strLineTimePart.mid(0,2).toInt() * 60000;
            int s = strLineTimePart.mid(3,2).toInt() * 1000;
            int ms =  strLineTimePart.mid(6,2).toInt() * 10;
            int milliseconds = m + s + ms;
            LyricLine line;
            line.start = milliseconds;
            line.duration = 0;
            line.text = strLineStringPart;
            if(lyricLines.size() > 0) {
                beginInsertRows(QModelIndex(), lyricLines.size(), lyricLines.size()+1);
                lyricLines.append(line);
                endInsertRows();
            } else {
                beginInsertRows(QModelIndex(), 0, 0);
                lyricLines.append(line);
                endInsertRows();
            }
        }

        return true;
    }

protected:
    typedef QList<LyricLine> LyricLineList;

    LyricLineList lyricLines;
};


#endif // LYRIC_H
