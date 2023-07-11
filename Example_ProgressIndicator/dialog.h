#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class QProgressIndicator;
class Dialog : public QDialog
{
    Q_OBJECT
private:
    Ui::Dialog *ui;
    QProgressIndicator* m_pi;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_horizontalSlider_valueChanged(int value);
};
#endif // DIALOG_H
