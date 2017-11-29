#ifndef TCPLINK_H
#define TCPLINK_H

#include "mavlink.h"
#include <QTcpSocket>
#include <QHostAddress>
#include "link.h"

class TcpLink : public Link
{
public:
    QTcpSocket * tcp;
    TcpLink();
    void startLink();
    void sendData(mavlink_message_t msg);

private slots:
    void recvData();
};

#endif // TCPLINK_H
