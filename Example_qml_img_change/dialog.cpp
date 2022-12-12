#include "dialog.h"
#include "ui_dialog.h"
#include <QQuickView>
#include <QQuickItem>
#include <QTimer>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_num = 0;
    m_view = new QQuickView();
    QString qml_filepath = "qrc:/test1.qml";
    m_view->setSource(qml_filepath);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    m_view->show();
}

void Dialog::on_pushButton_2_clicked()
{
    m_timer->start(30);
}

void Dialog::on_pushButton_3_clicked()
{
    m_timer->stop();
}

void Dialog::slot_timeout()
{
    QQuickItem *item = m_view->rootObject();
    //QObject *object = qobject_cast<QObject*>(m_view->rootObject());
    QObject *obj = item->findChild<QObject*>("obj_img_123");
    if (!obj)
        return;

    if (m_num > 29)
        m_num = 0;

    obj->setProperty("source", "qrc:/loading_img/loading_" + QString::number(m_num).rightJustified(5,'0') + ".png");

    m_num++;
}
