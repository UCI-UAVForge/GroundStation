#ifndef DATAOBJECTS_H
#define DATAOBJECTS_H

#include "telemetrypacket.h"

class TelemetryData {
private:

public:
    unsigned long time;
    double heading, lat, lng, alt, pitch, roll, yaw, xaccel, yaccel, zaccel, xvel, yvel, zvel;

    TelemetryData(Protocol::TelemetryPacket *packet);
    TelemetryData();

    ~TelemetryData();
};

#endif // DATAOBJECTS_H
