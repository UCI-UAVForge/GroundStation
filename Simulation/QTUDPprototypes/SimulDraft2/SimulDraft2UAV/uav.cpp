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
