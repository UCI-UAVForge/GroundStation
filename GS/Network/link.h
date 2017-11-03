#ifndef LINK_H
#define LINK_H

#include <QDebug>
#include <QUdpSocket>
#include <QObject>
#include <queue>
#include <vector>
#include "mavlink.h"

class Link: public QObject
{
    Q_OBJECT
public:
    const static int GS_PORT_NUM = 30725;
    const static int UAV_PORT_NUM = 30735;
    Link();

    void startLink();
    void sendAllMAVLinkMsgs(std::vector<mavlink_message_t>);
    void sendAllMAVLinkMsgs(std::queue<mavlink_message_t>);
    void sendMAVLinkMsg(mavlink_message_t);

private:
    QUdpSocket * sendUdpSocket;
    QUdpSocket * recvUdpSocket;

private slots:
    void processPendingDatagrams();
signals:
    void messageReceived(mavlink_message_t msg);
};

#endif // LINK_H
