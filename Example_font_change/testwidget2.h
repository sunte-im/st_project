#ifndef TESTWIDGET2_H
#define TESTWIDGET2_H

#include <QWidget>

namespace Ui {
class TestWidget2;
}

class TestWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidget2(QWidget *parent = nullptr);
    ~TestWidget2();

private:
    Ui::TestWidget2 *ui;
};

#endif // TESTWIDGET2_H
