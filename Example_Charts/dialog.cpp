#include "dialog.h"
#include "ui_dialog.h"
#include "customcharts.h"

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

void Dialog::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e);
    QPainter painter;
    QFont font;
    painter.begin(this);
    CustomCharts PieChart;
    PieChart.setType(CustomCharts::Histogram);//{Histogram,Pie,Dpie};
    PieChart.setLegendType(CustomCharts::Vertical);//{Round,Vertical}
    PieChart.setCords(100,100,this->width()/1.5,this->height()/1.5);
    PieChart.addPiece("Item1",QColor(200,10,50),34);
    PieChart.addPiece("Item2",Qt::green,27);
    PieChart.addPiece("Item3",Qt::cyan,14);
    PieChart.addPiece("Item4",Qt::yellow,7);
    PieChart.addPiece("Item5",Qt::blue,4);
    PieChart.addPiece("Item6",Qt::magenta,14);
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}

