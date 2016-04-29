#include "flightpath.h"
#include <QVector>

FlightPath::FlightPath()  {

}

FlightPath::~FlightPath() {

}

void FlightPath::addCmdAction(Protocol::ActionType action, double delay){
    this->append(new TimedAction(action,delay));
}

void FlightPath::addNavAction(Protocol::Waypoint wp, double delay){
    this->append(new TimedAction(wp,delay));
}

QList<Protocol::Waypoint>* FlightPath::getOrderedWaypoints(){
    QList<Protocol::Waypoint> *rtnList = new QList<Protocol::Waypoint>;
    QList<TimedAction*> waypointActions;

    for (TimedAction* action : *this) {
        if(action->hasWaypoint()){
            waypointActions.append(action);
        }
    }

    //work with the lists here to filter out all non waypoint packets
    //and get the rest in order -Jordan

    return rtnList;
}
