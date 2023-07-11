#include "httpserver.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QUrl>
#include <QDebug>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

HttpServer::HttpServer(QObject *parent) : QObject(parent)
{
//    m_tcpServer = new QTcpServer();
//    m_tcpServer->listen(QHostAddress::LocalHost, 80);
//    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(connectClient()));

    QHttpServer *server = new QHttpServer(this);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));

    server->listen(QHostAddress::Any, 50000);
}

void HttpServer::connectClient()
{
//    QTcpSocket *socket = m_tcpServer->nextPendingConnection();
//    if(socket)
//    {

//        socket->waitForReadyRead(1000);


//        //result code;
//        // get request
//        //QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
//        //if (tokens.at(0) == "GET")
//        //{
//        //
//        //}
//        QByteArray data = socket->readAll();
//        //std::string szRequest = data.toStdString();
//        qDebug() << __FUNCTION__ << data;
//        // make response
//        QByteArray codSuccess = "HTTP/1.1 200 OK\r\n\r\n success";
//        socket->write(codSuccess);

//        socket->flush();
//        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
//        socket->disconnectFromHost();
//    }
}

void HttpServer::handleRequest(QHttpRequest* req, QHttpResponse* resp)
{
    QString path = req->path();
    //QRegExp exp("^/hpcad?([a-z]+)$");
    //if( exp.indexIn(req->path()) != -1 )
    if (path == "/hpcad")
    {
        //resp->setHeader("Content-Type", "text/xml");
        resp->writeHead(200);

        //QString name = exp.capturedTexts()[1];
        QString body =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                "<hpcad>"
                 "<result id=\"200\" value=\"OK\"/>"
                 "<command id=\"GetCaseInfo\">"
                  "<parameter id=\"case_id\" value=\"asdf\"/>"
                  "<parameter id=\"patient_id\" value=\"qwer\"/>"
                  "<parameter id=\"case_status\" value=\"1\"/>"
                  "<parameter id=\"last_step\" value=\"3\"/>"
                 "</command>"
                "</hpcad>";
        resp->end(body.toUtf8());
        //resp->end(body.arg(name).toUtf8());
    }
    else
    {
        resp->writeHead(403);
        resp->end(QByteArray("You aren't allowed here!"));
    }
}
