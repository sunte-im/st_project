#ifndef TOOTHWIDGET_H
#define TOOTHWIDGET_H

#include <QWidget>

namespace Ui {
class ToothWidget;
}

class QPushButton;
class QLabel;
class ToothWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::ToothWidget *ui;
    QList<QPushButton*> m_btnList;
    QList<QLabel*> m_toothLabelList;
    QList<QLabel*> m_numLabelList;

public:
    explicit ToothWidget(QWidget *parent = nullptr);
    ~ToothWidget();

    void init();

    void setClickedEnable(bool f);
    void setType(QString num, QString item);
    void select(QString num);

    void updateUi();
    //void updateUi_teethLabeling();

    void clear();

signals:
    void clicked(QString num);

private slots:
    void clickedButton();
};

#endif // TOOTHWIDGET_H
