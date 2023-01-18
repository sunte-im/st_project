#include "timelinewidget2.h"
#include <QDebug>
#include <QPainter>
#include <QTime>

TimeLineWidget2::TimeLineWidget2(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(1440, 30);
}

TimeLineWidget2::~TimeLineWidget2()
{

}

void TimeLineWidget2::addTime(QTime begin, QTime end)
{
    addTime(QTime(0, 0, 0).secsTo(begin), QTime(0, 0, 0).secsTo(end));
}

void TimeLineWidget2::addTime(int begin, int end)
{
    if (begin > end)
        return;

    st_timeline timeline;
    timeline.begin = begin;
    timeline.end = end;

    m_timeLineList.append(timeline);
}

void TimeLineWidget2::clear()
{
    m_timeLineList.clear();

    updateUi();
}

void TimeLineWidget2::updateUi()
{
    update();
}

void TimeLineWidget2::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor("#697178"));

    if (m_timeLineList.size() < 1)
        return;

    drawTime(p);
}

void TimeLineWidget2::drawTime(QPainter& p)
{
    foreach (st_timeline timeline, m_timeLineList)
    {
        qDebug() << __FUNCTION__ << timeline.begin << timeline.end;
        p.fillRect(timeline.begin, 0, timeline.end-timeline.begin, height(), QColor("#BF0000"));
    }
}
