#ifndef INTEROP_H
#define INTEROP_H
#import <QtNetwork>

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
public:
    Interop(std::string username, std::string password);
    QJsonDocument getMissions();
    QJsonDocument getMission(int id);
    void sendTelemetry(float latitude, float longitude, float altitude_msl, float uas_heading);
    QJsonDocument sendODLC(QJsonDocument odlc);
    QJsonDocument getUploadedODLCs();
    QJsonDocument getUploadedODLC(int id);
    QJsonDocument updateODLC(int id, QJsonDocument data);
    void deleteODLC(int id);
    QImage getODLCThumbnail(int id);
    void updateODLCThumbnail(int id, QImage image);
    void deleteODLCThumbnail(int id);
public slots:
    void replyFinished(QNetworkReply *reply);
};
#endif // INTEROP_H
