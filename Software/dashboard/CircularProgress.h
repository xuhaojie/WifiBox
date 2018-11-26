
#ifndef __CIRCULARPROGRESS_H__
#define __CIRCULARPROGRESS_H__
#include <QtQuick>
#include <QQuickPaintedItem>

class CircularProgress : public QQuickPaintedItem
{
    Q_OBJECT
/*
    Q_PROPERTY(bool minValue READ m_MinValueValue WRITE m_MinValueValue)
    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth)
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
*/
    Q_PROPERTY(QColor basicColor READ getBasicColor WRITE setBasicColor)
    Q_PROPERTY(QColor startColor READ getStartColor WRITE setStartColor)
    Q_PROPERTY(QColor stopColor READ getStopColor WRITE setStopColor)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double strokeWidth READ getStrokeWidth WRITE setStrokeWidth)
//    Q_PROPERTY(double startAngle READ getStartAngle WRITE setStartAngle)
//    Q_PROPERTY(double stopAngle READ getStopAngle WRITE setStopAngle)
    Q_PROPERTY(bool counterClockwise READ getCounterClockwise WRITE setCounterClockwise)
public:
    CircularProgress(QQuickItem *parent = 0);
    ~CircularProgress();

    void paint(QPainter *painter);


protected:
    QColor m_BasicColor;
    QColor m_StartColor;
    QColor m_StopColor;

    double m_StartAngle;
    double m_StopAngle;

    bool m_CounterClockwise;

    double m_StrokeWidth;


    static const int PositionLeft = 180;
    static const int PositionTop = 90;
    static const int PositionRight = 0;
    static const int PositionBottom = -90;

    QColor getBasicColor(){return m_BasicColor;}
    void setBasicColor(QColor color){m_BasicColor = color;}
    QColor getStartColor(){return m_StartColor;}
    void setStartColor(QColor color){m_StartColor = color;}
    QColor getStopColor(){return m_StopColor;}
    void setStopColor(QColor color){m_StopColor = color;}

    double getStartAngle(){return m_StartAngle;}
    void setStartAngle(double value){ m_StartAngle = value;}
    double getStopAngle(){return m_StopAngle;}
    void setStopAngle(double value){ m_StopAngle = value;}
    bool getCounterClockwise(){return m_CounterClockwise;}
    void setCounterClockwise(bool value){ m_CounterClockwise = value;}

    double getStrokeWidth(){return m_StrokeWidth;}
    void setStrokeWidth(double value){ m_StrokeWidth = value;}



    /**
     * @brief Return position (in degrees) of minimum value.
     * \sa setNullPosition
     */
    double nullPosition() const { return m_nullPosition; }
    /**
     * @brief Defines position of minimum value.
     * @param position position on the circle (in degrees) of minimum value
     * \sa nullPosition
     */
    void setNullPosition(double position);


    /**
     * @brief Sets width of the outline circle pen.
     * @param penWidth width of the outline circle pen (in pixels)
     */
    void setOutlinePenWidth(double penWidth);
    /**
     * @brief Returns width of the outline circle pen.
     */
    double outlinePenWidth() const { return m_outlinePenWidth; }

    /**
     * @brief Sets width of the data circle pen.
     * @param penWidth width of the data circle pen (in pixels)
     */
    void setDataPenWidth(double penWidth);
    /**
     * @brief Returns width of the data circle pen.
     */
    double dataPenWidth() const { return m_dataPenWidth; }

    /**
     * @brief Sets colors of the visible data and makes gradient brush from them.
     * Gradient colors can be set for \a Donut and \a Pie styles (see setBarStyle() function).
     *
     * *Warning*: this function will override widget's `palette()` to set dynamically created gradient brush.
     *
     * @param stopPoints List of colors (should have at least 2 values, see Qt's \a QGradientStops for more details).
     * Color value at point 0 corresponds to the minimum() value, while color value at point 1
     * corresponds to the maximum(). Other colors will be distributed accordingly to the defined ranges (see setRange()).
     */
    void setDataColors(const QGradientStops& stopPoints);


    /**
     * @brief Returns current value shown on the widget.
     * \sa setValue()
     */
    double getValue() const { return m_Value; }
    /**
     * @brief Returns minimum of the allowed value range.
     * \sa setMinValue, setRange
     */
    double getMinValue() const { return m_MinValue; }
    /**
     * @brief Returns maximum of the allowed value range.
    * \sa setMaxValue, setRange
     */
    double getMaxValue() const { return m_MaxValue; }


    void setValue(double val);


    /**
     * @brief Defines minimum und maximum of the allowed value range.
     * If the current value does not fit into the range, it will be automatically adjusted.
     * @param min minimum of the allowed value range
     * @param max maximum of the allowed value range
     */
    void setRange(double min, double max);
    /**
     * @brief Defines minimum of the allowed value range.
     * If the current value does not fit into the range, it will be automatically adjusted.
     * @param min minimum of the allowed value range
     * \sa setRange
     */
    void setMinValue(double min);
    /**
     * @brief Defines maximum of the allowed value range.
     * If the current value does not fit into the range, it will be automatically adjusted.
     * @param max maximum of the allowed value range
     * \sa setRange
     */
    void setMaxValue(double max);
    /**
     * @brief Sets a value which will be shown on the widget.
     * @param val must be between minimum() and maximum()
     */


protected:


    virtual void drawBase(QPainter* painter, const QRectF& baseRect, const QRectF &innerRect);
    virtual void drawValue(QPainter* painter, const QRectF& baseRect, double value, double arcLength, const QRectF & innerRect
                           , double innerRadius);

    virtual QSize minimumSizeHint() const { return QSize(32,32); }

    virtual bool hasHeightForWidth() const { return true; }
    virtual int heightForWidth(int w) const { return w; }

    double m_MinValue;
    double m_MaxValue;
    double m_Value;

    double m_nullPosition;

    double m_outlinePenWidth, m_dataPenWidth;

    static const int UF_VALUE = 1;
    static const int UF_PERCENT = 2;
    static const int UF_MAX = 4;
    int m_updateFlags;

};

#endif // __CIRCULARPROGRESS_H__
