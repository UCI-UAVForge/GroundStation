#include "groundstation.h"

#include <QDateTime>


GroundStation::GroundStation(QWidget *parent)
//    : QPushButton(tr("Quit"), parent)
{
//    connect(&timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

//    timer.start(2 * 1000);
    //sendDatagram();
    udpSocket.bind(GS_PORT_NUM);

    connect(&udpSocket, SIGNAL(readyRead()),
                this, SLOT(processPendingDatagrams()));

    QTextStream(stdout) << "Listening for packets.." << endl;


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
    udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, GS.UAV_PORT_NUM);
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

void GroundStation::processPendingDatagrams()
{

    while(udpSocket.hasPendingDatagrams())
    {
        QTextStream(stdout) << "Processing started" << endl;
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        
        // Read from the udpSocket while there is a datagram and store into datagram.
        udpSocket.readDatagram(datagram.data(), datagram.size());


        //do {
            //datagram.resize(udpSocket.pendingDatagramSize());
            //udpSocket.readDatagram(datagram.data(), datagram.size());
        //} while (udpSocket.hasPendingDatagrams());

        //QDataStream in(&datagram, QIODevice::ReadOnly);
        //in.setVersion(QDataStream::Qt_4_3);
        
        
       // Convert Datagram into proper packet.
        Protocol::Packet* packet = Protocol::Packet::Parse((u_int8_t*)datagram.data(), 1000);
        Protocol::Packet::Type packet_type = packet.getPacketType();

        // Depending on the type call the proper method to extract packet's information and print
        if(packet != nullptr)
        {
            QTextStream(stdout) << "Packet number " << UAV.NUM_RECV_PACKETS + 1 << endl;
            switch(packet_type)
            {
                case Protocol::PacketType::ActionPacket:
                    print_action_packet(*packet);
                    break;
                case Protocol::PacketType::AckPacket:
                    print_ack_packet(*packet);
                    break;
                case Protocol::PacketType::InfoPacket:
                    print_info_packet(*packet);
                    break;
                case Protocol::PacketType::TelemetryPacket:
                    print_telemetry_packet(*packet);
                    break;
                default:
            }

            QTextStream(stdout) << endl;
            ++UAV.NUM_RECV_PACKETS;
        }
        else
        {
            QTextStream(stdout) << "ERROR: Packet is invalid" << endl;
        }
    }
}
