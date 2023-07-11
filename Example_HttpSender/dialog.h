#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class HttpSender;
class Dialog : public QDialog
{
    Q_OBJECT
private:
    Ui::Dialog *ui;
    HttpSender* m_httpSender;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();


private slots:
    void on_pushButton_clicked();
};
#endif // DIALOG_H
