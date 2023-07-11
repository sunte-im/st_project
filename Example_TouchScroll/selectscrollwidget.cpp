#include "selectscrollwidget.h"
#include "ui_selectscrollwidget.h"
#include <QLabel>
#include <QDebug>

SelectScrollWidget::SelectScrollWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectScrollWidget)
{
    ui->setupUi(this);

    ui->scrollArea->setType(TouchScrollAreaWidget::TYPE_CENTER_SELECT);
    ui->scrollArea->setFixedHeight(250);
    connect(ui->scrollArea, SIGNAL(selectCenterSignals(int)), this,
            SLOT(selectCenterSignalsFromTouchScrollAreaWidget(int)));
}

SelectScrollWidget::~SelectScrollWidget()
{
    delete ui;
}

void SelectScrollWidget::addList(QStringList list)
{
    for (int i = 0; i < 2; ++i)
    {
        QLabel* label = new QLabel;
        label->setText("");
        label->setFixedHeight(50);
        ui->verticalLayout->addWidget(label);
    }

    for (int i = 0; i < list.size(); ++i)
    {
        QLabel* label = new QLabel;
        label->setAlignment(Qt::AlignCenter);
        label->setProperty("num", i);
        if (i == 0)
            label->setStyleSheet("QLabel{color:#00cc79; font-family: Roboto; font-size: 26px; font-weight: bold;}");
        else
            label->setStyleSheet("QLabel{color:#555555; font-family: Roboto; font-size: 26px; font-weight: normal;}");
        label->setText(list.at(i));
        label->setFixedHeight(50);
        ui->verticalLayout->addWidget(label);
        m_labelList.append(label);
    }

    for (int i = 0; i < 2; ++i)
    {
        QLabel* label = new QLabel;
        label->setText("");
        label->setFixedHeight(50);
        ui->verticalLayout->addWidget(label);
    }
}

void SelectScrollWidget::select(int num)
{
    //qDebug() << __FUNCTION__ << num;
    ui->scrollArea->setValue(num*50);
}

void SelectScrollWidget::selectCenterSignalsFromTouchScrollAreaWidget(int value)
{
    qDebug() << __FUNCTION__ << value;

    int num = 0;
    if (value > 0)
    {
        num = value / 50;
    }

    foreach (QLabel* label, m_labelList)
    {
        if (label->property("num").toInt() == num)
            label->setStyleSheet("QLabel{color:#00cc79; font-family: Roboto; font-size: 26px; font-weight: bold;}");
        else
            label->setStyleSheet("QLabel{color:#555555; font-family: Roboto; font-size: 26px; font-weight: normal;}");
    }

    emit selectNumSignals(num);
}
