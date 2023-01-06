#include "timelinebeginendbodydialog.h"
#include "ui_timelinebeginendbodydialog.h"
#include <windows.h>
#include <WinUser.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <objidl.h> // Fixes error C2504: 'IUnknown' : base class undefined
#include <gdiplus.h>
#include <GdiPlusColor.h>
#pragma comment (lib,"Dwmapi.lib") // Adds missing library, fixes error LNK2019: unresolved external symbol __imp__DwmExtendFrameIntoClientArea
#pragma comment (lib,"user32.lib")

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

TimeLineBeginEndBodyDialog::TimeLineBeginEndBodyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeLineBeginEndBodyDialog)
{
    ui->setupUi(this);
    m_mousePressed = false;
    setFixedHeight(30);
    ui->groupBox->installEventFilter(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    m_timeLinePos = 0;
}

TimeLineBeginEndBodyDialog::~TimeLineBeginEndBodyDialog()
{
    delete ui;
}

void TimeLineBeginEndBodyDialog::setTimeLinePos(int pos)
{
    m_timeLinePos = pos;
}

void TimeLineBeginEndBodyDialog::setMousePressed(bool f)
{
    m_mousePressed = f;
}

bool TimeLineBeginEndBodyDialog::nativeEvent(const QByteArray& /*eventType*/, void* message, long* result)
{
    MSG* msg = static_cast<MSG*>(message);

    if (msg->message == WM_NCHITTEST)
    {
        //if (m_maxScreen/*isMaximized()*/)
        //{
        //    return false;
        //}

        *result = 0;
        const LONG borderWidth = 8;
        RECT winrect;
        GetWindowRect(reinterpret_cast<HWND>(winId()), &winrect);

        // must be short to correctly work with multiple monitors (negative coordinates)
        short x = msg->lParam & 0x0000FFFF;
        short y = (msg->lParam & 0xFFFF0000) >> 16;

        bool resizeWidth = minimumWidth() != maximumWidth();
        bool resizeHeight = minimumHeight() != maximumHeight();
        if (resizeWidth)
        {
            //left border
            if (x >= winrect.left && x < winrect.left + borderWidth)
            {
                *result = HTLEFT;
            }
            //right border
            if (x < winrect.right && x >= winrect.right - borderWidth)
            {
                *result = HTRIGHT;
            }
        }
        if (resizeHeight)
        {
            //bottom border
            if (y < winrect.bottom && y >= winrect.bottom - borderWidth)
            {
                *result = HTBOTTOM;
            }
            //top border
            if (y >= winrect.top && y < winrect.top + borderWidth)
            {
                *result = HTTOP;
            }
        }
        if (resizeWidth && resizeHeight)
        {
            //bottom left corner
            if (x >= winrect.left && x < winrect.left + borderWidth &&
                    y < winrect.bottom && y >= winrect.bottom - borderWidth)
            {
                *result = HTBOTTOMLEFT;
            }
            //bottom right corner
            if (x < winrect.right && x >= winrect.right - borderWidth &&
                    y < winrect.bottom && y >= winrect.bottom - borderWidth)
            {
                *result = HTBOTTOMRIGHT;
            }
            //top left corner
            if (x >= winrect.left && x < winrect.left + borderWidth &&
                    y >= winrect.top && y < winrect.top + borderWidth)
            {
                *result = HTTOPLEFT;
            }
            //top right corner
            if (x < winrect.right && x >= winrect.right - borderWidth &&
                    y >= winrect.top && y < winrect.top + borderWidth)
            {
                *result = HTTOPRIGHT;
            }
        }

        if (*result != 0)
            return true;

        QWidget *action = QApplication::widgetAt(QCursor::pos());
        if (action == this){
            *result = HTCAPTION;
            return true;
        }
    }

    return false;
}

void TimeLineBeginEndBodyDialog::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor("#FF00FF"));
}

bool TimeLineBeginEndBodyDialog::eventFilter(QObject* obj, QEvent* e)
{
    //if (obj != ui->groupBox)
    //    return QWidget::eventFilter(obj, e);

    QMouseEvent* mEvt = (QMouseEvent*)e;

    if (e->type() == QEvent::MouseButtonPress)
    {
        if (mEvt->button() == Qt::LeftButton)
        {
            m_mousePressed = true;
            m_lastMouseMovePoint = mEvt->pos();
        }
    }
    else if (e->type() == QEvent::MouseMove)
    {
        if (m_mousePressed)
        {
            QPoint diff = mEvt->pos() - m_lastMouseMovePoint;
            if (m_timeLinePos < 0)
            {
                if (diff.x() < 0)
                    return QWidget::eventFilter(obj, e);

                emit moveSignals();
                return QWidget::eventFilter(obj, e);
            }
            else
            {
                move(mapToGlobal(QPoint(diff.x(), 0)));
            }
            emit moveSignals();
        }
    }
    else if (e->type() == QEvent::MouseButtonRelease)
    {
        m_mousePressed = false;
        emit moveEndSignals();

        if (m_timeLinePos < 0)
            m_timeLinePos = 0;
    }

    return QWidget::eventFilter(obj, e);
}

void TimeLineBeginEndBodyDialog::resizeEvent(QResizeEvent*)
{
    if (m_timeLinePos < 0)
        setMouseTracking(false);

    emit moveEndSignals();
}
