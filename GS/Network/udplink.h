#ifndef UDPLINK_H
#define UDPLINK_H

#include <QUdpSocket>
#include <queue>
#include <vector>
#include "mavlink.h"
#include "link.h"
#include <QHostAddress>

class UdpLink: public Link
{
public:
    UdpLink();
    void startLink(QString hostport);
    void sendAllMAVLinkMsgs(std::vector<mavlink_message_t>);
    void sendAllMAVLinkMsgs(std::queue<mavlink_message_t>);
    void sendData(mavlink_message_t);
    void closeLink();
    int getPort();
    QHostAddress getHost();

private:
    QUdpSocket * sendUdpSocket;
    QUdpSocket * recvUdpSocket;

    int GCS_PORT = 14550;
    int UAV_PORT = 5761;
    QHostAddress GCS_HOST = QHostAddress::LocalHost;
    QHostAddress UAV_HOST = QHostAddress::LocalHost;

private slots:
    void recvData();
};

#endif // LINK_H
