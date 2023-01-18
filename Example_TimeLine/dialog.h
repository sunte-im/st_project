#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class TimeLineWidget;
class TimeLineWidget2;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    TimeLineWidget* m_timeLineWidget;
    TimeLineWidget2* m_timeLineWidget2;

private slots:
    void slot_begin_end_signals(int beginSec, int endSec);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};
#endif // DIALOG_H
