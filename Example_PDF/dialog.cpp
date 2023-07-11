#include "dialog.h"
#include "ui_dialog.h"
#include "toothwidget.h"
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextBlock>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_toothWidget = new ToothWidget(this);
    m_toothWidget->move(10,10);
    connect(m_toothWidget, SIGNAL(clicked(QString)), SLOT(slot_clicked(QString)));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    m_toothWidget->updateUi();
    qDebug() << __FUNCTION__;
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPagedPaintDevice::A4);
    printer.setOutputFileName("test12345.pdf");
    printer.setOrientation(QPrinter::Portrait);
    printer.setPageMargins(10, 10, 10, 10, QPrinter::Millimeter);
    //printer.setResolution(300);

    QPainter painter;
    //painter.setRenderHint(QPainter::Antialiasing);
    painter.begin(&printer);

    //QPixmap pixmap("./img_tooth.png");
    QPixmap pixmap = m_toothWidget->grab(QRect(QPoint(0, 0), QSize(-1, -1)));
    painter.drawPixmap(QPoint(printer.width()/2-m_toothWidget->width()/2, 200), pixmap);

    QString html;
    html += "<h1>Order form</h1>";
    html += QString("<table width='%1' border='1' align='center' frame='void' cellspacing='0' cellpadding='1px' rules='all'>").arg(printer.width());

    for (int i = 0; i < 9; i++) {
        html += "<tr>";
        for (int j = 0; j < 2; j++) {
            html += QString("<td border-collapse='collapse'>text%1\n\n\n</td>").arg(j+1);
        }
        html += "</tr>";
    }
    html += "</table>";

    QTextDocument textDoc;
    textDoc.setHtml(html);
    textDoc.drawContents(&painter);
    textDoc.end();
    painter.end();
}

void Dialog::on_pushButton_4_clicked()
{
    if (m_num.isEmpty())
        return;

    m_toothWidget->setType(m_num, "Crown");

    m_toothWidget->updateUi();
}

void Dialog::on_pushButton_3_clicked()
{
    if (m_num.isEmpty())
        return;

    m_toothWidget->setType(m_num, "Veneer");

    m_toothWidget->updateUi();
}

void Dialog::on_pushButton_2_clicked()
{
    if (m_num.isEmpty())
        return;

    m_toothWidget->setType(m_num, "Inlay");

    m_toothWidget->updateUi();
}

void Dialog::on_pushButton_5_clicked()
{
    if (m_num.isEmpty())
        return;

    m_toothWidget->setType(m_num, "Onlay");

    m_toothWidget->updateUi();
}

void Dialog::slot_clicked(QString num)
{
    m_num = num;
}
