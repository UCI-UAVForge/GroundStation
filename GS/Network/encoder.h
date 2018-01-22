#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include "mavlink.h"
#include "link.h"
#include "wyp.h"

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
    void sendMissionCount(uint16_t count);
//    void sendMissionItem(int seq, int cmd, float params[]);
    void sendMissionItem(Waypoint::WP waypoint);
    void sendClearAll();
    void sendMissionRequestList();
    void sendMissionRequest(uint16_t i);
    void sendMissionACK(uint16_t type);
    void sendMissionSetCurrent(uint16_t seq);

signals:

public slots:
};

#endif // ENCODER_H
