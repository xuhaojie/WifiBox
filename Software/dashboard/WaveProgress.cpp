#include "WaveProgress.h"
#include <QPainter>  
#include <QPen>  
#include <QBrush>  
#include <QColor>  
#include <QDebug>  
  
WaveProgress::WaveProgress(QQuickItem *parent)
    : QQuickPaintedItem(parent),
    m_MinValue(0), m_MaxValue(100),
    m_Value(25),
    m_StrokeWidth(3),
    m_StrokeColor(QColor("#7f7f7f")),
    m_StartColor(QColor("#0000ff")),
    m_StopColor(QColor("#ff0000")),
    m_WaveOffset(0.0),
    m_WaveHeight(0.0)
{  
    /*

    m_MinValue = 0;
    m_MaxValue = 100;
    m_Value = 0;

    m_StartAngle = 0;
    m_StopAngle = 360;

    m_BackStrokeWidth = 10;
    m_FrontStrokeWidth = 10;
    */
}  
  
WaveProgress::~WaveProgress()
{  

}  

void WaveProgress::setMinValue(double min)
{
    m_MinValue = min;
}

void WaveProgress::setMaxValue(double max)
{
    m_MaxValue = max;
}

void WaveProgress::setValue(double val)
{
    if (m_Value != val)
    {
        if (val < m_MinValue) m_Value = m_MinValue;
        else if (val > m_MaxValue) m_Value = m_MaxValue;
        else m_Value = val;

        update();
    }
}

void WaveProgress::paint(QPainter *painter)
{
    const int height = this-> height();
    const int width = this->width();
    int side = qMin(width, height);
    if(m_Value < m_TargetValue)
    {
        m_Value += 1;
        this->update();
    }
    else if(m_Value > m_TargetValue)
    {
        m_Value -= 1;
        this->update();
    }



    QSizeF itemSize = size();

    double outerRadius = qMin(width, height);
    QRectF baseRect(m_StrokeWidth / 2, m_StrokeWidth / 2, outerRadius - m_StrokeWidth, outerRadius - m_StrokeWidth);
    double dx = (width - outerRadius) / 2.0;
    double dy = (height - outerRadius) / 2.0;
    baseRect.adjust(dx,dy,dx,dy);
    double innerRadius = outerRadius - m_StrokeWidth;

    //计算当前值所占百分比
    double percent = 1.0f - (double)(m_Value - m_MinValue) / (m_MaxValue - m_MinValue);

    //正弦曲线公式 y = A * sin(ωx + φ) + k

    //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度
    double w = 1 * M_PI / width; //  waterDensity * M_PI / width

    //k表示y轴偏移,可以理解为进度,取值高度的进度百分比
    double k = innerRadius * percent + m_StrokeWidth/2;

    //第一条波浪路径集合
    QPainterPath waterPath1;
    //第二条波浪路径集合
    QPainterPath waterPath2;

    //移动到左上角起始点
    waterPath1.moveTo(0, outerRadius);
    waterPath2.moveTo(0, outerRadius);

    m_WaveOffset += 0.1;
    if (m_WaveOffset > (width / 2)) {
        m_WaveOffset = 0;
    }

    for(int x = 0; x <= width; x++) {
        //第一条波浪Y轴
        double waterY1 = (double)(m_WaveHeight * sin(w * x + m_WaveOffset)) + k;

        //第二条波浪Y轴
        double waterY2 = (double)(m_WaveHeight * sin(w * x + m_WaveOffset + (width / 2 * w))) + k;

        //如果当前值为最小值则Y轴为高度
        if (this->m_Value == m_MinValue) {
            waterY1 = outerRadius;
            waterY2 = outerRadius;
        }

        //如果当前值为最大值则Y轴为0
        if (this->m_Value == m_MaxValue) {
            waterY1 = m_StrokeWidth/2;
            waterY2 = m_StrokeWidth/2;
        }

        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);
    }

    //移动到右下角结束点,整体形成一个闭合路径
    waterPath1.lineTo(width, innerRadius);
    waterPath2.lineTo(width, innerRadius);

    QPainterPath framePath;
    framePath.setFillRule(Qt::OddEvenFill);
    framePath.moveTo(baseRect.center());
    framePath.addEllipse(baseRect);


    QPainterPath clipPath;
    clipPath.setFillRule(Qt::OddEvenFill);
    baseRect.adjust(m_StrokeWidth/2,m_StrokeWidth/2,-m_StrokeWidth/2,-m_StrokeWidth/2);
    clipPath.moveTo(baseRect.center());
    clipPath.addEllipse(baseRect);

    //dataPath.addEllipse(innerRect);


    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(QPen(m_StrokeColor, m_StrokeWidth));
    //painter->setBrush(m_StrokeColor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(framePath);

    //新路径,用大路径减去波浪区域的路径,形成遮罩效果
    QPainterPath path;
    painter->setPen(Qt::NoPen);

    QLinearGradient gradient(0,m_StrokeWidth/2,0,height - m_StrokeWidth);

    //gradient.setCoordinateMode(QGradient::StretchToDeviceMode);

    gradient.setColorAt(0, m_StopColor);
    gradient.setColorAt(1.0, m_StartColor);

    QBrush brush(gradient);
    painter->setBrush(brush);

    //第一条波浪挖去后的路径

    path = clipPath.intersected(waterPath1);
    painter->drawPath(path);

    //第二条波浪挖去后的路径
    path = clipPath.intersected(waterPath2);
    painter->drawPath(path);

    painter->restore();

    m_WaveHeight = m_WaveHeight - 0.1;
    if(m_WaveHeight > 0)
    {
       this->update();
    }
}
