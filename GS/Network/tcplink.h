#ifndef TCPLINK_H
#define TCPLINK_H

#include "mavlink.h"
#include <QTcpSocket>
#include <QHostAddress>
class TcpLink : public QObject
{
    Q_OBJECT
public:
    QTcpSocket * tcp;
    TcpLink();
    void sendMsg(mavlink_message_t);
public slots:
    void readTcpData();
signals:
    void messageReceived(mavlink_message_t);
};

#endif // TCPLINK_H
