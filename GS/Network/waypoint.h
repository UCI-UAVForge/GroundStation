#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QObject>
#include <QThread>
#include "encoder.h"
#include "decoder.h"
#include "mavlink.h"

#include <QStateMachine>


class Waypoint : public QObject, QThread
{
    Q_OBJECT
public:
    Waypoint(QObject *parent);
    void setEncoder(Encoder& encoder);
    int clearAllWaypoints();
    int readWaypointsList();

signals:
    void reqClearAll();

public slots:
    void updateMissionClearAll(mavlink_mission_ack_t mission_ack);

private:
    bool timeout = false;
    int numAttempts = 10;
    int nPoints;
    void requestAttempt(void (*req)());
};

#endif // WAYPOINT_H
