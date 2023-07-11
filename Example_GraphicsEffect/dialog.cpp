#include "dialog.h"
#include "ui_dialog.h"
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <QMessageBox>

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
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setOffset(5,5);
    ui->label->setGraphicsEffect(shadow);

    QGraphicsDropShadowEffect *shadow1 = new QGraphicsDropShadowEffect();
    shadow1->setOffset(5,5);
    ui->label_5->setGraphicsEffect(shadow1);

    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(5);
    ui->label_2->setGraphicsEffect(blur);

    QGraphicsBlurEffect *blur1 = new QGraphicsBlurEffect();
    blur1->setBlurRadius(5);
    ui->label_6->setGraphicsEffect(blur1);

    QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
    colorize->setColor(QColor(255, 125, 0));
    ui->label_3->setGraphicsEffect(colorize);

    QGraphicsColorizeEffect *colorize1 = new QGraphicsColorizeEffect();
    colorize1->setColor(QColor(255, 125, 0));
    ui->label_7->setGraphicsEffect(colorize1);

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect();
    opacity->setOpacity(0.6);
    ui->label_4->setGraphicsEffect(opacity);

    QGraphicsOpacityEffect *opacity1 = new QGraphicsOpacityEffect();
    opacity1->setOpacity(0.6);
    ui->label_8->setGraphicsEffect(opacity1);
}

void Dialog::on_pushButton_2_clicked()
{
    ui->label->setGraphicsEffect(nullptr);
    ui->label_2->setGraphicsEffect(nullptr);
    ui->label_3->setGraphicsEffect(nullptr);
    ui->label_4->setGraphicsEffect(nullptr);

    ui->label_5->setGraphicsEffect(nullptr);
    ui->label_6->setGraphicsEffect(nullptr);
    ui->label_7->setGraphicsEffect(nullptr);
    ui->label_8->setGraphicsEffect(nullptr);
}

void Dialog::on_pushButton_3_clicked()
{
    QGraphicsBlurEffect* m_blur = new QGraphicsBlurEffect(this);
    m_blur->setBlurRadius(5);
    setGraphicsEffect(m_blur);

    QMessageBox msgBox(this);
    msgBox.setText("Test MessageBox.");
    msgBox.exec();

    //QDialog dlg(this);
    //dlg.exec();

    setGraphicsEffect(nullptr);
}
