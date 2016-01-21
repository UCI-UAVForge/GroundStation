//Created by Nathan Brannon 11/20/15
//Used to handle packets between windows of ground station
//TODO:
//      Create alternate constructor with time_t as param to allow for inital time when mesage box was
//          created to help replace the millis() function in ack_packet
//      Integrate with networked end
//      Write function to intake table from mapplanning and create vector of telem/action packets
//          rather than load 1 by 1 externally


//Message box currently only functions as a way to move test packets around the ground station

#ifndef UAV_MESSAGEBOX_H
#define UAV_MESSAGEBOX_H


#include <iostream>
#include <vector>
#include <QApplication>
#include <Qpair>
#include <QList>


#include "qcomboboxdelegate.h"
#include "ackpacket.h"
#include "actionpacket.h"
#include "infopacket.h"
#include "telemetrypacket.h"

class messagebox
{
public:
    messagebox();
    void fetch_from_table(QList<QString> tableList);
    void load_ack_packet(uint8_t* buffer, size_t len);
    void load_action_packet(Protocol::ActionType at, double lat, double lon, float alt, float spd);
    void load_info_packet(std::string other);
    void load_telem_packet(float x, float y, float z, float p, float r, float yaw, double lat, double lon, float alt, float heading);
    std::vector<Protocol::AckPacket> get_ack_packets();
    std::vector<Protocol::ActionPacket> get_action_packets();
    std::vector<Protocol::InfoPacket> get_info_packets();
    std::vector<Protocol::TelemetryPacket> get_telem_packets();

private:
    void set_initial_timestamp();
    std::vector<Protocol::AckPacket> ackPackets;
    std::vector<Protocol::ActionPacket> actionPackets;
    std::vector<Protocol::InfoPacket> infoPackets;
    std::vector<Protocol::TelemetryPacket> telemetryPackets;
    int timestamp_init;

//signals:

//public slots:
};

#endif // UAV_MESSAGEBOX_H
