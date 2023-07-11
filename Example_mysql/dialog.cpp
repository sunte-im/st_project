#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlError>
#include <QDebug>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    qDebug() << "driver: " << QSqlDatabase::drivers();

    m_sqlDB = QSqlDatabase::addDatabase("QMYSQL");
}

Dialog::~Dialog()
{
    if (m_sqlDB.isOpen())
        m_sqlDB.close();

    delete ui;
}

void Dialog::setText(QString text)
{
    ui->textEdit->append(text + "\n");
}


void Dialog::on_pushButton_connect_clicked()
{
    if (m_sqlDB.isOpen())
        m_sqlDB.close();

    //m_sqlDB.setHostName("database-1.chvcaiqgm8by.us-east-1.rds.amazonaws.com");
    //m_sqlDB.setPort(3306);
    //m_sqlDB.setDatabaseName("test_db");
    //m_sqlDB.setUserName("admin");
    //m_sqlDB.setPassword("admin_111");
    m_sqlDB.setHostName(ui->lineEdit_host->text());
    m_sqlDB.setPort(ui->lineEdit_port->text().toInt());
    m_sqlDB.setDatabaseName(ui->lineEdit_db_name->text());
    m_sqlDB.setUserName(ui->lineEdit_id->text());
    m_sqlDB.setPassword(ui->lineEdit_pw->text());
    bool ok = m_sqlDB.open();

    qDebug() << __FUNCTION__ << " database open : " << ok;

    if (!ok)
    {
        qDebug() << __FUNCTION__ << " error : " << m_sqlDB.lastError().text()
                 << "  number :" << m_sqlDB.lastError().number();


        setText("Connect - NOK");
    }
    else
    {
        setText("Connect - OK");

        QString queryStr = "SELECT * FROM dental.user";
        QSqlQuery query(queryStr, m_sqlDB);

        while (query.next())
        {
            QString id = query.value("user_id").toString();
            QString pw = query.value("password").toString();

            qDebug() << __FUNCTION__ << "user_id: " << id << "  pw: " << pw;
        }
    }


}

void Dialog::on_pushButton_login_clicked()
{
    QString id = ui->lineEdit_login_id->text();
    QString pw = ui->lineEdit_login_pw->text();

    if (id.isEmpty() || pw.isEmpty())
        return;

    if (!m_sqlDB.isOpen())
        return;

    QString queryStr = "SELECT * FROM dental.user WHERE user_id='" + id + "'";

    QSqlQuery query(queryStr, m_sqlDB);

    qDebug() << __FUNCTION__ << "size: " << query.size()
             << " queryStr: " << queryStr;

    if (query.size() < 1)
    {
        setText("Not exist user id\n");
        return;
    }

    QString user_id;
    QString password;
    while (query.next())
    {
        user_id = query.value("user_id").toString();
        password = query.value("password").toString();
    }

    qDebug() << __FUNCTION__ << " user_id: " << user_id << " password: " << password;

    if (pw == password)
        setText("login OK");
    else
        setText("login NOK");

}

void Dialog::on_pushButton_add_clicked()
{
    QString id = ui->lineEdit_add_id->text();
    QString pw = ui->lineEdit_add_pw->text();

    if (id.isEmpty() || pw.isEmpty())
        return;

    if (!m_sqlDB.isOpen())
        return;

    QSqlQuery query(m_sqlDB);
    query.prepare("INSERT INTO dental.user (user_id, password)"
                  "VALUES (:user_id, :password)");

    query.bindValue(":user_id", id);
    query.bindValue(":password", pw);

    if (!query.exec())
    {
        setText(" add NOK");
    }
    else
    {
        setText(" add OK");
    }
}
