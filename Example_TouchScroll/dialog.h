#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class QLabel;
class Dialog : public QDialog
{
    Q_OBJECT

private:
    Ui::Dialog *ui;
    QList<QLabel*> m_labelList;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void selectNumSignalsFromSelectScrollWidget(int n);
    void selectCenterSignals_0(int value);
    void on_pushButton_clicked();
};
#endif // DIALOG_H
