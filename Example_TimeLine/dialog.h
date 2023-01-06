#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class TimeLineWidget;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    TimeLineWidget* m_timeLineWidget;

private slots:
    void slot_begin_end_signals(int beginSec, int endSec);
};
#endif // DIALOG_H
