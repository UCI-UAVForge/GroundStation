#ifndef UAV_H
#define UAV_H

#include <QObject>
#include <QUdpSocket>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>

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
    static int NUM_RECV_PACKETS = 0;
    UAV(QWidget *parent = 0);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocket;

signals:

public slots:
};

#endif // UAV_H
