#include "groundstation.h"

#include <QDateTime>

GroundStation::GroundStation(QWidget *parent)
//    : QPushButton(tr("Quit"), parent)
{
//    connect(&timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

//    timer.start(2 * 1000);
    sendDatagram();
}

void GroundStation::sendDatagram()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    out << altitude();

    udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, 27015);
}

double GroundStation::altitude() const
{
    return 4;
}

