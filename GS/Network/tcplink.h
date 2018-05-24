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
    void startLink(QString hostport);
    void sendData(mavlink_message_t msg);
    void closeLink();

private slots:
    void recvData();
};

#endif // TCPLINK_H
