#include "missionpath.h"

MissionPath::MissionPath() {
}

MissionPath::MissionPath(QList<Waypt> waypoints, int currentWaypoint) {
    this->waypoints = waypoints;
    this->currentWaypoint = currentWaypoint;
}

MissionPath::addWaypoint(Waypt waypoint){
   waypoints->append(waypoint);
}

MissionPath::addWaypoint(Waypt waypoint, int order) {
    waypoints->insert(order, waypoint);
}

MissionPath::removeWaypoint(int order) {
   waypoints->removeAt(order);
}

MissionPath::setCurrent(int i) {
    if (waypoints->size() > i) {
        currentWaypoint = i;
    }
}
