#include "uav.h"
#include <QDateTime>

#include "Packet.h"
#include "TelemetryPacket.h"
#include "ActionPacket.h"

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
    QByteArray datagram;
        QTextStream(stdout) << "Processing started";



    do {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    } while (udpSocket.hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_3);

    u_int8_t packetFormed[1000];


    Protocol::ActionPacket test((u_int8_t*)datagram.data(), 1000);
    Protocol::Waypoint waypoint;

    waypoint = test.GetWaypoint();

    QTextStream(stdout) << "Action: " << (u_int8_t)test.GetAction();
    QTextStream(stdout) << "\nWaypoint: " << waypoint.lat << " ," << waypoint.lon << " ," <<
                           waypoint.alt << " ," << waypoint.speed;

//    QTextStream(stdout) << test;
//        QTextStream(stdout) << "run this shit";


//    QTextStream(stdout) << altitude;
}
