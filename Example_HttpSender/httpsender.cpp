#include "httpsender.h"
#include <QMessageBox>

HttpSender::HttpSender(QObject *parent) : QObject(parent)
{
    m_nam = new QNetworkAccessManager(this);
    m_nam->setNetworkAccessible(QNetworkAccessManager::Accessible);
    connect(m_nam, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)), this, SLOT(slot_NetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
}

void HttpSender::send(QString url)
{
    qDebug() << __FUNCTION__ << url;
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply = m_nam->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
    //connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(slotSslErrors(QList<QSslError>)));
}

void HttpSender::slotFinished()
{
    QNetworkReply* reply = (QNetworkReply*)sender();

    if (!reply) return;

    //qInfo() << __FUNCTION__
    //        << "  Send URL: " << reply->url().url();

    reply->deleteLater();
}

void HttpSender::slotReadyRead()
{
    QNetworkReply* reply = (QNetworkReply*)sender();
    if (!reply) return;

    QString result = reply->readAll();
    qInfo() << __FUNCTION__
            << "  Send URL: " << reply->url().url()
            << "  Result URL" << result
            << "  headerList " << reply->rawHeaderList()
            << "  header date : " << reply->rawHeader("Date");

    // Mon, 12 Jun 2023 02:24:52 GMT
    QString headerDate = reply->rawHeader("Date");
    qDebug() << __FUNCTION__ << "headerDate: " << headerDate;
}

void HttpSender::slotError(QNetworkReply::NetworkError error)
{
    qDebug() << "HttpSender::slotError error: " << error;

    QNetworkReply* reply = (QNetworkReply*)sender();

    if (!reply) return;

    qInfo() << __FUNCTION__
            << "  Send URL: " << reply->url().url()
            << " error : " << reply->errorString()
            << " code: " << reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toInt();

    int _netAcc = m_nam->networkAccessible();
    QString error1 = QString("%1, %2, %3").arg(reply->errorString()).arg(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()).arg(_netAcc);
    QMessageBox::information(nullptr, "tesst222", error1);


}

void HttpSender::slot_NetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility acc)
{
    int netAcc = m_nam->networkAccessible();
    int netacc2 = acc;
    switch (netAcc)
    {
        case QNetworkAccessManager::Accessible:
            // You are online.
            break;

        case QNetworkAccessManager::NotAccessible:
            // You are offline.
            break;

        case QNetworkAccessManager::UnknownAccessibility:
        default:
            // You know nothing, Jon Snow.
            break;
    }

    QString error1 = QString("%1 , %2").arg(netAcc).arg(netacc2);
    QMessageBox::information(nullptr, "tesst1111", error1);

    m_nam->setNetworkAccessible(QNetworkAccessManager::Accessible);
    netAcc = m_nam->networkAccessible();

    QString error21 = QString("%1, %2").arg(netAcc).arg(netacc2);
    QMessageBox::information(nullptr, "tesst1111", error21);
}
