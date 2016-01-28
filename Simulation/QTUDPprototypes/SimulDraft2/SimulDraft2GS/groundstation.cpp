#include "groundstation.h"

#include <QDateTime>


GroundStation::GroundStation(QWidget *parent)
//    : QPushButton(tr("Quit"), parent)
{
//    connect(&timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

//    timer.start(2 * 1000);
    //sendDatagram();
}

void GroundStation::sendAllActionPackets(std::vector<Protocol::Packet*> packets)
{
    //QTextStream(stdout) << "The size of the vector is " << packets.size() << endl;
    for(auto i = packets.begin(); i != packets.end(); ++i)
    {
        sendAPacket(&*i);
    }

}


void GroundStation::sendAPacket(Protocol::Packet* packet)
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    
    // Allocate storage for the packet in the for of u_int8_t
    u_int8_t storage[GroundStation::PACKET_LENGTH];
    
    // Convert the packet into bytes and store into storage
    packet->GetBytes(storage, GroundStation::PACKET_LENGTH);

    // Send bytes inside storage to out datastream
    for(int i =0; i < GroundStation::PACKET_LENGTH; i++)
    {
        out << storage[i];
    }

    // Send datagram through UDP socket
    udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, 27015);
}


void GroundStation::sendDatagram()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    u_int8_t storage[1000];
    altitude(storage, 1000);
    for(int i =0; i < 1000; i++)
    {
        out << storage[i];
    }

    QTextStream(stdout) << storage;

    udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, 27015);
}

//double GroundStation::altitude() const
void GroundStation::altitude(u_int8_t* storage, int len) const
{
    Protocol::ActionPacket testActionPacket;

    testActionPacket.SetAction(Protocol::ActionType::Shutdown);
    Protocol::Waypoint waypoint;
    waypoint.lat = 90;
    waypoint.lon = 45;
    waypoint.alt = 100;
    waypoint.speed = 250;
    testActionPacket.SetWaypoint(waypoint);


    testActionPacket.GetBytes(storage, len);

//    return 4;
}

