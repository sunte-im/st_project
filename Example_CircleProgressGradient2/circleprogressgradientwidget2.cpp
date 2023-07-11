#include "circleprogressgradientwidget2.h"
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QConicalGradient>

CircleProgressGradientWidget2::CircleProgressGradientWidget2(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 350);
    m_value = 0;

    m_colorStart = "#00b2ff";
    m_colorEnd = "#1ac881";
    m_colorHeadCircle = "#1ac881";
    m_visible = true;
}

void CircleProgressGradientWidget2::_setVisible(bool f)
{
    m_visible = f;

    update();
}

void CircleProgressGradientWidget2::setValue(int value)
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

void CircleProgressGradientWidget2::setProgressGradientColor(QString start, QString end, QString headCircle)
{
    m_colorStart = start;
    m_colorEnd = end;
    m_colorHeadCircle = headCircle;

    update();
}

void CircleProgressGradientWidget2::paintEvent(QPaintEvent*)
{
    if (!m_visible)
        return;

    QPainter painter(this);
    QPixmap pixmap(":/images/circle_base.png");       // background image
    qreal pd = m_value * 360;


    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(QPoint(0,0), pixmap);

    if (pd == 0)
        return;

    // set gradient color
    QConicalGradient conicalGrad(this->rect().center(), 94);
    conicalGrad.setColorAt(0, m_colorEnd);
    conicalGrad.setColorAt(1, m_colorStart);

    QPainterPath path;
    //path.moveTo(width()/2, 99);
    path.moveTo(200, 103);
    path.arcTo(QRectF(128, 103, 145, 145), 90, -pd);
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setBrush(QBrush(conicalGrad));
    pen.setWidth(7);

    painter.strokePath(path, pen);

    // line header circle
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(m_colorHeadCircle));
    painter.drawEllipse(path.currentPosition(), 9, 9);
    painter.setBrush(Qt::white);
    painter.drawEllipse(path.currentPosition(), 5, 5);
}
