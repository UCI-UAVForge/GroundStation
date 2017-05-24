#ifndef FLIGHTPATH_H
#define FLIGHTPATH_H

#include <QList>
#include <QPair>
#include <QString>
#include "actionpacket.h"

class TimedAction;

class FlightPath: public QList<TimedAction*>{
public:

    /**
     * @brief FlightPath - default constructor
     */
    FlightPath();

    /**
     * @brief FlightPath - Creates a new FlightPath using the
     * data stored in the target file. Serves as a load function.
     * @param filename - the name of the target file
     */
    FlightPath(QString filename);

    /**
     * @brief FlightPath - Default destructor
     */
    ~FlightPath();

    /**
     * @brief addCmdAction Adds a new Command-type Action to this FlightPath
     * @param type - the type of Action this new packet contains
     * @param delay - the queue position of this Action - small numbers send first
     */
    void addCmdAction(Protocol::ActionType type, double delay);

    /**
     * @brief addNavAction Adds a new Navigation-type Action to this FlightPath
     * @param wp - the destination Waypoint for this navigation action
     * @param delay - the queue position of this Action - small numbers send first
     */
    void addNavAction(Protocol::Waypoint wp, double delay);

    /**
     * @brief save Writes this FlightPath's data out to a target file
     * @param filename the name of the target file
     * @return true if the write was successful, false otherwise
     */
    bool save(QString filename);

    /**
     * @brief getOrderedWaypoints Returns a list of all Waypoint objects in
     * ascending order of delay (queue postion).
     * @return A pointer to the sorted QList containing all the Waypoints
     */
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
