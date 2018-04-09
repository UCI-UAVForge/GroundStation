#ifndef MISSIONPATH_H
#define MISSIONPATH_H

#include "waypt.h";
#include <QList>;
#include "waypoint.h";

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
    uint16_t length();
    QVector<Waypoint::WP> generateWaypoints(uint16_t startingSeq);
    QList<QVector3D>* toList();
};

#endif // MISSIONPATH_H
