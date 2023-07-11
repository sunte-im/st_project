#ifndef DROPWIDGET_H
#define DROPWIDGET_H

#include <QWidget>

namespace Ui {
class DropWidget;
}

class DropWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::DropWidget *ui;

public:
    explicit DropWidget(QWidget *parent = nullptr);
    ~DropWidget();

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
};

#endif // DROPWIDGET_H
