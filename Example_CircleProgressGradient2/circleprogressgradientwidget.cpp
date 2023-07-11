#include "circleprogressgradientwidget.h"
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QConicalGradient>

CircleProgressGradientWidget::CircleProgressGradientWidget(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(295, 295);
    m_value = 0;

    m_colorStart = "#00b2ff";
    m_colorEnd = "#1ac881";
    m_colorHeadCircle = "#1ac881";
}

CircleProgressGradientWidget::~CircleProgressGradientWidget()
{
}

void CircleProgressGradientWidget::setValue(int value)
{
    qreal _real = (qreal)value/100;

    if (m_value == _real)
        return;

    m_value = _real;

    //qDebug() << __FUNCTION__ << " value: " << value
    //         << " _real: " << _real
    //         << " value: " << m_value;

    update();
}

void CircleProgressGradientWidget::setProgressGradientColor(QString start, QString end, QString headCircle)
{
    m_colorStart = start;
    m_colorEnd = end;
    m_colorHeadCircle = headCircle;

    update();
}

void CircleProgressGradientWidget::paintEvent(QPaintEvent*)
{
    QPixmap pixmap(":/images/img_printing.png");       // background image
    qreal pd = m_value * 360;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(QPoint(0,0), pixmap);

    if (pd == 0)
        return;

    // set gradient color
    QConicalGradient conicalGrad(this->rect().center(), 94);
    conicalGrad.setColorAt(0, m_colorEnd);
    conicalGrad.setColorAt(1, m_colorStart);

    QPainterPath path;
    path.moveTo(width()/2, 40);
    path.arcTo(QRectF(40, 40, 210, 210), 90, -pd);
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setBrush(QBrush(conicalGrad));
    pen.setWidth(12);

    painter.strokePath(path, pen);

    // line header circle
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(m_colorHeadCircle));
    painter.drawEllipse(path.currentPosition(), 13, 13);
    painter.setBrush(Qt::white);
    painter.drawEllipse(path.currentPosition(), 9, 9);
}
