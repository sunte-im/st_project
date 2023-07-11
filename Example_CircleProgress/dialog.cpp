#include "dialog.h"
#include "ui_dialog.h"
#include <QSlider>
#include <QVBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QVBoxLayout * l = new QVBoxLayout(this);
    CPBar * p = new CPBar;
    QSlider * s = new QSlider(Qt::Horizontal, this);
    s->setMinimum(0);
    s->setMaximum(100);
    l->addWidget(p);
    l->addWidget(s);
    setLayout(l);
    connect(s, &QSlider::valueChanged, [=](){ p->upd((qreal)s->value() / s->maximum());});
}

Dialog::~Dialog()
{
    delete ui;
}

