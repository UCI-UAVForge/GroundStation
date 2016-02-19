#include "groundstation.h"
#include "unistd.h"
#include <iostream>
#include <QDateTime>

GroundStation::GroundStation(QWidget *parent)
//    : QPushButton(tr("Quit"), parent)
{
//    connect(&timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

//    timer.start(2 * 1000);

    for (int i = 0; i < 5; i++){
        usleep(1000000);
        std::cout<<"sending!"<<std::endl;
        sendDatagram();
    }
    exit(0);
}

void GroundStation::sendDatagram()
{
    static int count = 0;
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    out << QByteArray("This is an uncreative string " + QString::number(count++).toLocal8Bit());

    //udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, 27015);
    udpSocket.writeDatagram(datagram, QHostAddress("192.168.1.4"), 27015);
}

double GroundStation::altitude() const
{
    return 46;
}

