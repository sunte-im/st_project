#include "dialog.h"
#include "ui_dialog.h"
#include "httpsender.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_httpSender = new HttpSender(this);
}

Dialog::~Dialog()
{
    if (m_httpSender)
        m_httpSender->deleteLater();

    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    m_httpSender->send(ui->lineEdit->text());
}
