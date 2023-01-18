#ifndef TIMELINEWIDGET2_H
#define TIMELINEWIDGET2_H

#include <QWidget>

struct st_timeline
{
    int begin;
    int end;
};

class TimeLineWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit TimeLineWidget2(QWidget *parent = nullptr);
    ~TimeLineWidget2();

    void addTime(QTime begin, QTime end);
    void addTime(int begin, int end);
    void clear();
    void updateUi();

private:
    QList<st_timeline> m_timeLineList;

protected:
    void paintEvent(QPaintEvent *);
    void drawTime(QPainter& p);
};

#endif // TIMELINEWIDGET2_H
