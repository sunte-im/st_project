#ifndef NIGHTCHARTSWIDGET_H
#define NIGHTCHARTSWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "customcharts.h"
class NightchartsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NightchartsWidget(QWidget *parent = 0);
    void addItem(QString name, QColor color, float value);
    void setType(CustomCharts::type type);
    void clear();
protected:
    virtual void paintEvent(QPaintEvent * e);
private:
    CustomCharts _chart;
    int _margin_left;
    int _margin_top;

};

#endif // NIGHTCHARTSWIDGET_H
