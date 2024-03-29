#include "mytcpsocket.h"
#include <QApplication>

MyTcpSocket::MyTcpSocket()
{
    command_socket = new QTcpSocket();
    file_socket = new QTcpSocket();
    tcpServer_c = new QTcpServer();
    tcpServer_f = new QTcpServer();

    tcpServer_c->listen(QHostAddress::Any,PORT1);
    tcpServer_f->listen(QHostAddress::Any,PORT2);

    connect(tcpServer_c,SIGNAL(newConnection()),this,SLOT(on_connect_c()));
    connect(tcpServer_f,SIGNAL(newConnection()),this,SLOT(on_connect_f()));
}

void MyTcpSocket::on_connect_c(){
    command_socket = tcpServer_c->nextPendingConnection();

    QString ip = command_socket->peerAddress().toString();
    quint16 port = command_socket->peerPort();

    qDebug() << __FUNCTION__ << ip << port;
    //qDebug()<<QString("[%1:%2]성공적인 연결").arg(ip).arg(port);
    command_socket->disconnect();
    connect(command_socket,SIGNAL(readyRead()),this,SLOT(on_read_command()));
}

void MyTcpSocket::on_connect_f(){
    file_socket = tcpServer_f->nextPendingConnection();

    QString ip = file_socket->peerAddress().toString();
    quint16 port = file_socket->peerPort();

    qDebug() << __FUNCTION__ << ip << port;
    //qDebug()<<QString("[%1:%2]성공적인 연결").arg(ip).arg(port);
    file_socket->disconnect();
    connect(file_socket,SIGNAL(readyRead()),this,SLOT(on_read_file()));
}

void MyTcpSocket::set_file(QString filePath){
    if(filePath.isEmpty()){
        qDebug() << __FUNCTION__ << "fail path..";
        //qDebug()<<"파일 경로 설정에 실패했습니다.";
        return;
    }
    QFileInfo info(filePath);
    filename = info.fileName();
    filesize = info.size();
    sendSize = 0;

    file.setFileName(filePath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if(false == isOk)
    {
        qDebug() << __FUNCTION__ << ERROR_CODE_77;
        //qDebug()<<ERROR_CODE_77;
    }
    return;
}

void MyTcpSocket::send_command(){
    QString head = QString("%1##%2##%3").arg(FILE_CODE).arg(filename).arg(filesize);
    qint64 len = command_socket->write(head.toUtf8());
    if(len <= 0){
        qDebug() << __FUNCTION__ << ERROR_CODE_110;
        //qDebug()<<ERROR_CODE_110;
        file.close();
    }
}

void MyTcpSocket::send_command(int code,QString str){
    QString head = QString("%1##%2").arg(code).arg(str);
    qint64 len = command_socket->write(head.toUtf8());
    if(len <= 0){
        qDebug() << __FUNCTION__ << code;
    }
}

void MyTcpSocket::send_file(){
    qDebug() << __FUNCTION__;
    qint64 len = 0;
    do
    {
        char buf[4*1024] = {0};
        len = file.read(buf,sizeof(buf));

        qDebug()<<file_socket->write(buf,len);

        sendSize += len;
        qDebug()<<len<<sendSize;
    }while(len > 0);

     if(sendSize == filesize)
     {
         //qDebug("보낸 파일");
         file.close();

         file_socket->disconnect();
         file_socket->close();
     }
}

void MyTcpSocket::on_read_command(){
    QByteArray buf = command_socket->readAll();
    qDebug() << __FUNCTION__ << buf;

    int code = QString(buf).section("##",0,0).toInt();
    if(code == FILE_CODE)
    {

        filename = QString(buf).section("##",1,1);
        filesize = QString(buf).section("##",2,2).toInt();
        recvSize = 0;

        qDebug() << __FUNCTION__ << filename;
        filename = qApp->applicationDirPath() + "/" + filename;
        file.setFileName(filename);
        bool isOk = file.open(QIODevice::WriteOnly);
        if(false == isOk)
        {
            qDebug()<<"writeonly error 49";
            command_socket->disconnectFromHost();
            command_socket->close();
            return;
        }
        qDebug() << __FUNCTION__ << filename << filesize/1024;

        //qDebug()<<QString("파일 이름 :%1\n 크기:%2 kb").arg(filename).arg(filesize/1024);
        send_command(FILE_HEAD_REC_CODE,"ok");
    }
    if(code == FILE_DOWN_LOAD){
        send_file();
    }
}

void MyTcpSocket::on_read_file(){
    QByteArray buf = file_socket->readAll();
    qint64 len = file.write(buf);

    qDebug()<<recvSize;
    if(len > 0)
    {
       recvSize += len;
       qDebug()<< len;
    }

    if(recvSize == filesize)
    {
        file.close();
        //QMessageBox::information(this,"완료","파일 수신 완료");
        send_command(FILE_REC_CODE,"ok");
        file_socket->disconnectFromHost();
        file_socket->close();
    }
}
