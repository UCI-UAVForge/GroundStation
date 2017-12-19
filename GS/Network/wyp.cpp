#include "wyp.h"
#include <qDebug>

Waypoint::Waypoint(QObject *parent) : QObject(parent) {
}

// Waypoint protocol
// Default number of attempts = 10; msTimeout = 50

int Waypoint::clearAllWaypoints() {
    // Returns 1 when successful, 0 if unsuccessful
    timeout = true;
    requestAttempt(REQUEST_TYPE::clear);
    if (!timeout) return 1;
    timeout = false;
    return 0;
}

Waypoint::WP *Waypoint::readWaypointsList() {
    timeout = true;
    requestAttempt(REQUEST_TYPE::list);
    if (timeout) return nullptr;
    if (nPoints==0) {
        emit(sendAck(0));
        return nullptr;
    }
    WP *waypoints = new WP[nPoints];
    for (int i = 0; i < nPoints; i++) {
        timeout = true;
        requestAttempt(REQUEST_TYPE::waypoint, i);
        if (timeout) return nullptr;
        waypoints[i] = savedWP; // !! Not too sure if this copies or references :(
    }
    emit(sendAck(0)); // MAV_MISSION_RESULTS=0 "Accepted OK"
    return waypoints;
}

void Waypoint::requestAttempt(int request_type, uint16_t waypoint_i) {
    QTimer timer;
    QEventLoop loop;
    for (int i = 0; i < numAttempts && timeout; i++) {
        if (i > 0) qDebug() << "REQUEST FAILED! RETRY ATTEMPT " << i;
        switch(request_type) {
        case REQUEST_TYPE::clear: emit(reqClearAll()); break;
        case REQUEST_TYPE::list: emit(reqList()); break;
        case REQUEST_TYPE::waypoint: emit(reqWP(waypoint_i)); break;
        default: qDebug() << "Waypoint::requestAttempt() RequestType error";
        }
        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(msTimeout);
        loop.exec();
    }
}

void Waypoint::updateMissionAck(mavlink_mission_ack_t mission_ack) {
    qDebug() << "wyp::updatemissionclearall->" << mission_ack.type;
    timeout = false;
    return;
}

void Waypoint::updateMissionCount(mavlink_mission_count_t mCount) {
    timeout = false;
    nPoints = mCount.count;
    return;
}

void Waypoint::updateMissionItem(mavlink_mission_item_int_t mission_item) {
    timeout = false;
    savedWP.id = mission_item.seq;
    savedWP.frame = mission_item.frame;
    savedWP.command = mission_item.command;
    savedWP.current = mission_item.current;
    savedWP.autocontinue = mission_item.autocontinue;
    savedWP.param1 = mission_item.param1;
    savedWP.param2 = mission_item.param2;
    savedWP.param3 = mission_item.param3;
    savedWP.param4 = mission_item.param4;
    savedWP.x = mission_item.x;
    savedWP.y = mission_item.y;
    savedWP.z = mission_item.z;
    return;
}
