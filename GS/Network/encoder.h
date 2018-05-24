#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include "mavlink.h"
#include "link.h"
#include "waypoint.h"

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
    void sendMode(int mode);
    void sendMissionCount(uint16_t count);
    void sendMissionItem(Waypoint::WP waypoint);
    void sendClearAll();
    void sendMissionRequestList();
    void sendMissionRequest(uint16_t i);
    void sendMissionACK(uint16_t type);
    void sendMissionSetCurrent(uint16_t seq);
    void sendSetServo(int pwm);

signals:

public slots:
};

#endif // ENCODER_H
