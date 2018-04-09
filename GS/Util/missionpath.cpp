#include "missionpath.h"

MissionPath::MissionPath() {
}

MissionPath::MissionPath(QList<Waypt> waypoints, int currentWaypoint) {
    this->waypoints = waypoints;
    this->currentWaypoint = currentWaypoint;
}

void MissionPath::addWaypoint(Waypt waypoint){
   waypoints.append(waypoint);
}

void MissionPath::addWaypoint(Waypt waypoint, int order) {
    waypoints.insert(order, waypoint);
}

void MissionPath::removeWaypoint(int order) {
   waypoints.removeAt(order);
}

void MissionPath::setCurrent(int i) {
    if (waypoints.size() > i) {
        currentWaypoint = i;
    }
}

uint16_t MissionPath::length() {
    waypoints.length();
}

QVector<Waypoint::WP> MissionPath::generateWaypoints(uint16_t startingSeq) {
    QVector<Waypoint::WP> path;
    uint16_t seq = startingSeq;
    for (int i = 0; i < waypoints.length(); i++) {
        path.append(waypoints[i].generateWP(seq++));
    }
}

QList<QVector3D>* MissionPath::toList() {
    QList<QVector3D> *list = new QList<QVector3D>();
    for (int i = 0; i < waypoints.length(); i++) {
        list->append(waypoints.at(i).coords);
    }
    return list;
}
