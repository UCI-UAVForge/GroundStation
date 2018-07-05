#ifndef MISSIONPATH_H
#define MISSIONPATH_H

#include "waypt.h"
#include <QList>
#include "waypoint.h"

class MissionPath {

public:
    MissionPath();
    MissionPath(QList<Waypt> waypoints, int currentWaypoint);
    int currentWaypoint;
    QList<Waypt> waypoints;

    void addWaypoint(Waypt waypoint);
    void addWaypoint(Waypt waypoint, int order);
    void removeWaypoint(int order);
    void setCurrent(int i);
    QVector<Waypoint::WP> generateWaypoints(uint16_t startingSeq);
    QList<QVector3D>* toList();
    QJsonValue toQJsonValue();
    void setDefaultLanding(QList<QVector3D> landingPath, QVector2D landingPoint, float abortAlt);
    uint16_t getSeq(uint16_t cmdSeq);
    uint16_t getIndex(uint16_t seq);
};

#endif // MISSIONPATH_H
