#include "dialog.h"
#include "ui_dialog.h"
#include <QProcess>
#include <QDebug>
#include <QFileDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QString path = ui->lineEdit->text();
    //QString path = "C:\Program Files\Internet Explorer\iexplore.exe";
    qDebug() << "path : " << path;

    if (!QFile::exists(path) || path.isEmpty())
        return;

    path = "\"" + path + "\"";      // remove gap windows path

    //QProcess::start(path);              // ones execute
    //QProcess::startDetached(path);        // multi execute

    QStringList arguments;
    arguments << "aaa";      // add argument
    QProcess::startDetached(path, arguments);
}

void Dialog::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    ui->lineEdit->setText(fileName);
}
