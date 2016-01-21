#ifndef GROUNDSTATION_H
#define GROUNDSTATION_H

#include <QObject>
#include <QPushButton>
#include <QUdpSocket>

#include <QTimer>

#include "Packet.h"
#include "ActionPacket.h"


class GroundStation : public QObject
{
    Q_OBJECT

public:
    GroundStation(QWidget *parent = 0);
//    double altitude() const;
    void altitude(u_int8_t* storage, int len) const;

private slots:
       void sendDatagram();
private:
       QUdpSocket udpSocket;
       QTimer timer;

signals:

public slots:
};

#endif // GROUNDSTATION_H
