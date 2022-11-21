#include "dialog.h"
#include "ui_dialog.h"
#include "customcalendarwidget.h"
#include <QTextCharFormat>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_calendar = new CustomCalendarWidget(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_2_clicked()
{
    // clear
    m_calendar->clear();

    ui->listWidget->clear();
}

void Dialog::on_pushButton_3_clicked()
{
    QMap<QDate, QTextCharFormat> map = m_calendar->dateTextFormat();
    qDebug() << __FUNCTION__ << map;

    foreach (QDate date, map.keys())
    {
        QString _date = date.toString("yyyy-MM-dd");
        ui->listWidget->addItem(_date);
    }
}
