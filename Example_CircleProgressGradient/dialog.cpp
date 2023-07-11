#include "dialog.h"
#include "ui_dialog.h"
#include "circleprogressgradientwidget.h"
#include <QDebug>
#include <QTimer>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);    
    m_splashNum = 0;
    QTimer* timer = new QTimer(this);
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
    m_widget = new CircleProgressGradientWidget(this);
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
    m_widget->setProgressGradientColor("#00e1d2", "#00a2fa", "#079df3");
}

void Dialog::on_pushButton_2_clicked()
{
    m_widget->setProgressGradientColor("#ffd269", "#ff7e69", "#ff7f69");
}

void Dialog::slot_timeout()
{
    if (m_splashNum > 39)
        m_splashNum = 0;

    qDebug() << __FUNCTION__ << m_splashNum;


    ui->groupBox->setStyleSheet("QGroupBox{border-image: url(:/3dprint_splash-"+QString::number(m_splashNum)+".png);}");

    m_splashNum++;
}
