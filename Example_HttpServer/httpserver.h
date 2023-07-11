#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "qhttpserverfwd.h"
#include <QObject>

class QTcpServer;
class HttpServer : public QObject
{
    Q_OBJECT

private:
    QTcpServer *m_tcpServer;

public:
    HttpServer(QObject *parent = 0);

private slots:
    void connectClient();

    void handleRequest(QHttpRequest *req, QHttpResponse *resp);
};

#endif // HTTPSERVER_H
