#include "interop.h"
#include <iostream>
Interop::Interop(std::string username, std::string password)
{
    QNetworkRequest req;
    QUrlQuery query;
    QUrl params;
    QByteArray postData;

    networkAccess = new QNetworkAccessManager();
    connect(networkAccess, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(replyFinished(QNetworkReply*)));

    req.setUrl(QUrl("http://localhost:8080"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    query.addQueryItem("username", QString::fromStdString(username));
    query.addQueryItem("password", QString::fromStdString(password));

    params.setQuery(query);
    postData = params.toEncoded(QUrl::RemoveFragment);

    QNetworkReply *reply = networkAccess->post(req, postData);
}

void Interop::replyFinished(QNetworkReply *reply)
{
    if(reply->error()) {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else {
        qDebug() << "ContentType: " << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << "Last Modified: " << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
        qDebug() << "Content Length: " << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << "HTTP Code: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP Reason: " << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        qDebug() << "Response: " << reply->readAll();
    }
    reply->deleteLater();
}

QJsonDocument Interop::getMissions() {

}

QJsonDocument Interop::getMission(int id) {

}

void Interop::sendTelemetry(float latitude, float longitude, float altitude_msl, float uas_heading) {

}

QJsonDocument Interop::sendODLC(QJsonDocument odlc) {

}

QJsonDocument Interop::getUploadedODLCs() {

}

QJsonDocument Interop::getUploadedODLC(int id) {

}

QJsonDocument Interop::updateODLC(int id, QJsonDocument data) {

}

void Interop::deleteODLC(int id) {

}

//QImage Interop::getODLCThumbnail(int id) {

//}

//void Interop::updateODLCThumbnail(int id, QImage image) {

//}

void Interop::deleteODLCThumbnail(int id) {

}
