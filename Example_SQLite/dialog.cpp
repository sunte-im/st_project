#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_dbFilePath = qApp->applicationDirPath() + "/test.db";
    qDebug() << "DB path : " << m_dbFilePath;

}

Dialog::~Dialog()
{
    close();

    delete ui;
}

void Dialog::close()
{
    if (!m_db.isOpen())
    {
        return;
    }

    m_db.close();
}

void Dialog::create()
{
    QSqlQuery query(m_db);
    QString queryStr;
    queryStr =
            "CREATE TABLE User ("
            "Id	INTEGER NOT NULL UNIQUE,"
            "UserId	TEXT NOT NULL UNIQUE,"
            "Password	TEXT NOT NULL,"
            "Name	TEXT NOT NULL,"
            "Phone	TEXT NOT NULL,"
            "Email	TEXT,"
            "Admin	INTEGER NOT NULL,"
            "CreationDate	INTEGER NOT NULL,"
            "UpdateDate	INTEGER NOT NULL,"
            "PRIMARY KEY(Id AUTOINCREMENT)"
            ");";


    if (!query.exec(queryStr))
    {
        qDebug() << "Dialog::create failed to queryStr : " << queryStr;
    }
}


void Dialog::on_pushButton_make_clicked()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");    // kind database
    m_db.setDatabaseName(m_dbFilePath);             // database file name, path
    if(m_db.open())                                 // File open or make
    {
        qDebug() << "Dialog::on_pushButton_make_clicked make DB file : " << m_dbFilePath;
    }
    else
    {
        qDebug() << "Dialog::on_pushButton_make_clicked make DB file - Fail";
    }

    create();
}

void Dialog::on_pushButton_insert_clicked()
{
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO User (UserId, Password, Name, Phone, Email, Admin, CreationDate, UpdateDate)"
                  "VALUES (:UserId, :Password, :Name, :Phone, :Email, :Admin, :CreationDate, :UpdateDate)");

    query.bindValue(":UserId", "UserId_1");
    query.bindValue(":Password", "Password_1");
    query.bindValue(":Name", "Name_1");
    query.bindValue(":Phone", "Phone_1");
    query.bindValue(":Email", "Email_1");
    query.bindValue(":Admin", 1);
    query.bindValue(":CreationDate", 321);
    query.bindValue(":UpdateDate", 123);

    query.exec();
}

void Dialog::on_pushButton_update_clicked()
{
    QSqlQuery query(m_db);

    query.prepare("UPDATE User SET Password=:Password, Name=:Name, Phone=:Phone, Email=:Email, Admin=:Admin, CreationDate=:CreationDate, UpdateDate=:UpdateDate "
                  "WHERE UserId=:UserId");

    query.bindValue(":Password", "Password_2");
    query.bindValue(":Name", "Name_2");
    query.bindValue(":Phone", "Phone_2");
    query.bindValue(":Email", "Email_2");
    query.bindValue(":Admin", 0);
    query.bindValue(":CreationDate", 6666);
    query.bindValue(":UpdateDate", 8888);

    query.bindValue(":UserId", "UserId_1");

    if (!query.exec())
    {
        qDebug() << "Dialog::on_pushButton_update_clicked fail";
    }
}

void Dialog::on_pushButton_select_clicked()
{
    QString queryStr = "SELECT * FROM User";
    QSqlQuery query(queryStr, m_db);

    while (query.next())
    {
        qDebug() << "Dialog::on_pushButton_select_clicked select all ###  "
                 << " Id: " << query.value(0).toInt()
                 << " UserId: " << query.value(1).toString()
                 << " Password: " << query.value(2).toString()
                 << " Name: " << query.value(3).toString()
                 << " Phone: " << query.value(4).toString()
                 << " Email: " << query.value(5).toString()
                 << " Admin: " << query.value(6).toInt()
                 << " CreationDate: " << query.value(7).toInt()
                 << " UpdateDate: " << query.value(8).toInt();

        qDebug() << "Dialog::on_pushButton_select_clicked select all !!!  "
                 << " Id: " << query.value("Id").toInt()
                 << " UserId: " << query.value("UserId").toString()
                 << " Password: " << query.value("Password").toString()
                 << " Name: " << query.value("Name").toString()
                 << " Phone: " << query.value("Phone").toString()
                 << " Email: " << query.value("Email").toString()
                 << " Admin: " << query.value("Admin").toInt()
                 << " CreationDate: " << query.value("CreationDate").toInt()
                 << " UpdateDate: " << query.value("UpdateDate").toInt();
    }
}

void Dialog::on_pushButton_delete_clicked()
{
    QSqlQuery query(m_db);
    QString queryStr;
    queryStr = "DELETE FROM User";

    if (query.exec(queryStr))
    {
        qDebug() << "Dialog::on_pushButton_delete_clicked OK";
    }
    else
    {
        qDebug() << "Dialog::on_pushButton_delete_clicked failed to queryStr : " << queryStr;
    }
}
