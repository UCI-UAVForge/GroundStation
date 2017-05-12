#include "dataobjects.h"

TelemetryData::TelemetryData(Protocol::TelemetryPacket *packet){
    time = packet->get_timestamp();
    float temp1,temp2,temp3;
    packet->GetHeading(&temp1);
    heading = temp1;
    packet->GetLocation(&lat,&lng,&temp3);
    alt = temp3;
    packet->GetOrientation(&temp1,&temp2,&temp3);
    pitch = temp1;
    roll = temp2;
    yaw = temp3;
    packet->GetVelocity(&temp1,&temp2,&temp3);
    xvel = temp1;
    yvel = temp2;
    zvel = temp3;

    xaccel = 0;
    yaccel = 0;
    zaccel = 0;
}

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

WaypointData::WaypointData(Protocol::Waypoint wp) {
    wait = -1;
    heading = -1;
    lat = wp.lat;
    lng = wp.lon;
    alt = wp.alt;
    speed = wp.speed;
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
