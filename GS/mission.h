#ifndef MISSION_H
#define MISSION_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QMap>
#include "actionpacket.h"
#include "telemetrypacket.h"

class Mission {
public:
    Mission();
    Mission(QList<Protocol::Waypoint> flightPath);

    ~Mission();

    /** @brief Extracts data from an input Packet and stores the values in
     * the values field.
     *  @param telemPacket A pointer to the packet that will be read.
     *  @date April 8, 2016
     */
    void addPacket(Protocol::TelemetryPacket telemPacket);

    /**
     * @brief addWaypoint is used to build up the flightpath for this mission.
     * Waypoints should be added in the order they will be flown in.
     * @param lat The latitude in degrees associated with the new waypoint
     * @param lng The longitude in degrees associated with the new waypoint
     * @param alt The altitude in meters associated with the new waypoint
     * @todo Jordan - Move this elsewhere (FlightPath class)
     */
    //void addWaypoint(double lat, double lng, double alt);

    QVector<double> *getValuesForID(int id);
    QVector<double> *getValuesForIndex(int index);
    double getValueForIndexAndID(int index,int id);

private:
    //** @brief A Dictionary of metrics recorded. Each entry is a list of values */
    QVector<QVector<double>* > values;
    //QList<QPair<std::string,double> > values;
    //QList<Protocol::Packet*> networkStream;
    //QList<Waypoint*> flightPlan;

};

#endif // MISSION_H
