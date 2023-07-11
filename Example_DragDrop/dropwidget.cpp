#include "dropwidget.h"
#include "ui_dropwidget.h"
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>

DropWidget::DropWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DropWidget)
{
    ui->setupUi(this);

    setAcceptDrops(true);
}

DropWidget::~DropWidget()
{
    delete ui;
}

void DropWidget::dragEnterEvent(QDragEnterEvent* e)
{
    if (e->mimeData()->hasFormat("text/plain") || e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}

void DropWidget::dropEvent(QDropEvent* e)
{
    qDebug() << "DropWidget::dropEvent";

    if (e->source() == this && e->possibleActions() & Qt::MoveAction)
           return;

    if (e->proposedAction() == Qt::CopyAction)
    {
        if (e->mimeData()->hasFormat("text/plain"))
        {
            QString textData = e->mimeData()->text();
            qDebug() << "DropWidget::dropEvent Data : " << textData;
            ui->label->setStyleSheet(textData);
        }
        else if (e->mimeData()->hasUrls())
        {
            qDebug() << "DropWidget::dropEvent..1 " << e->mimeData()->urls();
            foreach (const QUrl &url, e->mimeData()->urls())
            {
                QString fileName = url.toLocalFile();
                qDebug() << "DropWidget::dropEvent.. Dropped file:" << fileName;
            }
        }
        e->acceptProposedAction();
    }
    else
    {
        e->ignore();
    }
}
