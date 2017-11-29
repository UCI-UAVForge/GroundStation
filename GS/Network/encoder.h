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
    void sendMissionCount(int count);
    void sendMissionItem(int seq, int cmd, float params[]);


signals:

public slots:
};

#endif // ENCODER_H
