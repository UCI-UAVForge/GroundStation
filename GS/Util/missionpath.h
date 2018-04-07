#ifndef MISSIONPATH_H
#define MISSIONPATH_H

#include "waypt.h";
#include <QList>;

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
};

#endif // MISSIONPATH_H
