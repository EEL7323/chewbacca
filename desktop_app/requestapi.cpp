#include "requestapi.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QEventLoop>

namespace Ui {
class MainWindow;
}

RequestApi::RequestApi(QObject *parent) : QObject(parent)
{
    this->manager = new QNetworkAccessManager();
}

QNetworkRequest RequestApi::makeRequest(QString url)
{
    connect(this->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    return request;
}

void RequestApi::makeRequestGET(QString url)
{
    int statusCode;
    QNetworkRequest request = RequestApi::makeRequest(url);
    QNetworkReply *reply = this->manager->get(request);
    //connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));

}

void RequestApi::makeRequestPOST(QString url, QJsonObject json)
{

    QNetworkRequest request = RequestApi::makeRequest(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    this->manager->post(request,QJsonDocument(json).toJson());
    //connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void RequestApi::replyFinished(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    //qDebug("Reply");
    //qDebug()<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode == 201 || statusCode == 200)
    {
        qDebug()<<"Operacao efetuada com sucesso";
    } else {
        qDebug()<<"Erro: Status code";
        qDebug()<<statusCode;
    }

}

void RequestApi::slotError(QNetworkReply::NetworkError error)
{
    qDebug("slotError");
    qDebug() << error;
}

