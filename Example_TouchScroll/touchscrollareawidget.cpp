#include "touchscrollareawidget.h"
#include <QDebug>
#include <QScrollBar>
#include <QEvent>
#include <QMouseEvent>

TouchScrollAreaWidget::TouchScrollAreaWidget(QWidget *parent) : QScrollArea(parent)
{
    m_type = TYPE_NORMAL_SCROLL;
    m_mousePressFlag = false;
    installEventFilter(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_upCount = 0;
    m_downCount = 0;
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(valueChangedVerticalScrollBar(int)));
}

void TouchScrollAreaWidget::pressCurrentPos(QEvent* e)
{
    QMouseEvent *me = static_cast<QMouseEvent*>(e);
    m_prevPos = me->globalPos();
}

void TouchScrollAreaWidget::moveUpDown(QEvent* e)
{
    QMouseEvent *me = static_cast<QMouseEvent*>(e);
    QPoint curPos = me->globalPos();

    if (m_type == TYPE_LEFT_RIGHT_SCROLL)
    {
        int prevX = m_prevPos.x();
        int currnetX = curPos.x();
        int moveValue = abs(prevX) - abs(currnetX);
        if (prevX > currnetX)
        {
            //qDebug() << __FUNCTION__ << " .. LEFT";
            scrollLeft(abs(moveValue));
        }
        else if (prevX < currnetX)
        {
            //qDebug() << __FUNCTION__ << " .. RIGHT";
            scrollRight(abs(moveValue));
        }
    }
    else
    {
        int prevY = m_prevPos.y();
        int currnetY = curPos.y();
        int moveValue = abs(prevY) - abs(currnetY);
        if (prevY > currnetY)
        {
            //qDebug() << __FUNCTION__ << " .. UP";
            m_downCount = 0;
            scrollUp(abs(moveValue));
        }
        else if (prevY < currnetY)
        {
            //qDebug() << __FUNCTION__ << " .. DOWN";
            m_upCount = 0;
            scrollDown(abs(moveValue));
        }
    }


    m_prevPos = curPos;
}

void TouchScrollAreaWidget::scrollUp(int moveValue)
{
    if (m_type == TYPE_NORMAL_SCROLL)
    {
        int value = verticalScrollBar()->value();
        int max = verticalScrollBar()->maximum();
        value = value + moveValue;
        if (value > max) value = max;

        verticalScrollBar()->setValue(value);
    }
    else if (m_type == TYPE_CENTER_SELECT)
    {
        m_upCount = m_upCount + moveValue;

        if (m_upCount < 50)
            return;

        int value = verticalScrollBar()->value();
        int max = verticalScrollBar()->maximum();
        //qDebug() << __FUNCTION__ << " value : " << value << " max : " << max;
        //qDebug() << __FUNCTION__ << moveValue;
        value = value + 50;
        if (value > max) value = max;

        int _value = value/50;
        value = 50*_value;

        verticalScrollBar()->setValue(value);
        m_upCount = 0;

        //qDebug() << __FUNCTION__ << value;
    }
}

void TouchScrollAreaWidget::scrollDown(int moveValue)
{
    if (m_type == TYPE_NORMAL_SCROLL)
    {
        int value = verticalScrollBar()->value();
        int min = verticalScrollBar()->minimum();
        value = value - moveValue;
        if (value < min) value = min;

        verticalScrollBar()->setValue(value);
    }
    else if (m_type == TYPE_CENTER_SELECT)
    {
        m_downCount = m_downCount + moveValue;

        if (m_downCount < 50)
            return;

        int value = verticalScrollBar()->value();
        int min = verticalScrollBar()->minimum();
        //qDebug() << __FUNCTION__ << " value : " << value << " min : " << min;
        //qDebug() << __FUNCTION__ << moveValue;
        value = value - 50;
        if (value < min) value = min;

        if (value < 1)
            value = 1;

        int _value = value/50;
        value = 50*_value;

        verticalScrollBar()->setValue(value);
        m_downCount = 0;

        //qDebug() << __FUNCTION__ << value;
    }
}

void TouchScrollAreaWidget::scrollLeft(int moveValue)
{
    int value = horizontalScrollBar()->value();
    int max = horizontalScrollBar()->maximum();
    value = value + moveValue;
    if (value > max) value = max;

    horizontalScrollBar()->setValue(value);
}

void TouchScrollAreaWidget::scrollRight(int moveValue)
{
    int value = horizontalScrollBar()->value();
    int min = horizontalScrollBar()->minimum();
    value = value - moveValue;
    if (value < min) value = min;

    horizontalScrollBar()->setValue(value);
}

void TouchScrollAreaWidget::setType(TouchScrollAreaWidget::TYPE type)
{
    m_type = type;
}

void TouchScrollAreaWidget::setValue(int num)
{
    verticalScrollBar()->setValue(num);
}

bool TouchScrollAreaWidget::eventFilter(QObject* obj, QEvent* e)
{
    if (e->type() == QEvent::MouseButtonPress)
    {
        if (obj == this)
        {
            m_mousePressFlag = true;
            pressCurrentPos(e);
            //qDebug() << "TouchScrollAreaWidget::eventFilter MouseButtonPress";
        }
    }
    else if (e->type() == QEvent::MouseMove)
    {
        if (m_mousePressFlag)
        {
            moveUpDown(e);
            //qDebug() << "TouchScrollAreaWidget::eventFilter MouseMove...1";
        }
    }
    else if (e->type() == QEvent::MouseButtonRelease)
    {
        if (m_mousePressFlag)
        {
            m_mousePressFlag = false;
        }
    }

    return false;
}

void TouchScrollAreaWidget::valueChangedVerticalScrollBar(int value)
{
    //qDebug() << __FUNCTION__ << value;

    emit selectCenterSignals(value);
}
