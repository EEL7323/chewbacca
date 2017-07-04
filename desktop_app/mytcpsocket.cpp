#include "mytcpsocket.h"
#include "QJsonObject"
#include "QJsonDocument"
#include "QJsonArray"
#include "QFile"
#include "QTextStream"

MyTcpSocket::MyTcpSocket(QObject *parent) :
    QObject(parent)
{
}



void MyTcpSocket::doConnect()
{
    //qDebug() << "DOCONNECT";
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";


    socket->connectToHost("127.0.0.1", 5000);

    if(!socket->waitForConnected(15000))
    {
        qDebug() << "Error: " << socket->errorString();
    }

}

void MyTcpSocket::connected()
{
    //qDebug() << "O CARTAO eh";
    //qDebug() << cartao;
    QString t = QString("GET /user/id/card/%1 HTTP/1.0\r\n\r\n\r\n\r\n").arg(cartao);


    socket->write(t.toLocal8Bit());
       //qDebug() << "WRITEN...";
    socket->waitForReadyRead(10000);
    /*QString sok = "";
    while (socket->bytesAvailable() > 0){
    sok.append(socket->readAll());
    socket->waitForReadyRead(5000);
    }
    qDebug() << sok;*/


}

void MyTcpSocket::disconnected()
{
    //qDebug() << "disconnected...";
}

void MyTcpSocket::bytesWritten(qint64 bytes)
{
    //qDebug() << bytes << " bytes written...";
}

void MyTcpSocket::readyRead()
{
    QString d = "";
    while (socket->bytesAvailable() > 0){
    d.append(socket->readAll());
    socket->waitForReadyRead(5000);
    }

    data = d;
}
