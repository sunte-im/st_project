#ifndef KEYPADWIDGET_H
#define KEYPADWIDGET_H

#include <QGroupBox>

namespace Ui {
class KeyPadWidget;
}
class QAbstractButton;
class KeyPadWidget : public QGroupBox
{
    Q_OBJECT
public:
    enum TYPE
    {
        TYPE_abc,
        TYPE_123,
        TYPE_number
    };

private:
    Ui::KeyPadWidget *ui;

public:
    explicit KeyPadWidget(QWidget *parent = nullptr);
    ~KeyPadWidget();

    void setType(TYPE type);
    void setText(QString text);
    void backSpace();
    void clearText();
    void enter();

signals:
    void enterSignals(QString text);

private slots:
    void slotButtonClicked(QAbstractButton*);
    void on_pushButton_backSpace_clicked();
    void on_pushButton_backSpace_2_clicked();
    void on_pushButton_backSpace_3_clicked();
    void on_pushButton_clearAll_clicked();
    void on_pushButton_66_clicked();
    void on_pushButton_enter_clicked();
    void on_pushButton_close_clicked();
    void on_pushButton_space_clicked();
    void on_pushButton_space_2_clicked();
};

#endif // KEYPADWIDGET_H
