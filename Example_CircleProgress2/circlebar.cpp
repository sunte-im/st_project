#include "circlebar.h"
#include <QPen>
#include <QPainter>
#include <QDebug>

CircleBar::CircleBar(QWidget *parent) : QWidget(parent), m_p(0)
{

}

void CircleBar::update_(qreal pp)
{
    qDebug() << __FUNCTION__ << pp;
    if (m_p == pp) return;
    m_p = pp;
    update();
}

void CircleBar::addItem(int p, QString color)
{
    qreal p_= (qreal)p/100;
    m_itemList.append(st_circlebar_item(p_, color));
    update();
}

void CircleBar::paintEvent(QPaintEvent *)
{
    int margin = 100;
    qreal max_p = 0;
    qreal total_p = 0;
    //qreal pd = m_p * 360;
    QPainter paint(this);
    paint.fillRect(rect(), Qt::white);
    paint.translate(4, 4);
    paint.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidth(50);

    for (int i = 0; i < m_itemList.size(); ++i)
    {
        st_circlebar_item item = m_itemList.at(i);
        qreal p = item.p * 360;
        QPainterPath path;
        path.moveTo(width()/2, margin);
        if (max_p > 0)
            path.arcTo(QRectF(margin, margin, width()-margin*2, height()-margin*2), 90, 360 - (total_p * 360));
        else
            path.arcTo(QRectF(margin, margin, width()-margin*2, height()-margin*2), 90, -p);

        pen.setColor(QColor(item.color));
        paint.strokePath(path, pen);

        total_p += item.p;
        if (item.p >= max_p)
            max_p = item.p;
    }


    QPainterPath path;
    path.moveTo(width()/2, margin);
    pen.setWidth(50);
    pen.setColor(QColor("#B5B6B9"));
    //pen.setCapStyle(Qt::FlatCap);
    //pen2.setDashPattern(QVector<qreal>{0.5, 1.105});
    //path2.arcTo(QRectF(100, 100, 300, 300), 90, rd);
    path.arcTo(QRectF(margin, margin, width()-margin*2, height()-margin*2), 90, 360 - (total_p * 360));
    //pen2.setDashOffset(2.2);
    paint.strokePath(path, pen);
}
