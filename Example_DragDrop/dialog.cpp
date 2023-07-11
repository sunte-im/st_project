#include "dialog.h"
#include "ui_dialog.h"
#include "dragwidget.h"
#include "dropwidget.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_dragWidget = new DragWidget(this);
    m_dropWidget = new DropWidget(this);

    ui->horizontalLayout->addWidget(m_dragWidget);
    ui->horizontalLayout->addWidget(m_dropWidget);
}

Dialog::~Dialog()
{
    delete ui;
}

