#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGroupBox>
#include <QSizeGrip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->hide();                        // status hide
    setWindowFlags(Qt::FramelessWindowHint);      // mainwindow frameless

    QGroupBox* box = new QGroupBox(this);
    box->setStyleSheet("QGroupBox{background-color:yellow;}");
    ui->gridLayout->setContentsMargins(0,0,0,0);
    ui->gridLayout->addWidget(box);

    m_sizeGrip = new QSizeGrip(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    m_sizeGrip->move(width()-m_sizeGrip->width(), height()-m_sizeGrip->height());
}
