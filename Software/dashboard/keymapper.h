#ifndef __KEYMAPPER_H__
#define __KEYMAPPER_H__

#include <QObject>
#include <car.h>
#include <QQuickView>

class KeyMapper : public QObject
{
    Q_OBJECT
public:
    explicit KeyMapper(QObject *parent = nullptr);
    int Init(Car* pCar);
signals:

public slots:

    void buttonSlot(unsigned int buttonState);

    void wheelSlot(int wheelState);

protected:
    Car* m_car;
    QQuickView *m_view;
    unsigned int m_buttonState;
    int m_wheelState;

};

#endif // __KEYMAPPER_H__
