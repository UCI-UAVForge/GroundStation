#ifndef UAV_MESSAGEBOX_CPP
#define UAV_MESSAGEBOX_CPP

#include "messagebox.h"

messagebox::messagebox()
    :timestamp_init(0)
{

}

void messagebox::fetch_from_table(QList<QString> tableList){

}

void messagebox::load_ack_packet(uint8_t* buffer, size_t len){
    ackPackets.push_back(Protocol::AckPacket(buffer, len));
}

void messagebox::load_action_packet(Protocol::ActionType at, double lat, double lon, float alt, float spd){
    Protocol::Waypoint wp;
    wp.lat = lat;
    wp.lon = lon;
    wp.alt = alt;
    wp.speed = spd;
    actionPackets.push_back(Protocol::ActionPacket());
    actionPackets.back().SetAction(at);
    actionPackets.back().SetWaypoint(wp);
}

void messagebox::load_info_packet(std::string other){
    infoPackets.push_back(Protocol::InfoPacket());
    infoPackets.back().SetOther(other);
}

void messagebox::load_telem_packet(float x, float y, float z, float p, float r, float yaw, double lat, double lon, float alt, float heading){
    telemetryPackets.push_back(Protocol::TelemetryPacket());
    telemetryPackets.back().SetVelocity(x, y, z);
    telemetryPackets.back().SetOrientation(p, r, yaw);
    telemetryPackets.back().SetLocation(lat, lon, alt);
    telemetryPackets.back().SetHeading(heading);
}

std::vector<Protocol::AckPacket> messagebox::get_ack_packets(){
    return ackPackets;
}

std::vector<Protocol::ActionPacket> messagebox::get_action_packets(){
    return actionPackets;
}

std::vector<Protocol::InfoPacket> messagebox::get_info_packets(){
    return infoPackets;
}

std::vector<Protocol::TelemetryPacket> messagebox::get_telem_packets(){
    return telemetryPackets;
}

#endif // UAV_MESSAGEBOX_CPP
