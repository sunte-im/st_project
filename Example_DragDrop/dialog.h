#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class DragWidget;
class DropWidget;
class Dialog : public QDialog
{
    Q_OBJECT
private:
    Ui::Dialog *ui;
    DragWidget* m_dragWidget;
    DropWidget* m_dropWidget;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();


};
#endif // DIALOG_H
