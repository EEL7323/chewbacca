#ifndef REQUESTAPI_H
#define REQUESTAPI_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>


class RequestApi : public QObject
{
    Q_OBJECT
public:
    explicit RequestApi(QObject *parent = 0);
    QNetworkRequest makeRequest(QString url);
    void makeRequestGET(QString url);
    void makeRequestPOST(QString url, QJsonObject json);
    QNetworkAccessManager* manager;
private slots:
    void replyFinished(QNetworkReply* reply);
    void slotError(QNetworkReply::NetworkError error);
};


#endif // REQUESTAPI_H
