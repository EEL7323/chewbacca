#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>



class MyTcpSocket : public QObject
{
    Q_OBJECT
    QString cartao;
    QString data;
public:
    explicit MyTcpSocket(QObject *parent = 0);

    void doConnect();

    void setCartao(QString C) {
        cartao = C;
    }

    void setData(QString d) {
        data = d;
    }

    QString getCartao() {
       return cartao;
    }


    QString getData(){
        return data;
    }

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;

};

#endif // MYTCPSOCKET_H
