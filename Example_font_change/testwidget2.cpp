#include "testwidget2.h"
#include "ui_testwidget2.h"

TestWidget2::TestWidget2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget2)
{
    ui->setupUi(this);
}

TestWidget2::~TestWidget2()
{
    delete ui;
}
