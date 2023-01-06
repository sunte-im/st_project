#include "timelinewidget.h"
#include "ui_timelinewidget.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

TimeLineWidget::TimeLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeLineWidget)
{
    ui->setupUi(this);
    m_mousePressed = false;
    m_startPos = 0;
    m_endPos = 1440+28; //Width

    m_indicatorMoveFlag = false;
    m_indicatorPos = 0;
    m_indicatorColor = Qt::yellow;
    m_useIndicator = false;

    ui->groupBox_body->installEventFilter(this);

    //ui->splitter->handle(2)->installEventFilter(this);

    setFixedSize(1440+28, 60);
}

TimeLineWidget::~TimeLineWidget()
{
    delete ui;
}

QRect TimeLineWidget::indicatorRect()
{
    if (m_indicatorPos<0)
        m_indicatorPos = 0;
    else if (m_indicatorPos>m_endPos)
        m_indicatorPos = m_endPos;

    int x = m_indicatorPos;
    int y = 5;
    int w = 1;
    int h = height()-5;
    return QRect(x, y, w, h);
}

int TimeLineWidget::indicatorPos()
{
    return m_indicatorPos;
}

void TimeLineWidget::setIndicatorPos(int sec)
{
    int position = (int)(sec/60);
    if (position<0)
        position = 0;
    else if (position>=m_endPos)
        position = m_endPos;

    //qDebug() << "SsSingleSearchMap::setIndicatorPos"
    //         << " sec:" << sec
    //         << " position: " << position;

    m_indicatorPos = position;
    update();
}

int TimeLineWidget::indicatorToTime_sec()
{
    int sec = (int)(m_indicatorPos*60);
    if (sec<0)
        sec = 0;
    else if (sec>24*60*60)
        sec = 24*60*60;

    qDebug() << __FUNCTION__ << sec;
    return sec;
}

void TimeLineWidget::setUseIndicator(bool f)
{
    m_useIndicator = f;
}

void TimeLineWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor("#37424B"));

    drawBody(p);

    if (m_useIndicator)
        drawIndicator(p);
}

void TimeLineWidget::drawBody(QPainter& p)
{
    int hourCount = m_endPos - m_startPos + 1;
    if (hourCount <= 0) return;

#if 0
    int x = width()/4;
    int h = height();

    p.setPen(QColor("#DDDDDD"));


    p.drawText(0, 0, 14, h+1, Qt::AlignCenter, "0");
    p.drawText(x-7, 0, 14, h+1, Qt::AlignCenter, "6");
    p.drawText(x*2-7, 0, 14, h+1, Qt::AlignCenter, "12");
    p.drawText(x*3-7, 0, 14, h+1, Qt::AlignCenter, "18");
    p.drawText(width()-15, 0, 14, h+1, Qt::AlignCenter, "24");
#endif

    int x = (width()-28)/24;
    int h = height();

    QFont font = QApplication::font();
    font.setPixelSize(13);
    p.setFont(font);
    p.setPen(QColor("#DDDDDD"));


    for (int i = 0; i < 24; ++i)
        p.drawText(x*i, 0, 14, h-20, Qt::AlignCenter, QString::number(i));
    p.drawText(width()-25, 0, 14, h-20, Qt::AlignCenter, "24");

    p.setPen(QColor(Qt::black));
    QRect rect(0,0,width()-1,height()-1);
    p.drawRect(rect);
    rect.adjust(1,1,-1,-1);
}

void TimeLineWidget::drawIndicator(QPainter& p)
{
    QColor color = m_indicatorColor;
    p.fillRect(indicatorRect(), color);
}

void TimeLineWidget::mousePressEvent(QMouseEvent* evt)
{
    if (!m_useIndicator)
        return;

    if ( !(evt->button() & Qt::LeftButton) ) return;

    m_lastIndicatorPoint = evt->pos();

    update(indicatorRect());
    m_indicatorPos = evt->pos().x();
    update(indicatorRect());

    m_indicatorMoveFlag = true;
}

void TimeLineWidget::mouseMoveEvent(QMouseEvent* evt)
{
    if (!m_useIndicator)
        return;

    if (m_indicatorMoveFlag)
    {
        update(indicatorRect());
        m_indicatorPos = evt->pos().x();
        update(indicatorRect());

        m_lastIndicatorPoint = evt->pos();
    }
}

void TimeLineWidget::mouseReleaseEvent(QMouseEvent*)
{
    if (!m_useIndicator)
        return;

    m_indicatorMoveFlag = false;
    update(indicatorRect());

    int sec = indicatorToTime_sec();
    emit indicator_sec_signals(sec);
}

bool TimeLineWidget::eventFilter(QObject* obj, QEvent* e)
{
    if (obj != ui->groupBox_body)
        return QWidget::eventFilter(obj, e);

    //qDebug() << __FUNCTION__ << obj->objectName();

    if (e->type() == QEvent::Resize)
    {
        qDebug() << __FUNCTION__ << "body : " << ui->groupBox_body->geometry();
        int beginPos = ui->groupBox_body->geometry().x()-14;
        int endPos = ui->groupBox_body->width() +14 + beginPos;
        //qDebug() << __FUNCTION__ << "begin : " << beginPos << "  end : " << endPos;

        if (endPos >= 1440)
            endPos = 1440;

        emit begin_end_signals(beginPos*60, endPos*60);
    }

    return QWidget::eventFilter(obj, e);
}
