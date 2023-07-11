#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->widget->setText("-Left----Widget----Right-");
    ui->label->setText("=Left----Label----Right=");
    ui->pushButton_2->setText("=Left----PushButton----Right=");
}

Dialog::~Dialog()
{
    delete ui;
}
