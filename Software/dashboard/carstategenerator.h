#ifndef __CARSTATEGENERATOR_H__
#define __CARSTATEGENERATOR_H__

#include <QThread>
#include <car.h>

class CarStateGenerator : public QThread
{
    //Q_OBJECT
public:
    explicit CarStateGenerator(QObject *parent = 0);
    virtual ~CarStateGenerator()
    {}
    void SetTarget(Car* pCar);
    void run();

    void simulate();
protected:
    Car* m_car;
    unsigned int m_tick;
};

#endif // __CARSTATEGENERATOR_H__
