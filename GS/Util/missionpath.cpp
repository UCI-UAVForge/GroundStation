#include "missionpath.h"
#include <QDebug>

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

QVector<Waypoint::WP> MissionPath::generateWaypoints(uint16_t startingSeq) {
    QVector<Waypoint::WP> path;
    uint16_t seq = startingSeq;
    for (int i = 0; i < waypoints.length(); i++) {
        path.append(waypoints[i].generateWP(seq++));
        if (waypoints.at(i).changeSpeed && waypoints.at(i).action == 16)
            path.append(waypoints[i].setSpeed(seq++));
    }
    return path;
}

QList<QVector3D>* MissionPath::toList() {
    QList<QVector3D> *list = new QList<QVector3D>();
    for (int i = 0; i < waypoints.length(); i++) {
        list->append(waypoints.at(i).coords);
    }
    return list;
}

void MissionPath::setDefaultLanding(QList<QVector3D> landingPath, QVector2D landingPoint, float abortAlt) {
    waypoints.clear();
    foreach(QVector3D coords, landingPath) {
        waypoints.append(Waypt(coords));
    }
    Waypt land;
    land.setDefaultLanding(landingPoint, abortAlt);
    waypoints.append(land);
}

uint16_t MissionPath::getSeq(uint16_t cmdSeq) {
    uint16_t seq = cmdSeq;
    for (int i = 0; i < cmdSeq - 1; i++) {
        if (waypoints.at(i).changeSpeed) {
            seq++;
        }
    }
    return seq;
}

uint16_t MissionPath::getIndex(uint16_t seq) {
    uint16_t index = seq;
    for (int i = 0; i < waypoints.length(); i++) {
        if (waypoints.at(i).changeSpeed) {
            index--;
        }
    }
    return index;
}
