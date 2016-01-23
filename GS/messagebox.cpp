#ifndef UAV_MESSAGEBOX_CPP
#define UAV_MESSAGEBOX_CPP

#include "messagebox.h"

messagebox::messagebox()
{
    std::cout << "Message box succesfully created" << std::endl;
   timer = QTime();
   timer.start();
    std::cout << "Timer started at " << timer.currentTime << std::endl;
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
    actionPackets.back().SetWaypoint(wp);
}

void messagebox::load_info_packet(std::string other){
    addInfoPacket(Protocol::InfoPacket());
    infoPackets.back().SetOther(other);
}

void messagebox::load_telem_packet(double lat, double lon){
    telemetryPackets.push_back(Protocol::TelemetryPacket());
    telemetryPackets.back().SetLocation(lat, lon);
}

void messagebox::load_telem_packet(float x, float y, float z, float p, float r, float yaw, double lat, double lon, float alt, float heading){
    addTelemetryPacket(Protocol::TelemetryPacket());
    telemetryPackets.back().SetVelocity(x, y, z);
    telemetryPackets.back().SetOrientation(p, r, yaw);
    telemetryPackets.back().SetLocation(lat, lon, alt);
    telemetryPackets.back().SetHeading(heading);
}

void messagebox::recieve_initial_info(Protocol::InfoPacket intip){
    uint32_t initial_timestamp = intip.get_timestamp();
    timestamp_offset = initial_timestamp - ((uint32_t)timer.elapsed());
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

uint32_t messagebox::gs_to_uav_timestamp(){
    return ((uint32_t)timer.elapsed()) - timestamp_offset;
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
