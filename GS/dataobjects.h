#ifndef DATAOBJECTS_H
#define DATAOBJECTS_H

#include "telemetrypacket.h"
#include "actionpacket.h"

class TelemetryData {
private:

public:
    unsigned long time;
    double heading, lat, lng, alt, pitch, roll, yaw, xaccel, yaccel, zaccel, xvel, yvel, zvel;

    TelemetryData(Protocol::TelemetryPacket *packet);
    TelemetryData();

    ~TelemetryData();
};

class WaypointData{
private:
public:
    unsigned long wait;
    double heading, lat, lng, alt, speed;

    WaypointData(Protocol::Waypoint wp);
    WaypointData();

    ~WaypointData();

};

#endif // DATAOBJECTS_H
