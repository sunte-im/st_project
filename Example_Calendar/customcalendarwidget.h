#ifndef CUSTOMCALENDARWIDGET_H
#define CUSTOMCALENDARWIDGET_H

#include <QCalendarWidget>

class CustomCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
private:
    bool m_controlPressFlag;
    bool m_mousePressFlag;
    QDate m_startDate;
    QDate m_lastDate;
    QList<QDate> m_moveDateList;

public:
    explicit CustomCalendarWidget(QWidget *parent = nullptr);
    ~CustomCalendarWidget();

    void selectDate(QDate date);
    void selectDate(int yyyy, int mm, int dd);
    void clearSelectDate(QDate date);
    void clear();

protected:
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void slot_clicked(QDate date);
    void timeout_mouseReleaseTimer();
};

#endif // CUSTOMCALENDARWIDGET_H
