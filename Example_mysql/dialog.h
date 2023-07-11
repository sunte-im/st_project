#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

private:
    Ui::Dialog *ui;
    QSqlDatabase m_sqlDB;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void setText(QString text);

private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_login_clicked();
    void on_pushButton_add_clicked();
};
#endif // DIALOG_H
