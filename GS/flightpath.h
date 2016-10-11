#ifndef FLIGHTPATH_H
#define FLIGHTPATH_H

#include <QList>
#include <QPair>
#include "ActionPacket.h"

class TimedAction;

class FlightPath: public QList<TimedAction*>{
public:
    FlightPath();
    ~FlightPath();

    void addCmdAction(Protocol::ActionType, double delay);
    void addNavAction(Protocol::Waypoint, double delay);

    QList<Protocol::Waypoint>* getOrderedWaypoints();
private:
};


class TimedAction: public QPair<Protocol::ActionPacket*, double>{
private:
    bool holdsAction;
    bool holdsWaypoint;
public:
    TimedAction(Protocol::ActionType action, double delay){
        Protocol::ActionPacket *ap = new Protocol::ActionPacket();
        ap->SetAction(action);
        first = ap;
        second = delay;
        holdsAction = true;
        holdsWaypoint = false;
    }

    TimedAction(Protocol::Waypoint wp, double delay){
        Protocol::ActionPacket *ap = new Protocol::ActionPacket();
        ap->SetWaypoint(wp);
        ap->SetAction(Protocol::ActionType::AddWaypoint);
        first = ap;
        second = delay;
        holdsAction = false;
        holdsWaypoint = true;
    }

    bool hasWaypoint(){
        return holdsWaypoint;
    }

    bool hasAction(){
        return holdsAction;
    }
};
#endif // FLIGHTPATH_H
