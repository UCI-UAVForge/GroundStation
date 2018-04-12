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
#include "waypoint.h"
#include "obstacles.h"
#include "missionpath.h"
#include "point.hpp"
#include "waypt.h"


struct FlyZone {
    qreal max_alt;
    qreal min_alt;
    QList<QVector2D> boundary_points;
};

struct MissionTakeoff {
    float altitude;
    float pitch;
    float yawAngle;
};

class Mission : public QObject {
    Q_OBJECT
public:
    explicit Mission(QObject *parent = nullptr);

    Mission(QJsonObject);
    Mission(QJsonObject mission_obj, QJsonDocument obstacles_doc);
    Mission(const Mission& mission);

    int id;
    bool active;
    QVector2D home_pos;
    QVector2D air_drop_pos;
    QVector2D off_axis_odlc_pos;
    QVector2D emergent_last_known_pos;
    MissionPath mission_path;
    MissionPath interopPath;
    MissionPath generatedPath;
    MissionTakeoff takeoff;
    QList<QVector3D> * search_grid_points;
    QList<FlyZone> fly_zones;
    Obstacles obstacles;

    QList<QPolygonF> get_obstacles();
    void printJDoc();
    Point toECEF(double lat, double lon, double alt);
    QVector<Waypoint::WP> constructWaypoints(bool interop);
    uint16_t completeMissionLength(bool interop);
//    void setActions_wp();
    Obstacles getObstacles();
    QJsonDocument toJson();

signals:
    void loadToUAV(int seq, int cmd, float params[]);

private:
    QVector2D posToPoint(QJsonObject obj);
    QVector3D posTo3DPoint(QJsonObject obj);
    QJsonValue pointToPos(QVector2D point);

    MissionPath setMissionPath(QJsonArray pointArray);
    QList<FlyZone> setFlyZones(QJsonArray flyZoneArray);
    QList<QVector2D> setPoints(QJsonArray pointArray);
    QList<QVector3D> * set3DPoints(QJsonArray pointArray);
    double meters_to_deg(double meters, double latitude)
    {
        return (meters / (111.32 * 1000 * cos(latitude * (M_PI / 180))));
    }
    Waypoint::WP missionPrologue();
    Waypoint::WP generateTakeoff();
};

#endif // MISSION_H
