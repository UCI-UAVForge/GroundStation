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

    QVector<double> *getValuesForID(int id);
    QVector<double> *getValuesForIndex(int index);
    double getValueForIndexAndID(int index,int id);

    bool save(QString filename);
    int numOfEntries();
    void loadWaypoint(mavlink_mission_request_t mrequest);
    void setMission(QJsonDocument jsonDoc);

    QJsonObject get_off_axis_odlc_pos();
    QJsonArray get_search_grid_points();
    QJsonArray get_mission_waypoints();
    QJsonArray get_fly_zones();
    QJsonObject get_emergent_last_known_pos();
    bool isActive();
    int get_id();
    QJsonObject get_home_pos();
    QJsonObject get_air_drop_pos();
    void loadMissionObjects(QQuickWidget * mapWidget);
    void clearMission(QQuickWidget * mapWidget);
    void printJDoc();
    bool DNE();

signals:
    void loadToUAV(int seq, int cmd, float params[]);

private:
    void initValues();
    void clearArr(QJsonArray &arr);

    QVector2D posToPoint(QJsonObject obj);
    QVector3D posTo3DPoint(QJsonObject obj);

    MissionWaypoints setMissionWaypoints(QJsonArray pointArray);
    QList<FlyZone> * setFlyZones(QJsonArray flyZoneArray);
    QList<QVector2D> * setPoints(QJsonArray pointArray);
    QList<QVector3D> * set3DPoints(QJsonArray pointArray);
};

#endif // MISSION_H
