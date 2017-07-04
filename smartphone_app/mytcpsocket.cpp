/*

Faz a conexão com o servidor e extrai dos arquivos json informações para as transações,
contador de pessoas no RU e saldo.

*/


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


void MyTcpSocket::ConnectInicial()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    //qDebug() << "connecting...";


    socket->connectToHost("192.168.0.103", 5000);


    if(!socket->waitForConnected(5000))
    {
        //qDebug() << "Error: " << socket->errorString();
    }
}



void MyTcpSocket::connected()
{


    qDebug() << "connected...";

    File w;

    QString mFilename = "userid.txt";
    QString userid = "";
    userid = w.Read(mFilename, userid);
    QString t = QString("GET /transaction/%1 HTTP/1.0 \r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n").arg(userid);
    socket->write(t.toLocal8Bit());
    socket->waitForReadyRead(5000);

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
    File r;
    qDebug() << "reading...";
    qDebug() << "bites" << socket->bytesAvailable();
    QString data = "";
    while (socket->bytesAvailable() > 0){
    data.append(socket->readAll());
    socket->waitForReadyRead(5000);
    }
    qDebug() << "DATA" << data;
    data.remove(0,147);
    QString mFilename = "data.txt";
    r.Write(mFilename, data);


    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    qDebug() << "jsonDoc" << jsonDoc;
    QJsonArray jsonArray = jsonDoc.array();

    if (jsonDoc.isEmpty()){
        mFilename = "log.txt";
        r.Write(mFilename, "ERROR");
    }
    else
    {
    int jsonInt;
    int i = 0;
    int saldo = 0;
    QString transactions = "";
    QString time = "";
    QString matricula = "";
    QString nome = "";
    while (i < jsonArray.size()) {
    QJsonObject jsonObj = jsonArray[i].toObject();
    //qDebug() << "object" << jsonObj;
    jsonInt = jsonObj.value("event").toInt();
    saldo = saldo + jsonInt;
    matricula = jsonObj.value("matricula").toString();
    nome = jsonObj.value("username").toString();
    qDebug() << "json int " << jsonInt;
    if(jsonInt < 0){
    transactions.append("\n\n Creditos Utilizados:   ");
    transactions.append(QString::number(jsonInt));
    }
    else {
    transactions.append("\n\n Creditos Inseridos:   ");
    transactions.append(QString::number(jsonInt));
    }
    time = jsonObj.value("timestamp").toString();
    transactions.append("\n Data e Hora:   ");
    time = time.remove("GMT");
    transactions.append(time.remove(0,4));
    qDebug() << "transacoes " << time;
    i = i +1;
    //qDebug() << "i" << i;
    }



    QString saldoFinal = QString::number(saldo);
    mFilename = "matricula.txt";
    r.Write(mFilename, matricula);
    mFilename = "nome.txt";
    r.Write(mFilename, nome);
    mFilename = "saldo.txt";
    r.Write(mFilename, saldoFinal);
    mFilename = "transactions.txt";
    r.Write(mFilename, transactions);
    mFilename = "log.txt";
    r.Write(mFilename, "OK");
    }
}


void MyTcpSocket::ConnectContador()
{
    socket = new QTcpSocket(this);

    socket->connectToHost("192.168.0.103", 5000);


    QString t = QString("GET /contador HTTP/1.0 \r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
    socket->write(t.toLocal8Bit());
    socket->waitForReadyRead(5000);


    File c;
    QString contador = "";
    while (socket->bytesAvailable() > 0){
    contador.append(socket->readAll());
    socket->waitForReadyRead(5000);
    }
    contador.remove(0,146);


    QJsonDocument contadorDoc = QJsonDocument::fromJson(contador.toUtf8());
    QJsonArray contadorArray = contadorDoc.array();
    QJsonObject contadorObj = contadorArray[0].toObject();
    int pessoas = contadorObj.value("contador").toInt();
    QString pessoasFinal = QString::number(pessoas);
    QString mFilename = "pessoas.txt";
    c.Write(mFilename, pessoasFinal);
}
