#ifndef LINK_H
#define LINK_H

#include <QDebug>
#include <QUdpSocket>
#include <QObject>
#include <queue>
#include <vector>
#include "mavlink.h"

class UdpLink: public QObject
{
    Q_OBJECT
public:
    int GCS_PORT;
    int UAV_PORT;
    QHostAddress GCS_HOST;
    QHostAddress UAV_HOST;

    UdpLink(QHostAddress uavHost, int uavPort, QHostAddress gcsHost, int gcsPort);

    void startLink();
    void sendAllMAVLinkMsgs(std::vector<mavlink_message_t>);
    void sendAllMAVLinkMsgs(std::queue<mavlink_message_t>);
    void sendMsg(mavlink_message_t);

private:
    QUdpSocket * sendUdpSocket;
    QUdpSocket * recvUdpSocket;

private slots:
    void readUdpData();
signals:
    void messageReceived(mavlink_message_t msg);
};

#endif // LINK_H
