#include "groundstation.h"

#include <QDateTime>


int GroundStation::NUM_RECV_PACKETS = 0;

GroundStation::GroundStation(QWidget *parent)
//    : QPushButton(tr("Quit"), parent)
{
//    connect(&timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

//    timer.start(2 * 1000);
    //sendDatagram();

    // Connect receiving udp socket to groundstation port
    recvUdpSocket.bind(GroundStation::GS_PORT_NUM);

    // Trigger processPendinDatagrams() when a datagram comes in
    connect(&recvUdpSocket, SIGNAL(readyRead()),
                this, SLOT(processPendingDatagrams()));

    QTextStream(stdout) << "Listening for packets.." << endl;


}

void GroundStation::sendAllPackets(std::vector<Protocol::Packet*> packets)
{
    //QTextStream(stdout) << "The size of the vector is " << packets.size() << endl;
    for(auto i = packets.begin(); i != packets.end(); ++i)
    {
        sendAPacket(*i);
    }

}

void GroundStation::sendAllPackets(std::queue<Protocol::Packet*> packets)
{
    //QTextStream(stdout) << "The size of the vector is " << packets.size() << endl;
    int size = packets.size();
    for(int i = 0; i < size; ++i)
    {
        sendAPacket(packets.front());
        packets.pop();
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
    size_t packet_size = packet->GetBytes(storage, GroundStation::PACKET_LENGTH);

    // Send bytes inside storage to out datastream
    for(size_t i =0; i < packet_size; i++)
    {
        out << storage[i];
    }

    // Send datagram through UDP socket
    sendUdpSocket.writeDatagram(datagram, QHostAddress::LocalHost, GroundStation::UAV_PORT_NUM);
//    sendUdpSocket.writeDatagram(datagram, QHostAddress("169.234.57.192"), GroundStation::UAV_PORT_NUM);
}

/*
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

    sendUdpSocket.writeDatagram(datagram, QHostAddress::LocalHost, 27015);
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
*/

void GroundStation::processPendingDatagrams()
{

    while(recvUdpSocket.hasPendingDatagrams())
    {
        QTextStream(stdout) << "Processing started" << endl;
        QByteArray datagram;
        datagram.resize(recvUdpSocket.pendingDatagramSize());
        
        // Read from the udpSocket while there is a datagram and store into datagram.
        recvUdpSocket.readDatagram(datagram.data(), datagram.size());


        //do {
            //datagram.resize(udpSocket.pendingDatagramSize());
            //udpSocket.readDatagram(datagram.data(), datagram.size());
        //} while (udpSocket.hasPendingDatagrams());

        //QDataStream in(&datagram, QIODevice::ReadOnly);
        //in.setVersion(QDataStream::Qt_4_3);
        
        // Validates check sum first and then convert Datagram into proper packet.
        Protocol::Packet* packet = Protocol::Packet::Parse((uint8_t*)datagram.data(), datagram.size());
        Protocol::PacketType packet_type = packet->get_type();

        // Depending on the type call the proper method to extract packet's information and print
        if(packet != nullptr)
        {
            QTextStream(stdout) << "Packet number " << GroundStation::NUM_RECV_PACKETS + 1 << endl;
            switch(packet_type)
            {
                case Protocol::PacketType::Action:
                    print_action_packet(*dynamic_cast<Protocol::ActionPacket*>(packet));
                    break;
                case Protocol::PacketType::Ack:
                    print_ack_packet(*dynamic_cast<Protocol::AckPacket*>(packet));
                    break;
                case Protocol::PacketType::Info:
                    print_info_packet(*dynamic_cast<Protocol::InfoPacket*>(packet));
                    break;
                case Protocol::PacketType::Telem:
                    print_telemetry_packet(*dynamic_cast<Protocol::TelemetryPacket*>(packet));
                    break;
                default:
                    break;
            }

            QTextStream(stdout) << ""<< endl;
            ++GroundStation::NUM_RECV_PACKETS;        }
        else
        {
            QTextStream(stdout) << "ERROR: Packet is invalid" << endl;
        }
    }
}

void GroundStation::print_telemetry_packet(Protocol::TelemetryPacket& packet)
{
    float   vx, vy, vz,
            pitch, roll, yaw,
            heading, alt;

    double  lat, lon;

    // Extract all information from telemetry packet into variables
    packet.GetVelocity(&vx, &vy, &vz);
    packet.GetOrientation(&pitch, &roll, &yaw);
    packet.GetLocation(&lat, &lon, &alt);
    packet.GetHeading(&heading);

    // Print out information
    QTextStream(stdout) << "Type: Telemetry Packet" << endl;
    QTextStream(stdout) << "Velocity x: "   << vx << endl
                        << "Velocity y: "   << vy << endl
                        << "Velocity z: "   << vz << endl;
    QTextStream(stdout) << "Pitch: "        << pitch << endl
                        << "Roll: "         << roll << endl
                        << "Yaw: "          << yaw << endl;
    QTextStream(stdout) << "Latitude: "     << lat << endl
                        << "Longitude: "    << lon << endl
                        << "Altitude: "     << alt << endl;
    QTextStream(stdout) << "Heading: "      << heading << endl;

}

//    QTextStream(stdout) << altitude;

void GroundStation::print_ack_packet(Protocol::AckPacket& packet){
    QTextStream(stdout) << "Type: AckPacket" << endl;

}
void GroundStation::print_action_packet(Protocol::ActionPacket& packet){
    double 	lat, lon;
    float	alt, speed;

    QTextStream(stdout) << "Type: ActionPacket" << endl;
    Protocol::ActionType type = packet.GetAction();

    switch(type)
    {
        case Protocol::ActionType::Start : QTextStream(stdout) << "Start: " << (uint8_t)type << endl; break;
        case Protocol::ActionType::RequestInfo : QTextStream(stdout) << "Request Info: " << (uint8_t)type << endl; break;
        case Protocol::ActionType::AddWaypoint : QTextStream(stdout) << "Add Waypoint: " << (uint8_t)type << endl; break;
        case Protocol::ActionType::SetHome : QTextStream(stdout) << "Set Home: " << (uint8_t)type << endl; break;
        case Protocol::ActionType::RemoveWaypoint : QTextStream(stdout) << "Remove Waypoint: " << (uint8_t)type << endl; break;
        case Protocol::ActionType::Stop : QTextStream(stdout) << "Stop: " << (uint8_t)type << endl; break;
        case Protocol::ActionType::Shutdown : QTextStream(stdout) << "Shutdown: " << (uint8_t)type << endl; break;
        default :   QTextStream(stdout) << "Unknown Type: " << (uint8_t)type << endl; break;
    }

    Protocol::Waypoint waypoint = packet.GetWaypoint();
    lat = waypoint.lat;
    lon = waypoint.lon;
    alt = waypoint.alt;
    speed = waypoint.speed;

    QTextStream(stdout) << "Latitude: " << lat << endl;
    QTextStream(stdout) << "Longitude: " << lon << endl;
    QTextStream(stdout) << "Altitude: " << alt << endl;
    QTextStream(stdout) << "Speed: " << speed << endl;


}

void GroundStation::print_info_packet(Protocol::InfoPacket &packet){
    QTextStream(stdout) << "Type: InfoPacket" << endl;
    QTextStream(stdout) << "Points Storable: " << packet.GetStorable() << endl;
    QTextStream(stdout) << "Battery State: " << packet.GetBattery() << endl;
    QTextStream(stdout) << "Other : " << QString::fromStdString(packet.GetOther()) << endl;
 }
