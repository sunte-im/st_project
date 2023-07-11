#include "dialog.h"
#include "ui_dialog.h"
#include "circlemovewidget.h"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_circleWidget = new CircleMoveWidget(this);

    ui->verticalLayout->addWidget(m_circleWidget);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    m_circleWidget->moveLeft();
}

void Dialog::on_pushButton_2_clicked()
{
    m_circleWidget->moveRight();
}
