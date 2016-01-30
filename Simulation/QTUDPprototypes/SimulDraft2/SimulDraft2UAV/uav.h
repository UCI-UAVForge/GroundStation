#ifndef UAV_H
#define UAV_H

#include <QObject>
#include <QUdpSocket>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QTextStream>

#include "packet.h"
#include "ackpacket.h"
#include "actionpacket.h"
#include "infopacket.h"
#include "telemetrypacket.h"

class UAV : public QObject
{
    Q_OBJECT
public:
    const static int length = 1000;
    UAV(QWidget *parent = 0);

    /* Created Functions to print out information about packets
     * parameters(Packet type packet)
     * return void
     * created by: Daniel Ortega
     *
     **/
    void print_ack_packet(const Protocol::AckPacket& packet);
    void print_action_packet(const Protocol::ActionPacket& packet);
    void print_info_packet(const Protocol::InfoPacket& packet);
    void print_telemtry_packet(const Protocol::TelemtryPacket& packet);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocket;

signals:

public slots:
};

#endif // UAV_H
