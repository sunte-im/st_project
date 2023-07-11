#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class ScrollbarWidget;
class Dialog : public QDialog
{
    Q_OBJECT

private:
    Ui::Dialog *ui;
    ScrollbarWidget* m_scrollbarWidget;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void valueChangedVerticalScrollBar(int value);          // QScrollArea scrollbar value change slots
    void rangeChangedVerticalScrollBar(int min, int max);   // QScrollArea scrollbar min,max chage slots
    void valueChangedFromScrollbarWidget(int value);        // Custom ScrollbarWidget value change slots
};
#endif // DIALOG_H
