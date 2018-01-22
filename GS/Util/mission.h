#ifndef MISSION_H
#define MISSION_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQuickWidget>
#include <QQuickItem>
#include "mavlink.h"
#include "link.h"
#include <QObject>


struct FlyZone {
    qreal max_alt;
    qreal min_alt;
    QList<QVector2D> * boundary_points;
};

struct MissionWaypoints {
    QList<int> * actions;
    QList<QVector3D> * waypoints;
};

class Mission : public QObject {
    Q_OBJECT
public:
    explicit Mission(QObject *parent = nullptr);

    Mission(QJsonObject);

    int id;
    bool active;
    QVector2D home_pos;
    QVector2D air_drop_pos;
    QVector2D off_axis_odlc_pos;
    QVector2D emergent_last_known_pos;
    MissionWaypoints mission_waypoints;
    QList<QVector3D> * search_grid_points;
    QList<FlyZone> * fly_zones;

    void loadWaypoint(mavlink_mission_request_t mrequest);
    void clearMission(QQuickWidget * mapWidget);
    void printJDoc();
    bool DNE();

signals:
    void loadToUAV(int seq, int cmd, float params[]);

private:

    QVector2D posToPoint(QJsonObject obj);
    QVector3D posTo3DPoint(QJsonObject obj);

    MissionWaypoints setMissionWaypoints(QJsonArray pointArray);
    QList<FlyZone> * setFlyZones(QJsonArray flyZoneArray);
    QList<QVector2D> * setPoints(QJsonArray pointArray);
    QList<QVector3D> * set3DPoints(QJsonArray pointArray);
};

#endif // MISSION_H
