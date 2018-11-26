#include "CircularProgress.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug>

CircularProgress::CircularProgress(QQuickItem *parent)
    : QQuickPaintedItem(parent),
    m_MinValue(0),
    m_MaxValue(100),
    m_Value(25),
    m_nullPosition(PositionTop),
    m_StrokeWidth(10),
    m_outlinePenWidth(1),
    m_dataPenWidth(1),
    m_BasicColor(QColor("#7f7f7f")),
    m_StartColor(QColor("#0000ff")),
    m_CounterClockwise(false),
    m_StartAngle(0),
    m_StopAngle(360),
    m_StopColor(QColor("#ff0000"))
{
    /*

    m_BackStrokeWidth = 10;
    m_FrontStrokeWidth = 10;
    */
}

CircularProgress::~CircularProgress()
{

}

void CircularProgress::paint(QPainter *painter)
{

    const qreal width = this->width();
    const qreal height = this->height();
    double outerRadius = qMin(width, height);
    QRectF baseRect(1, 1, outerRadius-2, outerRadius-2);
    double dx = (width - outerRadius) / 2.0;
    double dy = (height - outerRadius) / 2.0;
    baseRect.adjust(dx,dy,dx,dy);

    painter->setRenderHint(QPainter::Antialiasing);

    // data brush


    QRectF innerRect;

    double innerRadius = outerRadius - m_StrokeWidth;

    double delta = (outerRadius - innerRadius) / 2;
    innerRect = QRectF(delta, delta, innerRadius, innerRadius);

    innerRect.adjust(dx,dy,dx,dy);

    const double angleRange = m_StopAngle - m_StartAngle;
    const double valueRange = m_MaxValue - m_MinValue;

    double arcStep = angleRange * m_Value / valueRange;

    // base circle
    drawBase(painter, baseRect,innerRect);

    // data circle

    drawValue(painter, baseRect, m_Value, arcStep,innerRect, innerRadius);

}

void CircularProgress::setRange(double min, double max)
{
    m_MinValue = min;
    m_MaxValue = max;

    if (m_MaxValue < m_MinValue)
        qSwap(m_MaxValue, m_MinValue);

    if (m_Value < m_MinValue)
        m_Value = m_MinValue;
    else if (m_Value > m_MaxValue)
        m_Value = m_MaxValue;


    update();
}

void CircularProgress::setMinValue(double min)
{
    setRange(min, m_MaxValue);
}

void CircularProgress::setMaxValue(double max)
{
    setRange(m_MinValue, max);
}

void CircularProgress::setValue(double val)
{
    if (m_Value != val)
    {
        if (val < m_MinValue)
            m_Value = m_MinValue;
        else if (val > m_MaxValue)
            m_Value = m_MaxValue;
        else
            m_Value = val;

        update();
    }
}

void CircularProgress::setOutlinePenWidth(double penWidth)
{
    if (penWidth != m_outlinePenWidth)
    {
        m_outlinePenWidth = penWidth;

        update();
    }
}

void CircularProgress::setDataPenWidth(double penWidth)
{
    if (penWidth != m_dataPenWidth)
    {
        m_dataPenWidth = penWidth;

        update();
    }
}


void CircularProgress::drawBase(QPainter *painter, const QRectF &baseRect,const QRectF &innerRect)
{
    QPainterPath dataPath;
    dataPath.setFillRule(Qt::OddEvenFill);
    dataPath.moveTo(baseRect.center());
    dataPath.addEllipse(baseRect);
    dataPath.addEllipse(innerRect);
    painter->setPen(QPen(m_BasicColor, m_outlinePenWidth));
    painter->setBrush(m_BasicColor);
    painter->drawPath(dataPath);
}

void CircularProgress::drawValue(QPainter *painter
                                  , const QRectF &baseRect
                                  , double value
                                  , double arcLength
                                  , const QRectF & innerRect
                                  , double innerRadius)
{
    // nothing to draw
    if (value == m_MinValue) return;


    QConicalGradient gradient;
    gradient.setCenter(0.5,0.5);
    gradient.setCoordinateMode(QGradient::StretchToDeviceMode);

    if(m_CounterClockwise)
    {
        arcLength = -arcLength;
        gradient.setColorAt(0, m_StartColor);
        gradient.setColorAt(1.0, m_StopColor);
    }
    else
    {
        gradient.setColorAt(0, m_StopColor);
        gradient.setColorAt(1.0, m_StartColor);
    }

    // angle
    if(m_CounterClockwise)    gradient.setAngle(m_StartAngle + m_nullPosition -1);
    else gradient.setAngle(m_StartAngle + m_nullPosition);

    QBrush brush(gradient);



    // for Pie and Donut styles
    QPainterPath dataPath;
    dataPath.setFillRule(Qt::OddEvenFill);
    dataPath.moveTo(baseRect.center());
    dataPath.arcTo(baseRect,  m_StartAngle + m_nullPosition, -arcLength);

    dataPath.moveTo(baseRect.center());
    dataPath.arcTo(innerRect, m_StartAngle + m_nullPosition - arcLength, arcLength);


    painter->setPen(Qt::NoPen);
    painter->setBrush(brush);

    painter->drawPath(dataPath);
}
