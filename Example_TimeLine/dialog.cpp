#include "dialog.h"
#include "ui_dialog.h"
#include "timelinewidget.h"
#include <QDebug>
#include <QTime>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_timeLineWidget = new TimeLineWidget(this);
    m_timeLineWidget->show();

    connect(m_timeLineWidget, SIGNAL(begin_end_signals(int,int)), this, SLOT(slot_begin_end_signals(int,int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slot_begin_end_signals(int beginSec, int endSec)
{
    qDebug() << __FUNCTION__ << beginSec << endSec;

    QTime beginTime(0,0,0,0);
    beginTime = beginTime.addSecs(beginSec);

    QTime endTime(0,0,0,0);
    endTime = endTime.addSecs(endSec);

    ui->timeEdit_begin->setTime(beginTime);
    ui->timeEdit_end->setTime(endTime);

}
