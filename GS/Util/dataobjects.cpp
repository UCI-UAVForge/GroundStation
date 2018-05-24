#include "dataobjects.h"

TelemetryData::TelemetryData() {
    time = 0;
    heading = 0;
    alt = 0;
    lat = 0;
    lng = 0;
    alt = 0;
    pitch = 0;
    roll = 0;
    yaw = 0;
    xvel = 0;
    yvel = 0;
    zvel = 0;
    xaccel = 0;
    yaccel = 0;
    zaccel = 0;
}

TelemetryData::~TelemetryData(){

}



WaypointData::WaypointData() {
    wait = 0;
    heading = 0;
    lat = 0;
    lng = 0;
    alt = 0;
    speed = 0;

}

WaypointData::~WaypointData() {

}
