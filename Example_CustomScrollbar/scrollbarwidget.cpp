#include "scrollbarwidget.h"
#include "ui_scrollbarwidget.h"
#include <QTimer>
#include <QDebug>

ScrollbarWidget::ScrollbarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScrollbarWidget)
{
    ui->setupUi(this);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

ScrollbarWidget::~ScrollbarWidget()
{
    delete ui;
}

void ScrollbarWidget::setPageStep(int value)
{
    ui->verticalScrollBar->setPageStep(value);
}

void ScrollbarWidget::setValue(int value)
{
    ui->verticalScrollBar->setValue(value);
}

void ScrollbarWidget::setRage(int min, int max)
{
    ui->verticalScrollBar->setRange(min, max);
}

void ScrollbarWidget::show(int msec)
{
    qDebug() << "ScrollbarWidget::show timer start";

    setVisible(true);
    m_timer->start(msec);
}

void ScrollbarWidget::on_verticalScrollBar_valueChanged(int value)
{
    qDebug() << "ScrollbarWidget::on_verticalScrollBar_valueChanged value: " << value;
    emit valueChanged(value);
}

void ScrollbarWidget::timeout()
{
    qDebug() << "ScrollbarWidget::timeout";

    m_timer->stop();

    hide();

    qDebug() << "ScrollbarWidget::timeout timer end";
}
