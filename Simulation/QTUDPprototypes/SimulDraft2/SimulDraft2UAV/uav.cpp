#include "uav.h"
#include <QDateTime>

UAV::UAV(QWidget *parent)
//    : QDialog(parent)
{
    udpSocket.bind(27015);

    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
//    QTextStream(stdout) << "run this shit";

}



void UAV::processPendingDatagrams()
{
    QByteArray datagram;
        QTextStream(stdout) << "run this shit";

    do {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    } while (udpSocket.hasPendingDatagrams());

    QByteArray altitude;
    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_3);
    in >> altitude;
    QTextStream(stdout) << "running...";


    QTextStream(stdout) << altitude;
}
