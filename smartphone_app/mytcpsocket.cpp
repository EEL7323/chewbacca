#include "mytcpsocket.h"
#include "QJsonObject"
#include "QJsonDocument"
#include "QJsonArray"
#include "QFile"
#include "QTextStream"
#include "file.h"

MyTcpSocket::MyTcpSocket(QObject *parent) :
    QObject(parent)
{
}



void MyTcpSocket::doConnect()
{
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
    File q;

    QString mFilename = "matricula.txt";
    QString Matricula = q.Read(mFilename, Matricula);
    qDebug() << "connected...";
    qDebug() << Matricula;
    QString t = QString("GET /transaction/%1 HTTP/1.0\r\n\r\n\r\n\r\n").arg(Matricula);


    socket->write(t.toLocal8Bit());
       qDebug() << "WRITEN...";
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
    qDebug() << "disconnected...";
}

void MyTcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void MyTcpSocket::readyRead()
{
    File s;
    qDebug() << "reading...";


    QString data = "";
    while (socket->bytesAvailable() > 0){
    data.append(socket->readAll());
    socket->waitForReadyRead(5000);
    }
    data.remove(0,147);
    qDebug() << data;
    QString mFilename = "data.txt";
    s.Write(mFilename, data);


    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    qDebug() << "json" << jsonDoc;
    QJsonArray jsonArray = jsonDoc.array();

    if (jsonDoc.isEmpty()){
        qDebug() << "Matricula incorreta";
        QString mFilename = "log.txt";
        s.Write(mFilename, "ERROR");

    }
    else{
    QString mFilename = "log.txt";
    s.Write(mFilename, "OK");

    qDebug() << "Matricula correta";
    int jsonInt;
    int i = 0;
    int saldo = 0;
    while (i < jsonArray.size()) {
    QJsonObject jsonObj = jsonArray[i].toObject();
    qDebug() << "object" << jsonObj;
    jsonInt = jsonObj.value("event").toInt();
    saldo = saldo + jsonInt;
    qDebug() << "value" << saldo;
    i = i +1;
    //qDebug() << "i" << i;
    }


    QString saldoFinal = QString::number(saldo);
    mFilename = "saldo.txt";
    s.Write(mFilename, saldoFinal);
    }



}
