#include "uav.h"
#include <QDateTime>

UAV::UAV(QWidget *parent)
//    : QDialog(parent)
{
    udpSocket.bind(UAV.UAV_PORT_NUM);

    connect(&udpSocket, SIGNAL(readyRead()),
                this, SLOT(processPendingDatagrams()));

    QTextStream(stdout) << "Listening for packets.." << endl;

}

void UAV::sendAllActionPackets(std::vector<Protocol::Packet*> packets)
{
    //QTextStream(stdout) << "The size of the vector is " << packets.size() << endl;
    for(auto i = packets.begin(); i != packets.end(); ++i)
    {
        sendAPacket(&*i);
    }

}


void UAV::sendAPacket(Protocol::Packet* packet)
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
    udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, UAV.GS_PORT_NUM);
}



void UAV::processPendingDatagrams()
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
        Protocol::Packet::Type packet_type = packet.get_type();

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

void UAV::print_telemetry_packet(const Protocol::TelemetryPacket& packet)
{
    float   vx, vy, vz,
            pitch, roll, yaw,
            heading;

    double  lat, lon, alt; 
    
    // Extract all information from telemetry packet into variables
    packet.GetVelocity(&vx, &vy, &vz);
    packet.GetOrientation(&pitch, &roll, &yaw);
    packet.GetLocation(&lat, &lon, &alt);
    packet.GetHeading(&heading);

    // Print out information
    QTextStream(stdout) << "Type: Telemetry Packet" << std::endl;
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

}
void UAV::print_ack_packet(const Protocol::AckPacket& packet){
    QTextStream(stdout) << "Type: AckPacket" << endl;

}
void UAV::print_action_packet(const Protocol::ActionPacket& packet){
    QTextStream(stdout) << "Type: ActionPacket" << endl;
    Protocol::ActionType type = packet.GetAction();
    switch(type)
    {
        case ActionType::Start : QTextStream(stdout) << "Start: " << type << endl; break;
        case ActionType::RequestInfo : QTextStream(stdout) << "Request Info: " << type << endl; break;
        case ActionType::AddWaypoint : QTextStream(stdout) << "Add Waypoint: " << type << endl; break;
        case ActionType::SetHome : QTextStream(stdout) << "Set Home: " << type << endl; break;
        case ActionType::RemoveWaypoint : QTextStream(stdout) << "Remove Waypoint: " << type << endl; break;
        case ActionType::Stop : QTextStream(stdout) << "Stop: " << type << endl; break;
        case ActionType::Shutdown : QTextStream(stdout) << "Shutdown: " << type << endl; break;
        default :   QTextStream(stdout) << "Unknown Type: " << type << endl; break;
    }
}

void UAV::print_info_packet(const Protocol::InfoPacket &packet){
    QTextStream(stdout) << "Type: InfoPacket" << endl;
    QTextStream(stdout) << "Points Storable: " << packet.GetStorable() << endl;
    QTextStream(stdout) << "Battery State: " << packet.GetBattery() << endl;
    QTextStream(stdout) << "Other : " << packet.GetOther() << endl;
 }
