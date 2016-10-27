//Created by Nathan Brannon 11/20/15
//Used to handle packets between windows of ground station
//TODO:
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


class messagebox {
public:
    friend class DigitalClock;
    messagebox();
    void load_ack_packet(uint8_t* buffer, size_t len);
    void load_action_packet(Protocol::ActionType atype, double lat, double lon, float alt, float spd);
    void load_action_packet(double lat, double lon, float alt, float spd);
    void load_info_packet(std::string other);
    void load_telem_packet(double lat, double lon);
    void load_telem_packet(float x, float y, float z, float p, float r, float yaw, double lat, double lon, float alt, float heading);

    /**
      * @brief Fetches the packets from table and stores them into the outbox where they will sent back
      * @param <type> double,double,float,float -> sets the waypoint
      *
      * @author Kevin Phan
      * @date 2016-2-05
      */
    void load_outAction_packets(double lat,double lon,float alt, float spd);
    void addOutActionPacket(const Protocol::ActionPacket &actionPacket);

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
     * \brief returns the packets from the sending side of messagebox
     *
     * \author Kevin Phan
     * \date 2016/1/29
    **/

    std::vector<Protocol::AckPacket> get_out_ack_packets();
    std::vector<Protocol::ActionPacket> get_out_action_packets();
    std::vector<Protocol::InfoPacket> get_out_info_packets();
    std::vector<Protocol::TelemetryPacket> get_out_telem_packets();

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
    QTime timer; //Qtime that starts when message box is created

private:


    /**
     * @brief Takes timestamp form timer and subtracts the offset determined form UAV timestamp
     * @return <type>uint32_t -> Timestamp that will fit with the UAV time
     *
     * @Author Nathan Brannon
     * @date 2016-1-22
     */
    uint32_t gs_to_uav_timestamp();
    std::vector<Protocol::AckPacket> ackPackets_incoming;
    std::vector<Protocol::ActionPacket> actionPackets_incoming;
    std::vector<Protocol::InfoPacket> infoPackets_incoming;
    std::vector<Protocol::TelemetryPacket> telemetryPackets_incoming;

    std::vector<Protocol::Packet *> packets_outgoing;

    /**
     * @brief Initialization of vectors that will store outgoing packets which will be sent to the server
     *
     * @author Kevin Phan
     * @date 2016-2-05
     */
    std::vector<Protocol::AckPacket> outAckPackets;
    std::vector<Protocol::ActionPacket> outActionPackets;
    std::vector<Protocol::InfoPacket> outInfoPackets;
    std::vector<Protocol::TelemetryPacket> outTelemPackets;
    
    uint32_t timestamp_offset; //Offset between GS timer and the UAV timer

//signals:

public slots:
    void recieve_packet(Protocol::Packet *packet);
};

#endif // UAV_MESSAGEBOX_H
