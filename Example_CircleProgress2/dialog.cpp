#include "dialog.h"
#include "ui_dialog.h"
#include <QSlider>
#include <QVBoxLayout>
#include "circlebar.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);


    //CPBar * p = new CPBar;
    //QSlider * s = new QSlider(Qt::Horizontal, this);
    //s->setMinimum(0);
    //s->setMaximum(100);
    //connect(s, &QSlider::valueChanged, [=](){ p->upd((qreal)s->value() / s->maximum());});


    CircleBar* bar = new CircleBar;
    bar->addItem(25, "#ff0000");
    bar->addItem(25, "#80FFC0");
    //bar->addItem(25, "#30C0FF");
    //connect(s, &QSlider::valueChanged, [=](){ bar->update_((qreal)s->value() / s->maximum());});



    QVBoxLayout * l = new QVBoxLayout(this);
    l->addWidget(bar);
    //l->addWidget(p);
    //l->addWidget(s);
    setLayout(l);
}

Dialog::~Dialog()
{
    delete ui;
}

