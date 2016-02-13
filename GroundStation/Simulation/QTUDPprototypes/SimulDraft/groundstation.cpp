#include "groundstation.h"


#include <QUdpSocket>
#include <QHostAddress>

#include <QTextStream>
#include <iostream>

GroundStation::GroundStation(QObject *parent) : QObject(parent)
{

}


void GroundStation::initSocket()
{

    /*
    QString strng = "hello";
    QTextStream(stdout) << strng << endl;*/

    host = QHostAddress::LocalHost;
    client = QHostAddress::LocalHost;


    QString strng11 = "[!] signal is working";
    QTextStream(stdout) << host.toString() << endl;


    sender->connectToHost(host, 5000);


    QString strng4 = "[!] signal is working";
    QTextStream(stdout) << strng4 << endl;

    getter->bind(host, sender->localPort());


    QString strng = "[!] signal is working";
    QTextStream(stdout) << strng << endl;
    connect(getter, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));


    QString strng2 = "[!] signal is working";
    QTextStream(stdout) << strng2 << endl;

    QByteArray datagram("ffs");
    sender->write(datagram);


    QString strng3 = "[!] signal is working";
    QTextStream(stdout) << strng3 << endl;
}

void GroundStation::readPendingDatagrams()
{
    while (getter->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(getter->pendingDatagramSize());

        QHostAddress sender2;
        quint16 senderPort;

        getter->readDatagram(datagram.data(),datagram.size(),&sender2,&senderPort);

        QTextStream(stdout) << datagram;

        QString strng = "[!] signal is working";
        QTextStream(stdout) << strng << endl;
    }
}
