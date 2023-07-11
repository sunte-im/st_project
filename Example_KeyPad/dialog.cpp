#include "dialog.h"
#include "ui_dialog.h"
#include "keypadwidget.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_keyPadWidget = new KeyPadWidget();
    connect(m_keyPadWidget, SIGNAL(enterSignals(QString)), this, SLOT(slotEnterSignals(QString)));
    m_keyPadWidget->hide();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    m_keyPadWidget->setType(KeyPadWidget::TYPE_abc);
}

void Dialog::on_pushButton_2_clicked()
{
    m_keyPadWidget->setType(KeyPadWidget::TYPE_123);
}

void Dialog::on_pushButton_3_clicked()
{
    m_keyPadWidget->setType(KeyPadWidget::TYPE_number);
}

void Dialog::on_pushButton_4_clicked()
{
    m_keyPadWidget->show();
}

void Dialog::slotEnterSignals(QString text)
{
    ui->label->setText(text);
}
