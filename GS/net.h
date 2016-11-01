#ifndef NET_H
#define NET_H

#include <QHostAddress>

namespace NET{

    /// LISTEN_PORT - the port number used for incoming network data
    static const int LISTEN_PORT = 20725;

    /// SEND_PORT - the port number outgoing data is sent to at the target
    /// address
    static const int SEND_PORT = 20735;

    /// PACKET_LENGTH - the maximum length of any single packet
    static const int PACKET_LENGTH = 1000;

    /// TARGET_ADDR - the default network target used when sending data.
    static const QHostAddress TARGET_ADDR = QHostAddress::LocalHost;

    /// UAV_IP_ADDRESS - a string format for the address of the UAV
    static const QString UAV_IP_ADDRESS = "localhost";
}

#endif // NET_H

