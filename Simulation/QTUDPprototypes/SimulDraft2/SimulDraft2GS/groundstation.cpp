#include "groundstation.h"

#include <QDateTime>

GroundStation::GroundStation(QWidget *parent)
//    : QPushButton(tr("Quit"), parent)
{
//    connect(&timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

//    timer.start(2 * 1000);
    sendDatagram();
//    sendDatagram();
//    sendDatagram();
//    sendDatagram();
//    sendDatagram();
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
    waypoint.lat = 1;
    waypoint.lon = 2;
    waypoint.alt = 500;
    waypoint.speed = 250;
    testActionPacket.SetWaypoint(waypoint);


    testActionPacket.GetBytes(storage, len);

//    return 4;
}

