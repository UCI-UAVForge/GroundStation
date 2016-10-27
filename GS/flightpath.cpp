#include "flightpath.h"
#include <QVector>
#include <iostream>

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

    while (!waypointActions.empty()){
        double earliestTime = std::numeric_limits<double>::infinity();
        TimedAction* earliestAction;
        for(int i = 0; i < waypointActions.length(); i++){
            TimedAction* currentAction = waypointActions.at(i);
            if(currentAction->second < earliestTime){
                earliestTime = currentAction->second;
                earliestAction = currentAction;
            }
        }
        waypointActions.removeOne(earliestAction);
        rtnList->append(earliestAction->first->GetWaypoint());
    }

    return rtnList;
}
