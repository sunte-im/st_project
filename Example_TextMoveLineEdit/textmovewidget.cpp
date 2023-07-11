#include "textmovewidget.h"
#include "ui_textmovewidget.h"
#include <QDebug>
#include <QTimer>
#include <QScrollBar>

TextMoveWidget::TextMoveWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::TextMoveWidget)
{
    ui->setupUi(this);
    m_move = false;
    m_moveRight = true;
    m_moveInterval = 500;
    m_rangeChangedTimer = new QTimer(this);
    connect(m_rangeChangedTimer, SIGNAL(timeout()), this, SLOT(timeout_fromRangeChangedTimer()));

    m_moveTimer = new QTimer(this);
    connect(m_moveTimer, SIGNAL(timeout()), this, SLOT(timeout_fromMoveTimer()));

    connect(ui->scrollArea->horizontalScrollBar(), SIGNAL(rangeChanged(int,int)),
            this, SLOT(rangeChanged_fromScrollBar(int,int)));

    m_preStepValue = -1;
}

TextMoveWidget::~TextMoveWidget()
{
    if (m_rangeChangedTimer)
    {
        if (m_rangeChangedTimer->isActive())
            m_rangeChangedTimer->stop();

        m_rangeChangedTimer->deleteLater();
    }

    if (m_moveTimer)
    {
        if (m_moveTimer->isActive())
            m_moveTimer->stop();

        m_moveTimer->deleteLater();
    }

    delete ui;
}

void TextMoveWidget::setText(QString text)
{
    ui->label->setText(text);
}

void TextMoveWidget::setMoveInterval(int msec)
{
    m_moveInterval = msec;
}

void TextMoveWidget::rangeChanged_fromScrollBar(int min, int max)
{
    qDebug() << __FUNCTION__ << min << max;

    m_rangeChangedTimer->start(1000);
}

void TextMoveWidget::timeout_fromRangeChangedTimer()
{
    int max = ui->scrollArea->horizontalScrollBar()->maximum();
    qDebug() << __FUNCTION__ << max;

    if (max > 0)
        m_move = true;
    else
        m_move = false;

    m_rangeChangedTimer->stop();

    if (m_move)
    {
        m_moveTimer->start(m_moveInterval);
        m_preStepValue = -1;
    }
    else
        m_moveTimer->stop();
}

void TextMoveWidget::timeout_fromMoveTimer()
{
    m_moveTimer->stop();
    int interval = m_moveInterval;
    int max = ui->scrollArea->horizontalScrollBar()->maximum();
    int currentValue = ui->scrollArea->horizontalScrollBar()->value();
    int singleStep = ui->scrollArea->horizontalScrollBar()->singleStep();

    if (m_moveRight)
    {
        m_preStepValue = currentValue + singleStep;
    }
    else
    {
        m_preStepValue = currentValue - singleStep;
    }

    ui->scrollArea->horizontalScrollBar()->setValue(m_preStepValue);

    if (m_preStepValue >= max)
    {
        m_moveRight = false;
        interval = 1000;
    }

    if (m_preStepValue <= 0)
    {
        m_moveRight = true;
        interval = 1000;
    }

    m_moveTimer->start(interval);

    //qDebug() << __FUNCTION__
    //         << " max: " << max
    //         << " currentValue: " << currentValue
    //         << " m_preStepValue: " << m_preStepValue;
}
