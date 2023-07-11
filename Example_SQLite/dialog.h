#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

private:
    Ui::Dialog *ui;

    QSqlDatabase m_db;
    QString m_dbFilePath;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void close();
    void create();

private slots:
    void on_pushButton_make_clicked();
    void on_pushButton_insert_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_select_clicked();


};
#endif // DIALOG_H
