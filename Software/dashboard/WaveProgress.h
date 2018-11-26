#ifndef __WAVEPROGRESS_H__
#define __WAVEPROGRESS_H__
#include <QtQuick>
#include <QQuickPaintedItem>

class WaveProgress : public QQuickPaintedItem
{  
    Q_OBJECT  
/*
    Q_PROPERTY(bool minValue READ m_MinValueValue WRITE m_MinValueValue)
    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth)  
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
*/
    Q_PROPERTY(QColor strokeColor READ getStrokeColor WRITE setStrokeColor)
    Q_PROPERTY(QColor startColor READ getStartColor WRITE setStartColor)
    Q_PROPERTY(QColor stopColor READ getStopColor WRITE setStopColor)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double targetValue READ getTargetValue WRITE setTargetValue)
    Q_PROPERTY(double strokeWidth READ getStrokeWidth WRITE setStrokeWidth)

public:  
    WaveProgress(QQuickItem *parent = 0);
    ~WaveProgress();
/*
    bool isEnabled() const{ return m_bEnabled; }  
    void setEnabled(bool enabled){ m_bEnabled = enabled; }  
  
    int penWidth() const { return m_pen.width(); }  
    void setPenWidth(int width) { m_pen.setWidth(width); }  
  
    QColor penColor() const { return m_pen.color(); }  
    void setPenColor(QColor color) { m_pen.setColor(color); }  
  
    Q_INVOKABLE void clear();  
    Q_INVOKABLE void undo();  
*/
    void paint(QPainter *painter);  
  
  
protected:  


    QColor getStrokeColor(){return m_StrokeColor;}
    void setStrokeColor(QColor color){m_StrokeColor = color;}

    QColor getStartColor(){return m_StartColor;}
    void setStartColor(QColor color){m_StartColor = color;}

    QColor getStopColor(){return m_StopColor;}
    void setStopColor(QColor color){m_StopColor = color;}

    double getStrokeWidth(){return m_StrokeWidth;}
    void setStrokeWidth(double value){m_StrokeWidth = value;}

    double getValue() const { return m_Value; }
    void setValue(double val);

    double getMinValue() const { return m_MinValue; }
    void setMinValue(double min);

    double getMaxValue() const { return m_MaxValue; }
    void setMaxValue(double max);

    double getTargetValue() const { return m_TargetValue; }
    void setTargetValue(double target)
    {
        if(m_TargetValue != target)
        {
            m_TargetValue = target;
            m_WaveHeight = this->height() / 20;
            this->update();
        }
    }


protected:
    QColor m_StrokeColor;
    QColor m_StartColor;
    QColor m_StopColor;
    double m_StrokeWidth;

    double m_MinValue, m_MaxValue;
    double m_Value;
    double m_TargetValue;
    double m_WaveOffset;
    double m_WaveHeight;


};  
  
#endif // __WAVEPROGRESS_H__
