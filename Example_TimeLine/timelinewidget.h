#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>

namespace Ui {
class TimeLineWidget;
}
class TimeLineWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::TimeLineWidget *ui;
    bool m_mousePressed;
    int m_startPos;
    int m_endPos;
    bool m_indicatorMoveFlag;
    QPoint m_lastIndicatorPoint;
    int m_indicatorPos;
    QColor m_indicatorColor;
    bool m_useIndicator;

public:
    explicit TimeLineWidget(QWidget *parent = nullptr);
    ~TimeLineWidget();

    QRect indicatorRect();
    int indicatorPos();
    void setIndicatorPos(int sec);
    int indicatorToTime_sec();
    void setUseIndicator(bool f);

protected:
    void paintEvent(QPaintEvent *);
    void drawBody(QPainter& p);
    void drawIndicator(QPainter& p);

    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

    bool eventFilter(QObject*, QEvent*);

signals:
    void indicator_sec_signals(int sec);
    void begin_end_signals(int beginSec, int endSec);
};

#endif // TIMELINEWIDGET_H
