#include "dragwidget.h"
#include "ui_dragwidget.h"
#include <QDrag>
#include <QMimeData>
#include <QDebug>

DragWidget::DragWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DragWidget)
{
    ui->setupUi(this);

    ui->label->setStyleSheet("background-color:rgb(0,255,0);");
}

DragWidget::~DragWidget()
{
    delete ui;
}

void DragWidget::mousePressEvent(QMouseEvent*)
{
    qDebug() << "DragWidget::mousePressEvent";
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(ui->label->styleSheet());
    drag->setMimeData(mimeData);

    drag->exec(Qt::CopyAction);

    QString color_r = QString::number(qrand() % ((255 + 1) - 0) + 0);
    QString color_g = QString::number(qrand() % ((255 + 1) - 0) + 0);
    QString color_b = QString::number(qrand() % ((255 + 1) - 0) + 0);
    ui->label->setStyleSheet("background-color:rba(" + color_r + "," + color_g + "," + color_b + ");");
}
