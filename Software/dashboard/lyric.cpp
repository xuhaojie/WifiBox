#include "lyric.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QTime>

/*
void Lyric::changeLrcFileTime(int time, bool isadd)
{
    QFile file(m_filedir);
    if(!file.exists())
        return;
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream stream(&file);
    QString all_text= stream.readAll();
    file.resize(0);

    QStringList lines = all_text.split("\n");
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");//这个是时间标签的格式[00:05.54]
                                            //正则表达式d{2}表示匹配2个数字
    foreach(QString oneline, lines)
    {
        int pos = rx.indexIn(oneline, 0);
        QString temp = oneline;
        temp.replace(rx, "");
        QString head="[%1:%2.%3]";
        QString setminutesstr="00";
        QString setsecondstr="00";
        QString setmsecondstr="00";

        while (pos != -1)
        { //表示匹配成功
            QString cap = rx.cap(0);//返回第0个表达式匹配的内容
            // 将时间标签转换为时间数值，以毫秒为单位
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();

            int totalTime=0;
            if(isadd)
                totalTime = minute * 60000 + second * 1000 + millisecond*10+time;
            else
                totalTime = minute * 60000 + second * 1000 + millisecond*10-time;
            totalTime=totalTime<0? 0:totalTime;

            int setminutes=totalTime/60000;//分钟数
            int setsecond=(totalTime-minute*60000)/1000;//秒
            int setmsecond=((totalTime)%1000)/10; //毫秒

// Change time format

            setminutesstr=QString::number(setminutes);
            if(setminutes>=0&&setminutes<=9)
                setminutesstr=QString::number(0)+setminutesstr;

            setsecondstr=QString::number(setsecond);
            if(setsecond>=0&&setsecond<=9)
                setsecondstr=QString::number(0)+setsecondstr;

            setmsecondstr=QString::number(setmsecond);
            if(setmsecond>=0&&setmsecond<=9)
                setmsecondstr=QString::number(0)+setmsecondstr;
            if(setminutes<0||setsecond<0||setmsecond<0)
            {
                setminutesstr="00";
                setsecondstr="00";
                setmsecondstr="00";
            }

            pos += rx.matchedLength();
            pos = rx.indexIn(oneline, pos);//匹配全部
        }
        if(!temp.isEmpty())
          stream<<head.arg(setminutesstr).arg(setsecondstr).arg(setmsecondstr)<<temp<<("\r\n");//写入！！
    }
    file.close();
}
*/



Lyric::Lyric(QObject *parent) : QAbstractListModel(parent) {
    m_currentIndex = 0;
    m_currentLineProgress = 1.0f;
    LyricLine line;
    line.start = 0;
    line.duration = 100000;
    line.text = "未找到歌词";
    lyricLines.append(line);
}

int Lyric::currentIndex() const {
    return m_currentIndex;
}

int Lyric::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return lyricLines.count();
}

QVariant Lyric::data(const QModelIndex & cursor, int role) const {
    int index = cursor.row();
    if ( index < 0 || index >= lyricLines.count())
            return QVariant();
    const LyricLine &ll = lyricLines.value(index);
    switch (role) {
    case timeRole:
        return ll.duration;
    case textRole:
        return ll.text;
    case progressRole:
        return m_currentLineProgress;
    default:
        return QVariant();
    }
}

bool Lyric::search(QString file) {
    bool result = false;
    clearData();


    QFileInfo fileinfo(file);
    QStringList lyricFileList;

    lyricFileList.append(fileinfo.path().mid(7) + "/" + fileinfo.completeBaseName() + ".krc");
    lyricFileList.append(fileinfo.path().mid(7) + "/" + fileinfo.completeBaseName() + ".lrc");
    lyricFileList.append(m_lyricPath + "/" + fileinfo.completeBaseName() + ".krc");
    lyricFileList.append(m_lyricPath + "/" + fileinfo.completeBaseName() + ".lrc");

    foreach (QString path, lyricFileList) {
        result = load(path);
        if(result){
            break;
        }
    }
    if(!result)
    {
        LyricLine line;
        line.start = 0;
        line.duration = 1000000;
        line.text = "未找到歌词";
        lyricLines.append(line);
        beginInsertRows(QModelIndex(), 0,0);
        endInsertRows();
    }
    return result;
}
/*
int Lyric::findIndex(int position) {
    //bug fix
    if (position == 0) {
        setcurrentIndex(0);
        return 0;
    }
    //bug fix end
    int countless = lyricData.count() - 1, mid = lyricData.count() / 2, diff = mid / 2;
    while (1) {
        if (lyricData.at(mid).getmilliseconds() <= position) {
            if (mid < countless && lyricData.at(mid + 1).getmilliseconds() > position) {
                break;
            } else {
                mid += diff;
            }
        } else {
            mid -= diff;
        }
        diff /= 2;
        if (diff == 0) {
            break;
        }
    }
    setcurrentIndex(mid);
    return mid;
}
*/
int Lyric::seek(int position) {
    int index = getIndex(position);

    float progress = getPercent(position);
    if(progress != m_currentLineProgress)
    {
        m_currentLineProgress =progress;
        emit progressChanged();
    }
    if (m_currentIndex != index)
    {
        m_currentIndex = index;
        emit currentIndexChanged();
        m_currentText = getText(index);
        emit currentTextChanged();
    }

    return m_currentIndex;
}

QString Lyric::getCurrentText() {
    return m_currentText;
}

int Lyric::getProgress() {
    return m_currentLineProgress;
}

void Lyric::setcurrentIndex(const int & i) {
    if ((i == 0 || (i < getCount())) && m_currentIndex != i) {
        m_currentIndex = i;
        emit currentIndexChanged();
    }
}

QHash<int, QByteArray> Lyric::roleNames() const {
    QHash<int, QByteArray> r;
    r[timeRole] = "time";
    r[textRole] = "textLine";
    r[progressRole] = "progress";
    return r;
}

void Lyric::clearData() {
    beginResetModel();
    lyricLines.clear();
    endResetModel();
}
