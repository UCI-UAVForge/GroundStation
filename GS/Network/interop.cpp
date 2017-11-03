#include "interop.h"

QString ENDPOINT = "http://localhost:8000";

Interop::Interop(const std::string& username, const std::string& password)
{
    networkAccess = new QNetworkAccessManager();
    connect(networkAccess, &QNetworkAccessManager::finished, this, &Interop::replyFinished);

    std::vector<HeaderSet> headers;
    headers.push_back(HeaderSet{QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded"});

    QByteArray postData;
    postData.append("username=" + QString::fromStdString(username) + "&");
    postData.append("password=" + QString::fromStdString(password));

    QNetworkReply *reply = postRequest(ENDPOINT + "/api/login", postData, headers);
    // want to raise an error here if failure
    waitForResponse(reply);
    if (reply->error()) {
        throw std::invalid_argument("bad login");
    }
}

void Interop::replyFinished(QNetworkReply* reply)
{
    if(reply->error()) {
        qCritical() << "Something bad happened to one of our requests: " << reply->errorString();
        qCritical() << reply->error();
    }
//    else {
//        qDebug() << "ContentType: " << reply->header(QNetworkRequest::ContentTypeHeader).toString();
//        qDebug() << "Last Modified: " << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
//        qDebug() << "Content Length: " << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
//        qDebug() << "HTTP Code: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
//        qDebug() << "HTTP Reason: " << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
//        qDebug() << "Response: " << reply->peek(reply->bytesAvailable());
//    }
    reply->deleteLater();
}

void Interop::waitForResponse(QNetworkReply* reply) {
    while(!reply->isFinished()) {
        qApp->processEvents();
    } // spin
}

QNetworkReply* Interop::sendRequest(const QNetworkAccessManager::Operation& operation, const QString& url, const QByteArray& data, const std::vector<HeaderSet>& headers) {
    QNetworkRequest req{QUrl(url)};
    for(HeaderSet headerSet : headers) {
        req.setHeader(headerSet.header, headerSet.value);
    }
    QNetworkReply* reply;

    switch (operation) {
    case QNetworkAccessManager::GetOperation:
        reply = networkAccess->get(req);
        break;
    case QNetworkAccessManager::PostOperation:
        reply = networkAccess->post(req, data);
        break;
    case QNetworkAccessManager::DeleteOperation:
        reply = networkAccess->deleteResource(req);
        break;
    case QNetworkAccessManager::PutOperation:
        reply = networkAccess->put(req, data);
        break;
    default:
        throw std::invalid_argument("operation not implemented");
    }
    waitForResponse(reply);
//    qDebug() << reply->request().url();
//    qDebug() << "Response: " << reply->peek(reply->bytesAvailable());
    return reply;
}

QNetworkReply* Interop::getRequest(const QString& url)
{
    return sendRequest(QNetworkAccessManager::GetOperation, url);
}

QNetworkReply* Interop::postRequest(const QString& url, const QByteArray& data, const std::vector<HeaderSet>& headers)
{
    return sendRequest(QNetworkAccessManager::PostOperation, url, data, headers);
}

QNetworkReply* Interop::deleteRequest(const QString& url)
{
    return sendRequest(QNetworkAccessManager::DeleteOperation, url);
}

QNetworkReply* Interop::putRequest(const QString& url, const QByteArray& data, const std::vector<HeaderSet>& headers)
{
    return sendRequest(QNetworkAccessManager::PutOperation, url, data, headers);
}

QJsonDocument Interop::getMissions() {
    QNetworkReply* reply = getRequest(ENDPOINT + "/api/missions");
    return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument Interop::getMission(int id) {
    QNetworkReply* reply = getRequest(ENDPOINT + "/api/missions/" + QString::number(id));
    return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument Interop::getObstacles()
{
    QNetworkReply* reply = getRequest(ENDPOINT + "/api/obstacles");
    return QJsonDocument::fromJson(reply->readAll());
}

void Interop::sendTelemetry(float latitude, float longitude, float altitude_msl, float uas_heading) {
    std::vector<HeaderSet> headers;
    headers.push_back(HeaderSet{QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded"});

    QByteArray postData;
    postData.append("latitude=" + QString::number(latitude) + "&");
    postData.append("longitude=" + QString::number(longitude) + "&");
    postData.append("altitude_msl=" + QString::number(altitude_msl) + "&");
    postData.append("uas_heading=" + QString::number(uas_heading));

    QNetworkReply *reply = postRequest(ENDPOINT + "/api/telemetry", postData, headers);
}

QJsonDocument Interop::sendODLC(const QJsonDocument& odlc) {
    std::vector<HeaderSet> headers;
    headers.push_back(HeaderSet{QNetworkRequest::ContentTypeHeader, "application/json"});

    QNetworkReply *reply = postRequest(ENDPOINT + "/api/odlcs", odlc.toJson(), headers);
    return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument Interop::getUploadedODLCs() {
    QNetworkReply* reply = getRequest(ENDPOINT + "/api/odlcs");
    return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument Interop::getUploadedODLC(int id) {
    QNetworkReply* reply = getRequest(ENDPOINT + "/api/odlcs/" + QString::number(id));
    return QJsonDocument::fromJson(reply->readAll());
}

QJsonDocument Interop::updateODLC(int id, const QJsonDocument& data) {
    std::vector<HeaderSet> headers;
    headers.push_back(HeaderSet{QNetworkRequest::ContentTypeHeader, "application/json"});

    QNetworkReply* reply = putRequest(ENDPOINT + "/api/odlcs/" + QString::number(id), data.toJson(), headers);
    return QJsonDocument::fromJson(reply->readAll());
}

void Interop::deleteODLC(int id) {
    QNetworkReply* reply = deleteRequest(ENDPOINT + "/api/odlcs/" + QString::number(id));
}

QImage Interop::getODLCThumbnail(int id) {
    QNetworkReply* reply = getRequest(ENDPOINT + "/api/odlcs/" + QString::number(id) + "/image");
    return QImage::fromData(reply->readAll());
}

void Interop::updateODLCThumbnail(int id, const QImage& image) {
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPG");

    std::vector<HeaderSet> headers;
    headers.push_back(HeaderSet{QNetworkRequest::ContentTypeHeader, "image/jpeg"});

    QNetworkReply *reply = postRequest(ENDPOINT + "/api/odlcs/" + QString::number(id) + "/image", ba, headers);
    // do something on error
}

void Interop::deleteODLCThumbnail(int id) {
    QNetworkReply* reply = deleteRequest(ENDPOINT + "/api/odlcs/" + QString::number(id));
}
