#ifndef __SETTING_H__
#define __SETTING_H__

#include <QObject>
#include <QQuickItem>
#include <qmap.h>


class Setting : public QObject
{
    Q_OBJECT
//    Q_ENUMS(GenerateAlgorithm)
    //Q_PROPERTY(float Speed)


public:
    explicit Setting(QObject *parent = 0);
    ~Setting();
    Q_INVOKABLE QVariant get(const QString& key)const;
    Q_INVOKABLE void set(const QString& key, const QVariant& value);
    Q_INVOKABLE bool load(const QString& fileName);
    Q_INVOKABLE bool save(const QString& fileName);



//    Q_INVOKABLE GenerateAlgorithm algorithm() const;
//    Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm);

signals:


public slots:

protected slots:


protected:
//    void time
    typedef QMap<QString,QVariant> SettingMap;
    SettingMap m_map;
    bool m_changed;
private:


};

#endif // __SETTING_H__
