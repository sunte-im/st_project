#include "dialog.h"
#include "ui_dialog.h"
#include "QProgressIndicator.h"
#include <QVBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_pi = new QProgressIndicator(this);
    QHBoxLayout* hbl = new QHBoxLayout();
    hbl->addWidget(m_pi);
    ui->widget->setLayout(hbl);

    m_pi->startAnimation();
    m_pi->setFixedSize(200,200);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    m_pi->startAnimation();
}

void Dialog::on_pushButton_2_clicked()
{
    m_pi->stopAnimation();
}

void Dialog::on_horizontalSlider_valueChanged(int value)
{
    m_pi->setAnimationDelay(value);
}
