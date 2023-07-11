#include "keypadwidget.h"
#include "ui_keypadwidget.h"

KeyPadWidget::KeyPadWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::KeyPadWidget)
{
    ui->setupUi(this);

    connect(ui->buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(slotButtonClicked(QAbstractButton*)));
}

KeyPadWidget::~KeyPadWidget()
{
    delete ui;
}

void KeyPadWidget::setType(KeyPadWidget::TYPE type)
{
    ui->stackedWidget->setCurrentIndex(type);
}

void KeyPadWidget::setText(QString text)
{
    QString _text = ui->lineEdit->text();
    ui->lineEdit->setText(_text.append(text));
}

void KeyPadWidget::backSpace()
{
    QString _text = ui->lineEdit->text();
    if (_text.isEmpty())
        return;

    _text.chop(1);
    ui->lineEdit->setText(_text);
}

void KeyPadWidget::clearText()
{
    ui->lineEdit->clear();
}

void KeyPadWidget::enter()
{
    QString text = ui->lineEdit->text();
    emit enterSignals(text);
    close();
}

void KeyPadWidget::slotButtonClicked(QAbstractButton* btn)
{
    setText(btn->text());
}

void KeyPadWidget::on_pushButton_backSpace_clicked()
{
    backSpace();
}

void KeyPadWidget::on_pushButton_backSpace_2_clicked()
{
    backSpace();
}

void KeyPadWidget::on_pushButton_backSpace_3_clicked()
{
    backSpace();
}

void KeyPadWidget::on_pushButton_clearAll_clicked()
{
    clearText();
}

void KeyPadWidget::on_pushButton_66_clicked()
{
    setText("&");
}

void KeyPadWidget::on_pushButton_enter_clicked()
{
    enter();
}

void KeyPadWidget::on_pushButton_close_clicked()
{
    close();
}

void KeyPadWidget::on_pushButton_space_clicked()
{
    setText(" ");
}

void KeyPadWidget::on_pushButton_space_2_clicked()
{
    setText(" ");
}
