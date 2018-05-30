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


struct FlyZone {
    qreal max_alt;
    qreal min_alt;
    QList<QVector2D> boundary_points;
};

class Mission : public QObject {
    Q_OBJECT
public:
    explicit Mission(QObject *parent = nullptr);

    Mission(QJsonObject obj);
    Mission(QJsonObject mission_obj, QJsonObject obs_obj);

    int id;
    bool active;
    QVector2D home_pos;
    QVector2D air_drop_pos;
    QVector2D off_axis_odlc_pos;
    QVector2D emergent_last_known_pos;
    MissionPath interopPath;
    MissionPath generatedPath;
    QList<QVector3D> * search_grid_points;
    QList<FlyZone> fly_zones;
    Obstacles obstacles;
    Waypt takeoff;
    MissionPath landing;

    QList<QPolygonF> get_obstacles();
    void printJDoc();
    Point toECEF(double lat, double lon, double alt);
    QVector<Waypoint::WP> constructWaypoints();
//    void setActions_wp();
//    Obstacles getObstacles();
    QList<QVector3D> *toList();
    QVector3D moveWaypoint(int index, QKeyEvent * k);
    void loadJson(QJsonObject obj);
    void loadInteropJson(QJsonObject &obj);
    QJsonDocument toJson();

signals:
    void loadToUAV(int seq, int cmd, float params[]);

private:
    QVector2D posToPoint(QJsonObject obj);
    QVector3D posTo3DPoint(QJsonObject obj);
    QJsonValue pointToPos(QVector2D point);

    MissionPath setMissionPath(QJsonArray pointArray);
    MissionPath setMissionPath2(QJsonArray pointArray);
    QList<FlyZone> setFlyZones(QJsonArray flyZoneArray);
    QList<QVector2D> setPoints(QJsonArray pointArray);
    QList<QVector3D> * set3DPoints(QJsonArray pointArray);
    float toMeters(float feet);
    float toFeet(float meters);
    void defaultLandingTakeoff();
    double meters_to_deg(double meters, double latitude)
    {
        return (meters / (111.32 * 1000 * cos(latitude * (M_PI / 180))));
    }
    Waypoint::WP missionPrologue();
};

#endif // MISSION_H
