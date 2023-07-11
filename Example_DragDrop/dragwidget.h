#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>

namespace Ui {
class DragWidget;
}

class DragWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::DragWidget *ui;

public:
    explicit DragWidget(QWidget *parent = nullptr);
    ~DragWidget();

protected:
    void mousePressEvent(QMouseEvent *e);

};

#endif // DRAGWIDGET_H
