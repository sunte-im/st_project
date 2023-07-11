#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QConicalGradient>
#include <QTimer>

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

void Dialog:: paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

//    QConicalGradient conicalGrad(QPointF(650, 150), 90);
//    conicalGrad.setColorAt(0, Qt::white);
//    conicalGrad.setColorAt(0.5, Qt::green);
//    conicalGrad.setColorAt(1, Qt::black);
//    QRect rect_conical(550,50,200,200);
//    painter.fillRect(rect_conical, conicalGrad);

//    QPainterPath path;
//    path.moveTo(100, 1000);
//    path.arcTo(QRectF(0, 0, 100, 100), 90, 360);

//    QPen pen;
//    pen.setCapStyle(Qt::FlatCap);
//    pen.setColor(QColor("#00FF00"));
//    pen.setWidth(8);
//    painter.strokePath(path, pen);

//    QRadialGradient radialGradient(310,110,100,310,110);
//    radialGradient.setColorAt(0,   QColor(0,255,0,0));
//    radialGradient.setColorAt(0.2, QColor(0,255,0,10));
//    radialGradient.setColorAt(0.3, QColor(0,255,0,30));
//    radialGradient.setColorAt(0.4, QColor(0,255,0,50));
//    radialGradient.setColorAt(0.5, QColor(0,255,0,60));
//    radialGradient.setColorAt(0.6, QColor(0,255,0,70));
//    radialGradient.setColorAt(0.7, QColor(0,255,0,60));
//    radialGradient.setColorAt(0.8, QColor(0,255,0,50));
//    radialGradient.setColorAt(0.9, QColor(0,255,0,40));
//    radialGradient.setColorAt(1.0, QColor(0,255,0,30));
//    painter.setBrush(QBrush(radialGradient));
//    painter.drawEllipse(210,10,200,200);

    painter.setPen(Qt::NoPen);

    QConicalGradient conicalGradient(110,110,0);
    conicalGradient.setColorAt(0,   QColor(0,0,255,0));
    conicalGradient.setColorAt(0.2, QColor(0,0,255,0));
    conicalGradient.setColorAt(0.3, QColor(0,0,255,0));
    conicalGradient.setColorAt(0.4, QColor(0,0,255,70));
    conicalGradient.setColorAt(0.5, QColor(0,0,255,100));
    conicalGradient.setColorAt(0.6, QColor(0,0,255,70));
    conicalGradient.setColorAt(0.7, QColor(0,0,255,0));
    conicalGradient.setColorAt(0.8, QColor(0,0,255,0));
    conicalGradient.setColorAt(0.9, QColor(0,0,255,0));
    conicalGradient.setColorAt(1.0, QColor(0,0,255,0));
    painter.setBrush(QBrush(conicalGradient));
    painter.drawEllipse(10,10,200,200);

    QRadialGradient radialGradient1(110,110,100,110,110);
    radialGradient1.setColorAt(0,   QColor(255,255,255,255));
    radialGradient1.setColorAt(0.2, QColor(255,255,255,255));
    radialGradient1.setColorAt(0.3, QColor(255,255,255,255));
    radialGradient1.setColorAt(0.4, QColor(255,255,255,200));
    radialGradient1.setColorAt(0.5, QColor(255,255,255,150));
    radialGradient1.setColorAt(0.6, QColor(255,255,255,100));
    radialGradient1.setColorAt(0.7, QColor(255,255,255,70));
    radialGradient1.setColorAt(0.8, QColor(255,255,255,50));
    radialGradient1.setColorAt(0.9, QColor(255,255,255,0));
    radialGradient1.setColorAt(1.0, QColor(255,255,255,30));
    painter.setBrush(QBrush(radialGradient1));
    painter.drawEllipse(10,10,200,200);

    QRadialGradient radialGradient(110,110,100,110,110);
    radialGradient.setColorAt(0,   QColor(0,255,0,0));
    radialGradient.setColorAt(0.2, QColor(0,255,0,10));
    radialGradient.setColorAt(0.3, QColor(0,255,0,30));
    radialGradient.setColorAt(0.4, QColor(0,255,0,50));
    radialGradient.setColorAt(0.5, QColor(0,255,0,60));
    radialGradient.setColorAt(0.6, QColor(0,255,0,70));
    radialGradient.setColorAt(0.7, QColor(0,255,0,60));
    radialGradient.setColorAt(0.8, QColor(0,255,0,50));
    radialGradient.setColorAt(0.9, QColor(0,255,0,40));
    radialGradient.setColorAt(1.0, QColor(0,255,0,30));
    painter.setBrush(QBrush(radialGradient));
    painter.drawEllipse(10,10,200,200);

}
