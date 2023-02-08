#include "dialog.h"
#include "ui_dialog.h"
#include "timelinewidget.h"
#include "timelinewidget2.h"
#include <QDebug>
#include <QTime>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_timeLineWidget = new TimeLineWidget(this);
    m_timeLineWidget3 = new TimeLineWidget(this);
    m_timeLineWidget2 = new TimeLineWidget2(this);

    connect(m_timeLineWidget, SIGNAL(begin_end_signals(int,int)), this, SLOT(slot_begin_end_signals(int,int)));
    connect(m_timeLineWidget3, SIGNAL(begin_end_signals(int,int)), this, SLOT(slot_begin_end_signals_3(int,int)));

    ui->verticalLayout->addWidget(m_timeLineWidget);
    ui->verticalLayout->addWidget(m_timeLineWidget3);
    ui->verticalLayout->addWidget(m_timeLineWidget2);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slot_begin_end_signals(int beginSec, int endSec)
{
    bool multiMode = ui->pushButton_3->isChecked();
    qDebug() << __FUNCTION__ << beginSec << endSec;

    QTime beginTime(0,0,0,0);
    beginTime = beginTime.addSecs(beginSec);

    QTime endTime(0,0,0,0);
    endTime = endTime.addSecs(endSec);

    if (multiMode)
    {
        ui->timeEdit_begin->setTime(beginTime);
    }
    else
    {
        ui->timeEdit_begin->setTime(beginTime);
        ui->timeEdit_end->setTime(endTime);
    }
}

void Dialog::slot_begin_end_signals_3(int beginSec, int endSec)
{
    bool multiMode = ui->pushButton_3->isChecked();

    if (!multiMode)
        return;

    qDebug() << __FUNCTION__ << beginSec << endSec;

//    QTime beginTime(0,0,0,0);
//    beginTime = beginTime.addSecs(beginSec);

    QTime endTime(0,0,0,0);
    endTime = endTime.addSecs(endSec);

    //ui->timeEdit_begin->setTime(beginTime);
    ui->timeEdit_end->setTime(endTime);
}

void Dialog::on_pushButton_clicked()
{
    int begin = ui->lineEdit_begin->text().toInt();
    int end = ui->lineEdit_end->text().toInt();

    m_timeLineWidget2->addTime(begin, end);

    m_timeLineWidget2->updateUi();
}

void Dialog::on_pushButton_2_clicked()
{
    m_timeLineWidget2->clear();
}

void Dialog::on_pushButton_3_clicked(bool checked)
{
    m_timeLineWidget->setFixedRight(checked);
    m_timeLineWidget3->setFixedLeft(checked);
}
