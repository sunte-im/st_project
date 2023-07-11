#include "dialog.h"
#include "ui_dialog.h"
#include <QPropertyAnimation>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);    

    ui->groupBox_bottom->hide();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(btn->geometry().x(), btn->geometry().y(), 100, 30));
    animation->setEndValue(QRect(btn->geometry().x()+500, btn->geometry().y(), 100, 30));
    animation->start();
}

void Dialog::on_pushButton_2_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(btn->geometry().x(), btn->geometry().y(), 100, 30));
    animation->setEndValue(QRect(btn->geometry().x()+500, btn->geometry().y(), 100, 30));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start();
}

void Dialog::on_pushButton_3_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(btn->geometry().x(), btn->geometry().y(), 100, 30));
    animation->setEndValue(QRect(btn->geometry().x()+500, btn->geometry().y(), 100, 30));
    animation->setEasingCurve(QEasingCurve::InOutBounce);
    animation->start();
}

void Dialog::on_pushButton_4_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(btn->geometry().x(), btn->geometry().y(), 100, 30));
    animation->setEndValue(QRect(btn->geometry().x()+500, btn->geometry().y(), 100, 30));
    animation->setEasingCurve(QEasingCurve::InOutElastic);
    animation->start();
}

void Dialog::on_pushButton_5_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(btn->geometry().x(), btn->geometry().y(), 100, 30));
    animation->setEndValue(QRect(btn->geometry().x()+500, btn->geometry().y(), 100, 30));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void Dialog::on_pushButton_6_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(btn->geometry().x(), btn->geometry().y(), 100, 30));
    animation->setEndValue(QRect(btn->geometry().x()+500, btn->geometry().y(), 100, 30));
    animation->setEasingCurve(QEasingCurve::InOutCirc);
    animation->start();
}

void Dialog::on_pushButton_7_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    int x = btn->geometry().x();
    int y = btn->geometry().y();
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(2000);
    animation->setKeyValueAt(0, QRect(x, y, 100, 30));
    animation->setKeyValueAt(0.8, QRect(x+250, y+250, 100, 30));
    animation->setKeyValueAt(1, QRect(x, y, 100, 30));
    animation->start();
}


void Dialog::on_pushButton_8_clicked()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(geometry().x(), geometry().y(), 30, 30));
    animation->setEndValue(QRect(geometry().x(), geometry().y(), 800, 600));
    animation->setEasingCurve(QEasingCurve::InOutCirc);
    animation->start();
}

void Dialog::on_pushButton_9_clicked()
{
    // show
    ui->groupBox->setFixedHeight(300);
    QGroupBox* box = ui->groupBox_bottom;
    box->show();

    QPropertyAnimation* animation = new QPropertyAnimation(box, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(box->geometry().x(), box->geometry().y(), box->geometry().width(), 0));
    animation->setEndValue(QRect(box->geometry().x(), box->geometry().y(), box->geometry().width(), 130));
    animation->start();
}

void Dialog::on_pushButton_10_clicked()
{
    // hide
    ui->groupBox_bottom->hide();
    ui->groupBox->setFixedHeight(180);
}
