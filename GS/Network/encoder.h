#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include "mavlink.h"
#include "link.h"

class Encoder : public QObject
{
    Q_OBJECT
public:
    explicit Encoder(QObject *parent = nullptr);
    Link * link;
    void setLink(Link * l);

    int SYS;
    int COM;

    void sendArm(bool armed);
    void sendSetGuided();
    void sendSetAuto();
    void sendSetManual();
    void sendSetCircle();
    void sendSetStabilize();
    void sendSetFBWA();
    void sendSetFBWB();
    void sendSetCruise();
    void sendSetRTL();
    void sendSetLoiter();
    void sendSetInitialising();
    void sendMissionCount(int count);
    void sendMissionItem(int seq, int cmd, float params[]);
    void sendClearAll();
    void sendWP_RequestList();
    void sendWP_Request(uint16_t i);
    void sendWP_ACK(uint16_t type);


signals:

public slots:
};

#endif // ENCODER_H
