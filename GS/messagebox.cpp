#ifndef UAV_MESSAGEBOX_CPP
#define UAV_MESSAGEBOX_CPP

#include "messagebox.h"

messagebox::messagebox()
    :timestamp_init(0)
{

}

void messagebox::fetch_from_table(QList<std::string> tableList){

}

void messagebox::load_ack_packet(uint8_t* buffer, size_t len){
    addAckPacket(Protocol::AckPacket(buffer, len));
}

void messagebox::loack_action_packet(Protocol::ActionType at, double lat, double lon, float alt, float spd){
    Protocol::Waypoint wp;
    wp.lat = lat;
    wp.lon = lon;
    wp.alt = alt;
    wp.speed = spd;
    addActionPacket(Protocol::ActionPacket());
    actionPackets.back().SetAction(at);
    actionPackets.back().SetWaypoint(wp);
}

void messagebox::load_info_packet(std::string other){
    addInfoPacket(Protocol::InfoPacket());
    infoPackets.back().SetOther(other);
}

void messagebox::load_telem_packet(float x, float y, float z, float p, float r, float yaw, double lat, double lon, float alt, float heading){
    addTelemetryPacket(Protocol::TelemetryPacket());
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


/// \see messagebox.h for more info
void messagebox::addAckPacket(const Protocol::AckPacket& ackPacket)
{
    ackPackets.push_back(ackPacket);
}


/// \see messagebox.h for more info
void messagebox::addActionPacket(const Protocol::ActionPacket& actionPacket)
{
    actionPackets.push_back(actionPacket);
}


/// \see messagebox.h for more info
void messagebox::addTelemetryPacket(const Protocol::TelemetryPacket& telemPacket)
{
    telemetryPackets.push_back(telemPacket);
}


/// \see messagebox.h for more info
void messagebox::addInfoPacket(const Protocol::InfoPacket& infoPacket)
{
    infoPackets.push_back(infoPacket);
}
#endif // UAV_MESSAGEBOX_CPP
