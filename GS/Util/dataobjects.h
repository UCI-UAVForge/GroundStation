#ifndef DATAOBJECTS_H
#define DATAOBJECTS_H



class TelemetryData {
private:

public:
    unsigned long time;
    double heading, lat, lng, alt, pitch, roll, yaw, xaccel, yaccel, zaccel, xvel, yvel, zvel;

    TelemetryData();

    ~TelemetryData();
};

class WaypointData{
private:
public:
    unsigned long wait;
    double heading, lat, lng, alt, speed;
    WaypointData();

    ~WaypointData();

};

#endif // DATAOBJECTS_H
