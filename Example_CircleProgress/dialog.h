#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPen>
#include <QPainter>

class CPBar : public QWidget {
    Q_OBJECT

    qreal p; // progress 0.0 to 1.0

public:
    CPBar(QWidget * p = 0) : QWidget(p), p(0)
    {
        setMinimumSize(208, 208);
    }

    void upd(qreal pp)
    {
        if (p == pp) return;
        p = pp;
        update();
    }

    void paintEvent(QPaintEvent *)
    {
        qreal pd = p * 360;
        qreal rd = 360 - pd;
        QPainter paint(this);
        paint.fillRect(rect(), Qt::white);
        paint.translate(4, 4);
        paint.setRenderHint(QPainter::Antialiasing);
        QPainterPath path, path2;
        path.moveTo(100, 0);
        path.arcTo(QRectF(0, 0, 200, 200), 90, -pd);
        QPen pen, pen2;
        pen.setCapStyle(Qt::FlatCap);
        pen.setColor(QColor("#00FF00"));
        pen.setWidth(8);
        paint.strokePath(path, pen);
        path2.moveTo(100, 0);
        pen2.setWidth(8);
        pen2.setColor(QColor("#d7d7d7"));
        pen2.setCapStyle(Qt::FlatCap);
        pen2.setDashPattern(QVector<qreal>{0.5, 1.105});
        path2.arcTo(QRectF(0, 0, 200, 200), 90, rd);
        pen2.setDashOffset(2.2);
        paint.strokePath(path2, pen2);
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
