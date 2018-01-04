#include "wyp.h"
#include <QDebug>

Waypoint::Waypoint(QObject *parent) : QObject(parent) {
}

// Waypoint protocol
// Default number of attempts = 10; msTimeout = 50

// Tested
int Waypoint::clearAllWaypoints() {
    // Returns 1 when successful, 0 if unsuccessful
    timeout = true;
    requestAttempt(REQUEST_TYPE::clear);
    if (!timeout) return 1;
    timeout = false;
    return 0;
}

// Not tested
Waypoint::WP *Waypoint::readWaypointsList() {
    // Returns nullptr when unsuccessful or empty waypoint list
    timeout = true;
    nPoints = 0;
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

// Not tested
int Waypoint::writeWaypoints(const WP * waypoints, uint16_t size) {
    // Returns 0 if unsuccessful
    ackFlag = false;
    currentRequestedMission = std::numeric_limits<uint16_t>::max();
    timeout = true;
    requestAttempt(REQUEST_TYPE::count, size);
    if (timeout) return 0;
    for (uint16_t i = 0; i<size; i++) {
        if (currentRequestedMission != i) {
            qDebug() << "WAYPOINT WRITE SEQ NOT MATCHING:: (Received:" << currentRequestedMission
                     << ") (Sending:" << i << ")";
            return 0;
        }
        if (ackFlag) {
            qDebug() << "WAYPOINT INCOMPLETE WRITE: wp msgs being sent outside transaction";
            return 0;
        }
        timeout = true;
        sendWaypoint(waypoints[i]);
        if (timeout) return 0;
    }
    if (ackFlag) return 1;
    qDebug() << "WP ACK NOT RECEIVED AFTER WRITE TRANSACTION";
    return 0;
}

// Not tested
int Waypoint::setCurrentWaypoint(uint16_t seq) {
    currentRequestedMission = std::numeric_limits<uint16_t>::max();
    timeout = true;
    requestAttempt(REQUEST_TYPE::setCurrent, seq);
    if (!timeout && currentRequestedMission == seq) return 1;
    return 0;
}

void Waypoint::requestAttempt(int request_type, uint16_t n) {
    QTimer timer;
    QEventLoop loop;
    for (int i = 0; i < numAttempts && timeout; i++) {
        if (i > 0) qDebug() << "REQUEST FAILED! RETRY ATTEMPT " << i+1;
        switch(request_type) {
        case REQUEST_TYPE::clear: emit(reqClearAll()); break;
        case REQUEST_TYPE::list: emit(reqList()); break;
        case REQUEST_TYPE::waypoint: emit(reqWP(n)); break;
        case REQUEST_TYPE::count: emit(sendWPCount(n)); break;
        case REQUEST_TYPE::setCurrent: emit(sendWPSetCurrent(n)); break;
        default: qDebug() << "Waypoint::requestAttempt() RequestType error";
        }
        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(msTimeout);
        loop.exec();
    }
}

void Waypoint::sendWaypoint(const WP& waypoint) {
    QTimer timer;
    QEventLoop loop;
    for (int i = 0; i < numAttempts && timeout; i++) {
        if (i>0) qDebug() << "REQUEST::SENDWP FAILED! RETRY ATTEMPT " << i;
        float params[] = {waypoint.param1, waypoint.param2, waypoint.param3, waypoint.param4, waypoint.x, waypoint.y, waypoint.z};
        emit(sendWP(waypoint.id, waypoint.command, params));
        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(msTimeout);
        loop.exec();
    }
}

void Waypoint::updateMissionAck(mavlink_mission_ack_t mission_ack) {
    if (mission_ack.type == 0) {
        ackFlag = true;
        timeout = false;
    }
}

void Waypoint::updateMissionCount(mavlink_mission_count_t mCount) {
    timeout = false;
    nPoints = mCount.count;
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
}

void Waypoint::updateMissionRequest(mavlink_mission_request_int_t mission_request) {
    timeout = false;
    currentRequestedMission = mission_request.seq;
}

void Waypoint::updateMissionCurrent(mavlink_mission_current_t mCurrent) {
    timeout = false;
    currentRequestedMission = mCurrent.seq;
}
