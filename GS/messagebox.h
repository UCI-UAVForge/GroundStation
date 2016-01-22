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
#include <QPair>
#include <QList>
#include <QTime>
#include "stdint.h"


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
    void load_telem_packet(double lat, double lon);
    void load_telem_packet(float x, float y, float z, float p, float r, float yaw, double lat, double lon, float alt, float heading);

    /**
     * @brief Takes initial info packet and sets timestamp based on it
     * @param <type>InfoPacket -> The inital infopacket sent from UAV
     *
     * @author Nathan Brannon
     * @date 2016-1-22
     */
    void recieve_initial_info(Protocol::InfoPacket intip);

    std::vector<Protocol::AckPacket> get_ack_packets();
    std::vector<Protocol::ActionPacket> get_action_packets();
    std::vector<Protocol::InfoPacket> get_info_packets();
    std::vector<Protocol::TelemetryPacket> get_telem_packets();

    /**
      * \brief Adds fully formed or empty packet into the proper packet container in messagebox
      * \param <type>Packet	-> A formed or empty Packets
      *
      * \author Alvin Truong
      * \date 2016-1-20
    **/
    void addAckPacket(const Protocol::AckPacket& ackPacket);
    void addActionPacket(const Protocol::ActionPacket& actionPacket);
    void addTelemetryPacket(const Protocol::TelemetryPacket& telemPacket);
    void addInfoPacket(const Protocol::InfoPacket& infoPacket);

private:
    QTime timer; //Qtime that starts when message box is created

    /**
     * @brief Takes timestamp form timer and subtracts the offset determined form UAV timestamp
     * @return <type>uint32_t -> Timestamp that will fit with the UAV time
     *
     * @Author Nathan Brannon
     * @date 2016-1-22
     */
    uint32_t gs_to_uav_timestamp();
    std::vector<Protocol::AckPacket> ackPackets;
    std::vector<Protocol::ActionPacket> actionPackets;
    std::vector<Protocol::InfoPacket> infoPackets;
    std::vector<Protocol::TelemetryPacket> telemetryPackets;
    uint32_t timestamp_offset; //Offset between GS timer and the UAV timer

//signals:

//public slots:
};

#endif // UAV_MESSAGEBOX_H
