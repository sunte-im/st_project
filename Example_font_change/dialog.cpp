#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include "testwidget.h"
#include "testwidget2.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    TestWidget* w = new TestWidget(this);
    w->move(50,740);
    w->show();

    TestWidget2* w2 = new TestWidget2();
    w2->show();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_comboBox_activated(const QString &arg1)
{
    qDebug() << __FUNCTION__ << arg1;
    //font.setFamily(arg1);
    QFont font(arg1);
    //font.setStyleHint(QFont::Monospace);
    //QApplication::setFont(font);
    qApp->setFont(font);
}

void Dialog::on_pushButton_clicked()
{
    qDebug() << __FUNCTION__ << qApp->font().family();
}

void Dialog::on_pushButton_2_clicked()
{
    //qDebug() << __FUNCTION__ << QApplication::font() << qApp->font();
    foreach (QWidget *widget, QApplication::allWidgets())
    {
        widget->setFont(QApplication::font());
        //widget->update();


        QString str = widget->styleSheet();     // get StyleSheet
        if (str.isEmpty())
            continue;

        str.replace(" ", "");       // 빈칸 제거

        bool exist = str.contains("font-family", Qt::CaseInsensitive); // 대소문자 구분 없이 font-family 검색
        if (!exist)
            continue;

        qDebug() << __FUNCTION__ << str << widget->objectName();

        QStringList strList;
        strList = str.split(";");
        QStringList changeStrList;
        foreach (QString _str, strList)
        {
            if (_str.isEmpty())
                continue;

            bool exist = _str.contains("font-family", Qt::CaseInsensitive); // 대소문자 구분 없이 font-family 검색
            if (!exist)
            {
                changeStrList.append(_str);
                continue;
            }

            QString changeStr = QString("font-family:%1").arg(QApplication::font().family());       // font-family StyleSheet 변경

            changeStrList.append(changeStr);
        }

        QString changeStr = changeStrList.join(";");
        qDebug() << __FUNCTION__ << " changeStr : " << changeStr;       // set StyleSheet
        widget->setStyleSheet(changeStr);
    }
}
