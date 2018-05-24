#ifndef INTEROP_H
#define INTEROP_H
#include <QtNetwork>
#include <QImage>
struct HeaderSet {
    QNetworkRequest::KnownHeaders header;
    QVariant value;
};
class Interop : public QObject
{
    Q_OBJECT
private:
    enum Orientations {
        N,
        NE,
        E,
        SE,
        S,
        SW,
        W,
        NW
    };
    enum Shapes {
        circle,
        semicircle,
        quarter_circle,
        triangle,
        square,
        rectangle,
        trapezoid,
        pentagon,
        hexagon,
        heptagon,
        octagon,
        star,
        cross
    };
    enum Colors {
        white,
        black,
        gray,
        red,
        blue,
        green,
        yellow,
        purple,
        brown,
        orange
    };
private:
    QNetworkAccessManager* networkAccess;
    void waitForResponse(QNetworkReply* reply);
    QNetworkReply* sendRequest(const QNetworkAccessManager::Operation& operation, const QString& url, const QByteArray& data = {}, const std::vector<HeaderSet>& headers = {});
    QNetworkReply* getRequest(const QString& url);
    QNetworkReply* postRequest(const QString& url, const QByteArray& data, const std::vector<HeaderSet>& headers = {});
    QNetworkReply* deleteRequest(const QString& url);
    QNetworkReply* putRequest(const QString& url, const QByteArray& data, const std::vector<HeaderSet>& headers = {});
public:
    Interop(const std::string& username, const std::string& password);
    QJsonDocument getMissions();
    QJsonDocument getMission(int id);
    QJsonDocument getObstacles();
    void sendTelemetry(float latitude, float longitude, float altitude_msl, float uas_heading);
    QJsonDocument sendODLC(const QJsonDocument& odlc);
    QJsonDocument getUploadedODLCs();
    QJsonDocument getUploadedODLC(int id);
    QJsonDocument updateODLC(int id, const QJsonDocument& data);
    void deleteODLC(int id);
    QImage getODLCThumbnail(int id);
    void updateODLCThumbnail(int id, const QImage& image);
    void deleteODLCThumbnail(int id);
public slots:
    void replyFinished(QNetworkReply* reply);
};
#endif // INTEROP_H
