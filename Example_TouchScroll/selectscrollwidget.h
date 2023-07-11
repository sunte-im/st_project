#ifndef SELECTSCROLLWIDGET_H
#define SELECTSCROLLWIDGET_H

#include <QWidget>

namespace Ui {
class SelectScrollWidget;
}

class QLabel;
class SelectScrollWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::SelectScrollWidget *ui;
    QList<QLabel*> m_labelList;

public:
    explicit SelectScrollWidget(QWidget *parent = nullptr);
    ~SelectScrollWidget();

    void addList(QStringList list);
    void select(int num);

signals:
    void selectNumSignals(int num);

private slots:
    void selectCenterSignalsFromTouchScrollAreaWidget(int value);
};

#endif // SELECTSCROLLWIDGET_H
