#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class CircleProgressGradientWidget;
class Dialog : public QDialog
{
    Q_OBJECT
private:
    Ui::Dialog *ui;
    CircleProgressGradientWidget* m_widget;
    int m_splashNum;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void slot_timeout();

};
#endif // DIALOG_H
