#include "keymapper.h"

KeyMapper::KeyMapper(QObject *parent) : QObject(parent),
  m_car(0),
  m_view(0),
  m_buttonState(0),
  m_wheelState(0)
{
    m_view = (QQuickView *)parent;
}

int KeyMapper::Init(Car *pCar)
{
    m_car = pCar;
    if(m_car)
    {
        //connect(m_pSocket, SIGNAL(aborted()), this, SLOT(abortedSlot()));

        connect(pCar, SIGNAL(buttonStateChanged(uint)), this, SLOT(buttonSlot(uint)));
        connect(pCar, SIGNAL(rcWheelStateChanged(int)), this, SLOT(wheelSlot(int)));
        //connect(pCar, SIGNAL(buttonStateChanged(uint)), this, SLOT(buttonSlot(uint)));
        //connect(pCar, SIGNAL(rcWheelStateChanged(uint)), this, SLOT(wheelSlot(uint)));
        return 0;
    }
    return -1;
}

void KeyMapper::buttonSlot(unsigned int buttonState)
{

    if(buttonState != m_buttonState)
    {
        if((buttonState & Car::Button_Audio_Prev) && !(m_buttonState & Car::Button_Audio_Prev))
        {
            QKeyEvent key_press(QKeyEvent::KeyPress, Qt::Key_MediaPrevious, Qt::NoModifier);
            QCoreApplication::sendEvent(m_view->rootObject(), &key_press);
        }
        if((buttonState & Car::Button_Audio_Next) && !(m_buttonState & Car::Button_Audio_Next))
        {
            QKeyEvent key_press(QKeyEvent::KeyPress, Qt::Key_MediaNext, Qt::NoModifier);
            QCoreApplication::sendEvent(m_view->rootObject(), &key_press);
        }
        if(buttonState & Car::Button_Audio_Mute)
        {
            if(!(m_buttonState & Car::Button_Audio_Mute))
            {
                QKeyEvent key_press(QKeyEvent::KeyPress, Qt::Key_MediaPause, Qt::NoModifier);
                QCoreApplication::sendEvent(m_view->rootObject(), &key_press);
            }
        }
        else
        {
            if(m_buttonState & Car::Button_Audio_Mute)
            {
                QKeyEvent key_press(QKeyEvent::KeyPress, Qt::Key_MediaPlay, Qt::NoModifier);
                QCoreApplication::sendEvent(m_view->rootObject(), &key_press);
            }
        }
        m_buttonState = buttonState;
    }
}

void KeyMapper::wheelSlot(int wheelState)
{
    int Value = wheelState;
    const int WhellValueBorder = 64;

    if(wheelState != m_wheelState)
    {
        if(m_wheelState >=0)
        {
            int delta = wheelState - m_wheelState;
            if(delta >= WhellValueBorder/2)
            {
                QKeyEvent key_press(QKeyEvent::KeyPress, Qt::Key_PageUp, Qt::NoModifier);
                QCoreApplication::sendEvent(m_view->rootObject(), &key_press);
            }
            else if(delta < -WhellValueBorder/2)
            {
                QKeyEvent key_press(QKeyEvent::KeyPress, Qt::Key_PageDown, Qt::NoModifier);
                QCoreApplication::sendEvent(m_view->rootObject(), &key_press);
            }

            else if(delta > 0)
            {
                QKeyEvent key_press(QKeyEvent::KeyPress, Qt::Key_PageDown, Qt::NoModifier);
                QCoreApplication::sendEvent(m_view->rootObject(), &key_press);
            }
            else if(delta <0)
            {
                QKeyEvent key_press(QKeyEvent::KeyPress, Qt::Key_PageUp, Qt::NoModifier);
                QCoreApplication::sendEvent(m_view->rootObject(), &key_press);
            }
        }
        m_wheelState = wheelState;

    }



}
