#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <Qt3DCore/Qt3DCore>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE


class Dialog : public QDialog
{
    Q_OBJECT
private:
    Ui::Dialog *ui;
    Qt3DCore::QTransform *m_textTransform;
    QMatrix4x4 m_matrix;
    float m_angle;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void init();

private slots:
    void timeout();

};
#endif // DIALOG_H
