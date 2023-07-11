#include "dialog.h"
#include "ui_dialog.h"
#include "ModelWindow.h"
#include "modelwidget_test.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ModelWindow* w = new ModelWindow(this);
    ModelWidget_Test* ww = new ModelWidget_Test(this);
    ModelWidget_Test* www = new ModelWidget_Test(this);

    ui->verticalLayout->addWidget(w);
    ui->verticalLayout->addWidget(ww);
    ui->verticalLayout->addWidget(www);
}

Dialog::~Dialog()
{
    delete ui;
}

