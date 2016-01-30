#include "uav.h"
#include <QDateTime>

UAV::UAV(QWidget *parent)
//    : QDialog(parent)
{
    udpSocket.bind(27015);

    connect(&udpSocket, SIGNAL(readyRead()),
                this, SLOT(processPendingDatagrams()));
//    QTextStream(stdout) << "run this shit";

}



void UAV::processPendingDatagrams()
{
    QTextStream(stdout) << "Processing started" << endl;

    while(udpSocket.hasPendingDatagrams())
    {
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


        //u_int8_t packetFormed[1000];
        //for(int i = 0; in.status() != QDataStream::ReadPastEnd  ; ++i)
        //{
            //in >> packetFormed[i];
        //}


        // Convert datagram into an actionpacket
        Protocol::ActionPacket action_packet((u_int8_t*)datagram.data(), 1000);
        //Protocol::ActionPacket test(packetFormed, 1000);
        Protocol::Waypoint waypoint;

        waypoint = action_packet.GetWaypoint();

        QTextStream(stdout) << "Action: "       << (u_int8_t)action_packet.GetAction() << endl;
        QTextStream(stdout) << "Latitude: "     << waypoint.lat << endl
                            << "Longitude: "    << waypoint.lon << endl
                            << "Altitude: "     <<  waypoint.alt << endl
                            << "Speed: "        << waypoint.speed << endl << endl;

    }
//    QTextStream(stdout) << test;
//        QTextStream(stdout) << "run this shit";


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
