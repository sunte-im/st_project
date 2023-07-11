#include "dialog.h"
#include "ui_dialog.h"
#include "touchscrollareawidget.h"
//#include <QScrollBar>
#include <QLabel>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QStringList strList;
    for (int i = 0; i < 24; ++i)
        strList << QString::number(i);
    ui->widget->addList(strList);

    connect(ui->widget, SIGNAL(selectNumSignals(int)), this, SLOT(selectNumSignalsFromSelectScrollWidget(int)));

    for (int i = 0; i < 12; ++i)
    {
        QLabel* label = new QLabel;
        label->setText(QString::number(i+1));
        label->setFixedHeight(50);
        label->setStyleSheet("border:1px solid balck;");
        ui->verticalLayout_5->addWidget(label);
    }

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::selectNumSignalsFromSelectScrollWidget(int n)
{
    qDebug() << __FUNCTION__ << n;
}

void Dialog::selectCenterSignals_0(int value)
{
    int num = 0;
    if (value > 0)
    {
        num = value / 50;
    }

    foreach (QLabel* label, m_labelList)
    {
        if (label->text() == QString::number(num))
            label->setStyleSheet("border:1px solid red;");
        else
            label->setStyleSheet("border:1px solid black;");
    }
}



void Dialog::on_pushButton_clicked()
{
    QString num = ui->lineEdit->text();
    ui->widget->select(num.toInt());
}
