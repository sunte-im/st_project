/*
  Copyright (c) 2011 - Tőkés Attila

  This file is part of SmtpClient for Qt.

  SmtpClient for Qt is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  SmtpClient for Qt is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY.

  See the LICENSE file for more details.
*/

#include "sendemail.h"
#include "ui_sendemail.h"

#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>

#include <iostream>

#include "define.h"

using namespace std;

SendEmail::SendEmail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendEmail)
{
    ui->setupUi(this);

    ui->host->setText(SMTP_SERVER);
    ui->port->setValue(/*587*/465);
    ui->ssl->setChecked(true);
    ui->auth->setChecked(true);
    ui->username->setText(SENDER_EMAIL);
    ui->password->setText(SENDER_PASSWORD);

    ui->sender->setText(QString(SENDER_NAME) + "<" + SENDER_EMAIL + ">");
    ui->recipients->setText(QString(RECIPIENT_NAME) + "<" + RECIPIENT_EMAIL + ">");    
}

SendEmail::~SendEmail()
{
    delete ui;
}

EmailAddress SendEmail::stringToEmail(const QString &str)
{
    int p1 = str.indexOf("<");
    int p2 = str.indexOf(">");

    if (p1 == -1)
    {
        // no name, only email address
        return EmailAddress(str);
    }
    else
    {
        return EmailAddress(str.mid(p1 + 1, p2 - p1 - 1), str.left(p1));
    }

}

void SendEmail::on_addAttachment_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        ui->attachments->addItems(dialog.selectedFiles());
}

void SendEmail::on_sendEmail_clicked()
{
    QString host = ui->host->text();
    int port = ui->port->value();
    bool ssl = ui->ssl->isChecked();
    bool auth = ui->auth->isChecked();
    QString user = ui->username->text();
    QString password = ui->password->text();

    EmailAddress sender = stringToEmail(ui->sender->text());

    QStringList rcptStringList = ui->recipients->text().split(';');

    QString subject = ui->subject->text();
    QString html = ui->texteditor->toHtml();

    SmtpClient smtp (host, port, ssl ? SmtpClient::SslConnection : SmtpClient::TcpConnection);
    connect(&smtp, SIGNAL(error(SmtpClient::SmtpError)), this, SLOT(slotError(SmtpClient::SmtpError)));
    connect(&smtp, SIGNAL(stateChanged(SmtpClient::ClientState)), this, SLOT(slotStateChanged(SmtpClient::ClientState)));
    connect(&smtp, SIGNAL(mailSent()), this, SLOT(slotMailSent()));

    MimeMessage message;

    message.setSender(sender);
    message.setSubject(subject);

    for (int i = 0; i < rcptStringList.size(); ++i)
         message.addRecipient(stringToEmail(rcptStringList.at(i)));

    MimeHtml content;
    content.setHtml(html);

    message.addPart(&content);

    QList<QFile*> files;
    QList<MimeAttachment*> attachments;
    for (int i = 0; i < ui->attachments->count(); ++i)
    {
        QFile* file = new QFile(ui->attachments->item(i)->text());
        files.append(file);

        MimeAttachment* attachment = new MimeAttachment(file);
        attachments.append(attachment);

        message.addPart(attachment);
    }

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected())
    {
        errorMessage("Connection Failed");
        return;
    }

    if (auth)
    {
        smtp.login(user, password);
        qDebug() << "user:" << user << "pw:" << password;
        if (!smtp.waitForAuthenticated())
        {
            errorMessage("Authentification Failed");
            return;
        }
    }

    smtp.sendMail(message);
    if (!smtp.waitForMailSent())
    {
        errorMessage("Mail sending failed");
        return;
    }
    else
    {
        QMessageBox okMessage (this);
        okMessage.setText("The email was succesfully sent.");
        okMessage.exec();
    }

    smtp.quit();

    for (auto file : files) {
        delete file;
    }

    for (auto attachment : attachments) {
        delete attachment;
    }

}

void SendEmail::errorMessage(const QString &message)
{
    QErrorMessage err (this);

    err.showMessage(message);

    err.exec();
}

void SendEmail::slotError(SmtpClient::SmtpError e)
{
    qDebug() << __FUNCTION__ << e;
}

void SendEmail::slotStateChanged(SmtpClient::ClientState s)
{
    qDebug() << __FUNCTION__ << s;
}

void SendEmail::slotMailSent()
{
    qDebug() << __FUNCTION__;
}
