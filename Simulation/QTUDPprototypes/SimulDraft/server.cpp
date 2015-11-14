#include "server.h"
#include <QUdpSocket>
#include <QHostAddress>

#include <QTextStream>
#include <iostream>

Server::Server() {
    //what do?

}

Server::~Server() {

}

void Server::initSocket()
{

    host = QHostAddress::LocalHost;
    client = QHostAddress::LocalHost;

    sender->connectToHost(client,3000);
    getter->bind(host, sender->localPort());
    connect(getter, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

    QByteArray datagram("ffs");
    sender->write(datagram);

}

void Server::readPendingDatagrams()
{
    while (getter->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(getter->pendingDatagramSize());

        QHostAddress sender2;
        quint16 senderPort;

        getter->readDatagram(datagram.data(),datagram.size(),&sender2,&senderPort);

        QTextStream(stdout) << datagram;

    }
}

/*
socket->hasPendingDatangrams()
qbytearray datagram
datagram.resize(socket->pendingdatagramssize())
socket->readDatagram(datagram.data(), datagram.size())
daragram.data()


http://www.informit.com/articles/article.aspx?p=1405552&seqNum=4
*/


