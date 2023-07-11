#include "dialog.h"
#include "ui_dialog.h"
#include "scrollbarwidget.h"
#include <QPushButton>
#include <QScrollBar>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    for (int i = 0; i < 15; ++i)
    {
        QPushButton* btn = new QPushButton(this);
        btn->setText(QString::number(i));
        ui->verticalLayout->addWidget(btn);
    }

    connect(ui->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(valueChangedVerticalScrollBar(int)));
    connect(ui->scrollArea->verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
            this, SLOT(rangeChangedVerticalScrollBar(int,int)));

    m_scrollbarWidget = new ScrollbarWidget(this);
    connect(m_scrollbarWidget, SIGNAL(valueChanged(int)),
            this, SLOT(valueChangedFromScrollbarWidget(int)));

    m_scrollbarWidget->move(250, 15);
    m_scrollbarWidget->setFixedHeight(280);
    m_scrollbarWidget->hide();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::valueChangedVerticalScrollBar(int value)
{
    qDebug() << "Dialog::valueChangedVerticalScrollBar value: " << value;
    m_scrollbarWidget->setPageStep(ui->scrollArea->verticalScrollBar()->pageStep());
    m_scrollbarWidget->setValue(value);
    m_scrollbarWidget->show(2000);
}

void Dialog::rangeChangedVerticalScrollBar(int min, int max)
{
    qDebug() << "Dialog::rangeChangedVerticalScrollBar min: " << min
             << " max: " << max;

    m_scrollbarWidget->setRage(min, max);
}

void Dialog::valueChangedFromScrollbarWidget(int value)
{
    qDebug() << "Dialog::valueChangedFromScrollbarWidget value: " << value ;

    ui->scrollArea->verticalScrollBar()->setValue(value);
}

