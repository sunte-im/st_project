#include "customcalendarwidget.h"
#include <QDebug>
#include <QTableView>
#include <QTextCharFormat>
#include <QMouseEvent>
#include <QTimer>

CustomCalendarWidget::CustomCalendarWidget(QWidget *parent) : QCalendarWidget(parent)
{
    m_mousePressFlag = false;
    m_controlPressFlag = false;

    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    setFocusPolicy(Qt::ClickFocus);
    setGridVisible(true);
    QTableView* view = findChild<QTableView*>("qt_calendar_calendarview");
    //view->installEventFilter(this);
    view->viewport()->installEventFilter(this);
    connect(this, SIGNAL(clicked(QDate)), this, SLOT(slot_clicked(QDate)));
    setStyleSheet("QTableView{selection-background-color: rgba(0,0,0,0); selection-color:black;}");
}

CustomCalendarWidget::~CustomCalendarWidget()
{

}

void CustomCalendarWidget::selectDate(QDate date)
{
    setStyleSheet("QTableView{selection-background-color: rgb(228, 97, 122); selection-color:white;}");
    QTextCharFormat textFormat;
    textFormat.setBackground(QBrush(QColor(228, 97, 122), Qt::SolidPattern));
    textFormat.setForeground(QBrush(Qt::white, Qt::SolidPattern));
    //textFormat.setFontWeight(QFont::Bold);

    setDateTextFormat(date, textFormat);
}

void CustomCalendarWidget::selectDate(int yyyy, int mm, int dd)
{
    QDate date;
    date.setDate(yyyy, mm, dd);
    selectDate(date);
}

void CustomCalendarWidget::clearSelectDate(QDate date)
{
    QMap<QDate, QTextCharFormat> dateMap = dateTextFormat();
    if (dateMap.contains(date))
    {
        dateMap.remove(date);
    }

    clear();
    foreach (QDate _date, dateMap.keys())
    {
        selectDate(_date);
    }
    setStyleSheet("QTableView{selection-background-color: rgba(0,0,0,0); selection-color:black;}");
}

void CustomCalendarWidget::clear()
{
    //qDebug() << __FUNCTION__ << dateTextFormat();

    setStyleSheet("QTableView{selection-background-color: rgba(0,0,0,0); selection-color:black;}");
    setDateTextFormat(QDate(), QTextCharFormat());
}

void CustomCalendarWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control)
    {
        m_controlPressFlag = true;
        event->accept();
    }
    else
    {
        if (dateTextFormat().contains(selectedDate()))
            setStyleSheet("QTableView{selection-background-color: rgb(228, 97, 122); selection-color:white;}");
        else
            setStyleSheet("QTableView{selection-background-color: rgba(0,0,0,0); selection-color:black;}");

        event->ignore();
    }

    return QCalendarWidget::keyPressEvent(event);
}

void CustomCalendarWidget::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control)
        m_controlPressFlag = false;
}

bool CustomCalendarWidget::eventFilter(QObject* obj, QEvent* e)
{
    if (e->type() == QEvent::MouseButtonPress)
    {
        if (m_controlPressFlag)
            return QObject::eventFilter(obj, e);

        QTableView* view = findChild<QTableView*>("qt_calendar_calendarview");
        QMouseEvent *me = static_cast<QMouseEvent *>(e);
        QModelIndex index = view->indexAt(me->pos());

        //qDebug() << __FUNCTION__
        //         << index.row() << index.column() << index.data();

        int row = index.row();
        int day = index.data().toInt();
        QDate date;
        date.setDate(yearShown(), monthShown(), day);

        if (row < 2 && day > 15)
        {
            date.setDate(yearShown(), monthShown(), 1);
            QDate _date = date.addMonths(-1);
            date.setDate(_date.year(), _date.month(), day);
            //qDebug() << __FUNCTION__
            //         << "Press _date : " << _date
            //         << "Press date1 : " << date;
        }

        if (row > 4 && day < 15)
        {
            date.setDate(yearShown(), monthShown(), 1);
            QDate _date = date.addMonths(1);
            date.setDate(_date.year(), _date.month(), day);

            //qDebug() << __FUNCTION__
            //         << "Press date1 : " << date;
        }

        m_startDate = date;

        clear();
        setSelectedDate(m_startDate);
        selectDate(m_startDate);
        //qDebug() << "CustomCalendarWidget::eventFilter MouseButtonPress" << m_startDate;

        m_mousePressFlag = true;


    }
    else if (e->type() == QEvent::MouseMove)
    {
        if (m_mousePressFlag)
        {
            QTableView* view = findChild<QTableView*>("qt_calendar_calendarview");
            QMouseEvent *me = static_cast<QMouseEvent *>(e);
            QModelIndex index = view->indexAt(me->pos());


            int row = index.row();
            int day = index.data().toInt();
            QDate date;
            date.setDate(yearShown(), monthShown(), day);

            if (row < 2 && day > 15)
            {
                date.setDate(yearShown(), monthShown(), 1);
                QDate _date = date.addMonths(-1);
                date.setDate(_date.year(), _date.month(), day);
            }

            if (row > 4 && day < 15)
            {
                date.setDate(yearShown(), monthShown(), 1);
                QDate _date = date.addMonths(1);
                date.setDate(_date.year(), _date.month(), day);
            }

            //qDebug() << "CustomCalendarWidget::eventFilter MouseMove" << date;

            qint64 daysBetween = date.toJulianDay() -  m_startDate.toJulianDay();
            //qDebug() << "CustomCalendarWidget::eventFilter daysBetween: " << daysBetween;

            if (qAbs(daysBetween) > 60)
                return QObject::eventFilter(obj, e);

            clear();
            selectDate(m_startDate);
            if (m_startDate > date)
            {
                for (int i = 0; i < qAbs(daysBetween); ++i)
                {
                    QDate _date = m_startDate;
                    _date = _date.addDays(-i-1);
                    selectDate(_date);

                    m_lastDate = _date;
                }

            }
            else if (m_startDate < date)
            {
                for (int i = 0; i < qAbs(daysBetween); ++i)
                {
                    QDate _date = m_startDate;
                    _date = _date.addDays(i+1);
                    selectDate(_date);

                    m_lastDate = _date;
                }
            }
        }
    }
    else if (e->type() == QEvent::MouseButtonRelease)
    {
        if (m_mousePressFlag)
        {
            m_mousePressFlag = false;
        }
    }

    return QObject::eventFilter(obj, e);
}

void CustomCalendarWidget::slot_clicked(QDate date)
{
    //qDebug() << __FUNCTION__ << date << m_controlPressFlag;
    if (m_controlPressFlag)
    {
        if (dateTextFormat().contains(date))
            clearSelectDate(date);
        else
            selectDate(date);
    }
}
