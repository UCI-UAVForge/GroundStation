#ifndef GROUNDSTATION_H
#define GROUNDSTATION_H

#include <QObject>
#include <QPushButton>
#include <QUdpSocket>

#include <QTimer>

//#include "Messagebox.h"

#include "packet.h"
#include "ackpacket.h"
#include "actionpacket.h"
#include "infopacket.h"
#include "telemetrypacket.h"

#include <queue>

/**
 * Protocol
 *
 * Start
 * ----------------------------------------------------------------
 * 1) After connection, GS sends Action(request):info packet
 * 2) UAV responds with Info Packet
 *
 *
 * Sending UAV on its path
 * ----------------------------------------------------------------
 * - GS will send numbered waypoint packets to program UAV route
 *      - Each waypoint packet NEEDS to receive an ACK
 *  - When ready, GS sends Action(start)
 *      - An ack should be expected
 *
 *
 * Rest of the time
 * ----------------------------------------------------------------
 * - Receives telemetry packet every 200ms.
 * - UAV will respond with a waypoint packet once it reaches wapyoint.
 *      - GS needs to send an ACK Packet
 * - GS can stop UAV with Action(stop)
 * - GS can shutdown with Action(shutdown)
 */
 
class GroundStation : public QObject
{
    Q_OBJECT
    

    /* Alvin Truong added on 16-1-27*/
    const static int PACKET_LENGTH = 1000;
    const static int GS_PORT_NUM = 20715;
    const static int UAV_PORT_NUM = 27015;
    static int NUM_RECV_PACKETS;

public:
    GroundStation(QWidget *parent = 0);
    /**
     * \brief   Member function takes a vector of packets and sends them all to the uav through UDP.
     * \param   packets represents a vector of action packets.
     *
     * \author  Alvin Truong
     * \date    16-1-27
     *
     **/
    void sendAllPackets(std::queue<Protocol::Packet*> packets);
    void sendAllPackets(std::vector<Protocol::Packet*> packets);
    /**
     * \brief   Function takes a single packet or a child of packet and sends it through UDP.
     * \param   packet represents a single packet or child of packet.
     *
     * \author  Alvin Truong
     * \date    16-1-27
     *
     **/
    void sendAPacket(Protocol::Packet* packet);
//    double altitude() const;
    //void altitude(u_int8_t* storage, int len) const;

     /* Created Functions to print out information about packets
     * parameters(Packet type packet)
     * return void
     * created by: Daniel Ortega
     *
     **/
    void print_ack_packet(Protocol::AckPacket& packet);
    void print_action_packet(Protocol::ActionPacket& packet);
    void print_info_packet(Protocol::InfoPacket& packet);
    void print_telemetry_packet(Protocol::TelemetryPacket& packet);

private slots:
    //void sendDatagram();
    void processPendingDatagrams();
        
private:
       QUdpSocket sendUdpSocket;
       QUdpSocket recvUdpSocket;
       QTimer timer;

signals:

public slots:
};

#endif // GROUNDSTATION_H
