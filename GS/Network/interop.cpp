#include "interop.h"

QString ENDPOINT = "http://localhost:8000";

Interop::Interop(std::string username, std::string password)
{
    QNetworkRequest req;
    QUrl params;

    networkAccess = new QNetworkAccessManager();
    connect(networkAccess, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(replyFinished(QNetworkReply *)));

    req.setUrl(QUrl(ENDPOINT + "/api/login"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QByteArray postData;
    postData.append("username=" + QString::fromStdString(username) + "&");
    postData.append("password=" + QString::fromStdString(password));

    QNetworkReply *reply = networkAccess->post(req, postData);
    waitForResponse(reply);
    qDebug() << "Response: " << reply->readAll();
    // want to raise an error here if failure
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

void Interop::waitForResponse(QNetworkReply* reply) {
    while(!reply->isFinished()) {
        qApp->processEvents();
    } // spin
}

QJsonDocument Interop::getMissions() {
    QNetworkRequest req;

    req.setUrl(QUrl(ENDPOINT + "/api/missions"));
    QNetworkReply* reply = networkAccess->get(req);
    waitForResponse(reply);

    qDebug() << "Response: " << reply->readAll();
    return QJsonDocument::fromJson(reply->readAll());
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
