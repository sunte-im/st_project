#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    qDebug() << "test log - 1 ";
}

void Dialog::on_pushButton_2_clicked()
{
    qWarning() << "test log - 2 ";
}

void Dialog::on_pushButton_3_clicked()
{
    qCritical() << "test log - 3 ";
}
