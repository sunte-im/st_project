#include "circlemovewidget.h"
#include <QPainter>
#include <QVariantAnimation>
#include <QDebug>

CircleMoveWidget::CircleMoveWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(294,294);
    m_animation = new QVariantAnimation(this);
    m_animation->setDuration(800);
    m_animation->setEasingCurve(QEasingCurve::InOutCirc);
    connect(m_animation, SIGNAL(valueChanged(const QVariant&)), this,
            SLOT(valueChangedFromAnimation(const QVariant&)));
    connect(m_animation, SIGNAL(finished()), this,SLOT(finishedFromAnimation()));
    m_currentStep = STEP_1;
    m_startAngle = 90;
}

CircleMoveWidget::~CircleMoveWidget()
{
    m_animation->stop();
}

void CircleMoveWidget::moveLeft()
{
    if (m_animation->state() != QAbstractAnimation::Stopped)
        return;

    if (m_currentStep == STEP_1) m_currentStep = STEP_3;
    else if (m_currentStep == STEP_2) m_currentStep = STEP_1;
    else if (m_currentStep == STEP_3) m_currentStep = STEP_2;

    m_animation->setStartValue(m_startAngle);
    m_animation->setEndValue(m_startAngle+120);
    m_animation->start();
}

void CircleMoveWidget::moveRight()
{
    if (m_animation->state() != QAbstractAnimation::Stopped)
        return;

    if (m_currentStep == STEP_1) m_currentStep = STEP_2;
    else if (m_currentStep == STEP_2) m_currentStep = STEP_3;
    else if (m_currentStep == STEP_3) m_currentStep = STEP_1;

    m_animation->setStartValue(m_startAngle);
    m_animation->setEndValue(m_startAngle-120);
    m_animation->start();
}

CircleMoveWidget::STEP CircleMoveWidget::getCurrnetStep()
{
    return m_currentStep;
}

void CircleMoveWidget::paintEvent(QPaintEvent*)
{
    QPixmap pixmap(":/img_scan_down.png");
    QRectF moveRectangle(43.0, 43.0, 207.0, 207.0);
    QRectF lineRectangle(39.0, 39.0, 215.0, 215.0);
    //int startAngle = -30 * 16;
    int startAngle = m_startAngle * 16;     // startAngle: -30, 90, 210
    int spanAngle = 120 * 16;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(QPoint(0,0), pixmap);

    // shadow
    if (m_animation->state() == QAbstractAnimation::Stopped)
    {
        QRectF shadowRectangle;
        for (int i = 0; i < 3; ++i)
        {
            int xy = 39;
            int wh = 215;
            if (m_currentStep == STEP_1)
                shadowRectangle.setRect(xy+i+1, xy+i+1, wh-i, wh-i);
            else if (m_currentStep == STEP_2)
                shadowRectangle.setRect(xy-i, xy+i+1, wh-i, wh-i);
            else if (m_currentStep == STEP_3)
                shadowRectangle.setRect(xy, xy-i, wh-i, wh-i);

            painter.setBrush(QColor(133,133,133,i*30));
            painter.drawPie(shadowRectangle, startAngle, spanAngle);
        }
    }

    // out line gradient drawPie
    QLinearGradient linearGrad(QPointF(width()/2, 0), QPointF(width()/2, height()));
    linearGrad.setColorAt(0, "#00ffa7");
    linearGrad.setColorAt(0.5, "#00c6f1");
    linearGrad.setColorAt(1, "#007df1");
    painter.setBrush(QBrush(linearGrad));
    painter.drawPie(lineRectangle, startAngle, spanAngle);

    // main drawPie
    QPen pen;
    pen.setColor("#FDFDFD");
    painter.setPen(pen);
    painter.setBrush(QBrush("#FDFDFD"));
    painter.drawPie(moveRectangle, startAngle, spanAngle);

    // center circle
    QLinearGradient radialGrad(QPointF(width()/2, height()/2-45), QPointF(width()/2, height()/2+45));
    radialGrad.setColorAt(0, "#00ffa7");
    radialGrad.setColorAt(0.5, "#00c6f1");
    radialGrad.setColorAt(1, "#007df1");
    painter.setBrush(QBrush(radialGrad));
    painter.drawEllipse(width()/2-45,height()/2-45,90,90);
}

void CircleMoveWidget::valueChangedFromAnimation(const QVariant & value)
{
    //qDebug() << "valueChangedFromAnimation value: " << value.toInt();

    m_startAngle = value.toInt();
    update();
}

void CircleMoveWidget::finishedFromAnimation()
{
    qDebug() << "finishedFromAnimation";
    update();

    if (m_startAngle == 330)
        m_startAngle = -30;
    else if (m_startAngle == -390)
        m_startAngle = -30;
}
