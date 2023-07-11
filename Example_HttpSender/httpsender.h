#ifndef HTTPSENDER_H
#define HTTPSENDER_H

#include <QObject>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class HttpSender : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager* m_nam;

public:
    explicit HttpSender(QObject *parent = nullptr);

    //void send(QString cmd, QUrlQuery query);
    void send(QString url);

signals:

private slots:
    void slotFinished();
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError);
    void slot_NetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility);
};

#endif // HTTPSENDER_H
