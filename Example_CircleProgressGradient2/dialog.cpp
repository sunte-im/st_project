#include "dialog.h"
#include "ui_dialog.h"
#include "circleprogressgradientwidget2.h"
#include <QDebug>
#include <QTimer>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);    
    m_splashNum = 0;
    QTimer* timer = new QTimer(this);
    //timer->start(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
    m_widget = new CircleProgressGradientWidget2(this);
    ui->horizontalLayout->addWidget(m_widget);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_horizontalSlider_valueChanged(int value)
{    
    m_widget->setValue(value);
}

void Dialog::on_pushButton_clicked()
{
    m_widget->setProgressGradientColor("#00b2ff", "#1ac881", "#1ac881");
}

void Dialog::on_pushButton_2_clicked()
{
    m_widget->setProgressGradientColor("#ffd269", "#ff7e69", "#ff7f69");
}

void Dialog::slot_timeout()
{
    if (m_splashNum > 194)
        m_splashNum = 0;

    QString numStr = QString::number(m_splashNum).rightJustified(5, '0');
    //qDebug() << __FUNCTION__ << numStr;
    ui->groupBox->setStyleSheet("QGroupBox{background-position:center;background-image: url(:/images/printing_"+numStr+".png);}");

    m_splashNum++;
}

void Dialog::on_pushButton_3_clicked(bool checked)
{
    m_widget->_setVisible(checked);
}
