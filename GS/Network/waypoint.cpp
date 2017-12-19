#include "waypoint.h"
#include <qDebug>
#include <QTime>
#include <QtCore>
#include <QEventLoop>

Waypoint::Waypoint(QObject *parent) : QObject(parent) {
}

// Waypoint protocol
// Default number of attempts = 10

int Waypoint::clearAllWaypoints() {
    // Returns 1 when successful, 0 if unsuccessful
    timeout = true;
    for (int i = 0; i < numAttempts && timeout; i++) {
        QTime time;
        time.start();
        qDebug() << "Attempt:" << i;
        emit(reqClearAll());
        while (time.elapsed() < 500) {
            QEventLoop::processEvents();
        }
    }
    if (!timeout) return 1;
    timeout = false;
    return 0;
}

int Waypoint::readWaypointsList() {
    timeout = true;
//    requestAttempt(Encoder::sendWP_RequestList());
    if (timeout) return 0;
    timeout = true;
    for (int i = 0; i < nPoints; i++) {
//        requestAttempt(Encoder::sendWP_Request(i));
        if (timeout) return 0;
        timeout = true;
    }
//    requestAttempt(Encoder::sendWP_ACK(0));
    if (timeout) return 0;
    timeout = true;
    return 1;
}

// USE 47 ACK PLS

void Waypoint::requestAttempt(void (*req)()) {
    for (int i = 0; i < numAttempts && timeout; i++) {
        (*req)();
        this->msleep(50);
    }
}

void Waypoint::updateMissionClearAll(mavlink_mission_ack_t mission_ack) {
    qDebug() << "RECEIVED";
    timeout = false;
    return;
}
