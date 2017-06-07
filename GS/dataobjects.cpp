#include "dataobjects.h"

TelemetryData::TelemetryData() {

}

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

TelemetryData::~TelemetryData(){

}
