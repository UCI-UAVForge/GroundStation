#ifndef GROUNDSTATION_H
#define GROUNDSTATION_H

#include <QObject>
#include <QPushButton>
#include <QUdpSocket>

#include <QTimer>

#include "Messagebox.h"

#include "packet.h"
#include "ackpacket.h"
#include "actionpacket.h"
#include "infopacket.h"
#include "telemetrypacket.h"

class GroundStation : public QObject
{
    Q_OBJECT
    

    /* Alvin Truong added on 16-1-27*/
    const static int PACKET_LENGTH = 1000;

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
    void sendAllActionPackets(std::vector<Protocol::ActionPacket> packets);
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
    void altitude(u_int8_t* storage, int len) const;

private slots:
       void sendDatagram();
private:
       QUdpSocket udpSocket;
       QTimer timer;

signals:

public slots:
};

#endif // GROUNDSTATION_H
