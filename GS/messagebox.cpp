#ifndef UAV_MESSAGEBOX_CPP
#define UAV_MESSAGEBOX_CPP

#include "messagebox.h"

messagebox::messagebox()
{
    std::cout << "Message box succesfully created" << std::endl;
   timer = QTime();
   timer.start();
    std::cout << "Timer started at " << timer.currentTime().msec()<< std::endl;
}
/* Uses code from MapExecution::getDoublePairs
takes input from MapPlanning::getTableAsStrings()
-Aaron Ko 1/19/2016 */
void messagebox::fetch_from_table(QList<QString> tableList){
    for(QString string : tableList){
        QList<QString> comps = string.split(",");
        double lat = comps[3].toDouble();
        double lon = comps[1].toDouble();
        if(comps[2] == "W") {
            lon *= -1.0;
        }
        if(comps[4] == "S") {
            lat *= -1.0;
        }
        load_action_packet(lat, lon, 0.0, 0.0);
        load_outAction_packets(lat,lon,0.0,0.0);
    }
}

void messagebox::load_ack_packet(uint8_t* buffer, size_t len){
    addAckPacket(Protocol::AckPacket(buffer, len));
}

void messagebox::load_action_packet(double lat, double lon, float alt, float spd){
    Protocol::Waypoint wp;
    wp.lat = lat;
    wp.lon = lon;
    wp.alt = alt;
    wp.speed = spd;
    addActionPacket(Protocol::ActionPacket());
//    actionPackets.back().SetAction(at);
    actionPackets_incoming.back().SetWaypoint(wp);
}

void messagebox::load_action_packet(Protocol::ActionType atype, double lat, double lon, float alt, float spd){
    Protocol::Waypoint wp;
    wp.lat = lat;
    wp.lon = lon;
    wp.alt = alt;
    wp.speed = spd;
    addActionPacket(Protocol::ActionPacket());
    actionPackets_incoming.back().SetAction(atype);
    actionPackets_incoming.back().SetWaypoint(wp);

}

void messagebox::load_outAction_packets(double lat, double lon, float alt, float spd) {
    Protocol::Waypoint wp;
    wp.lat = lat;
    wp.lon = lon;
    wp.alt = alt;
    wp.speed = spd;
    addOutActionPacket(Protocol::ActionPacket());
    outActionPackets.back().SetWaypoint(wp);
}

void messagebox::load_info_packet(std::string other){
    addInfoPacket(Protocol::InfoPacket());
    infoPackets_incoming.back().SetOther(other);
}

void messagebox::load_telem_packet(double lat, double lon){

    telemetryPackets_incoming.push_back(Protocol::TelemetryPacket());
    telemetryPackets_incoming.back().SetLocation(lat, lon);
}

void messagebox::load_telem_packet(float x, float y, float z, float p, float r, float yaw, double lat, double lon, float alt, float heading){
    addTelemetryPacket(Protocol::TelemetryPacket());
    telemetryPackets_incoming.back().SetVelocity(x, y, z);
    telemetryPackets_incoming.back().SetOrientation(p, r, yaw);
    telemetryPackets_incoming.back().SetLocation(lat, lon, alt);
    telemetryPackets_incoming.back().SetHeading(heading);
}

void messagebox::recieve_initial_info(Protocol::InfoPacket intip){
    uint32_t initial_timestamp = intip.get_timestamp();
    timestamp_offset = initial_timestamp - ((uint32_t)timer.elapsed());
}

std::vector<Protocol::AckPacket> messagebox::get_ack_packets(){
    return ackPackets_incoming;
}

std::vector<Protocol::ActionPacket> messagebox::get_action_packets(){
    return actionPackets_incoming;
}

std::vector<Protocol::InfoPacket> messagebox::get_info_packets(){
    return infoPackets_incoming;
}

std::vector<Protocol::TelemetryPacket> messagebox::get_telem_packets(){
    return telemetryPackets_incoming;
}

std::vector<Protocol::AckPacket> messagebox::get_out_ack_packets(){
    return outAckPackets;
}

std::vector<Protocol::ActionPacket> messagebox::get_out_action_packets(){
    return outActionPackets;
}

std::vector<Protocol::InfoPacket> messagebox::get_out_info_packets(){
    return outInfoPackets;
}

std::vector<Protocol::TelemetryPacket> messagebox::get_out_telem_packets(){
    return outTelemPackets;
}

uint32_t messagebox::gs_to_uav_timestamp(){
    return ((uint32_t)timer.elapsed()) - timestamp_offset;
}


/// \see messagebox.h for more info
void messagebox::addAckPacket(const Protocol::AckPacket& ackPacket)
{
    ackPackets_incoming.push_back(ackPacket);
}


/// \see messagebox.h for more info
void messagebox::addActionPacket(const Protocol::ActionPacket& actionPacket)
{
    actionPackets_incoming.push_back(actionPacket);
}

void messagebox::addOutActionPacket(const Protocol::ActionPacket &actionPacket) {
    outActionPackets.push_back(actionPacket);
}

/// \see messagebox.h for more info
void messagebox::addTelemetryPacket(const Protocol::TelemetryPacket& telemPacket)
{
    telemetryPackets_incoming.push_back(telemPacket);
}


/// \see messagebox.h for more info
void messagebox::addInfoPacket(const Protocol::InfoPacket& infoPacket)
{
    infoPackets_incoming.push_back(infoPacket);
}
#endif // UAV_MESSAGEBOX_CPP
