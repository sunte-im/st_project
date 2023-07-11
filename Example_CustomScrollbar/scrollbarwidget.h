#ifndef SCROLLBARWIDGET_H
#define SCROLLBARWIDGET_H

#include <QWidget>

namespace Ui {
class ScrollbarWidget;
}
class Timer;
class ScrollbarWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::ScrollbarWidget *ui;
    QTimer* m_timer;

public:
    explicit ScrollbarWidget(QWidget *parent = nullptr);
    ~ScrollbarWidget();

    void setPageStep(int value);    // scrollbar page step
    void setValue(int value);       // scrollbar value
    void setRage(int min, int max); // scrollbar range
    void show(int msec=3000);       // 3 sec Hide

private slots:
    void on_verticalScrollBar_valueChanged(int value);
    void timeout();

signals:
    void valueChanged(int value);
};

#endif // SCROLLBARWIDGET_H
