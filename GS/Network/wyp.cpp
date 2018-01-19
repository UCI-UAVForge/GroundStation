#include "wyp.h"
#include <QDebug>

Waypoint::Waypoint() {}

// Waypoint protocol
// Default number of attempts = 10; msTimeout = 50

// Tested
void Waypoint::clearAllWaypoints() {
    timeout = true;
    requestAttempt(REQUEST_TYPE::clear);
    if (!timeout) qDebug() << "All waypoints cleared";
    else {
        timeout = false;
        qDebug() << "Waypoint::clearAllWaypoints -> Waypoints not cleared";
    }
}

// Tested w/ one waypoint
void Waypoint::readWaypointsList() {
    // Returns nullptr when unsuccessful or empty waypoint list
    timeout = true;
    nPoints = 0;
    requestAttempt(REQUEST_TYPE::list);
    if (timeout){
        emit(waypointsReceived(nullptr, 0));
        return;
    }
    if (nPoints==0) {
        emit(sendAck(0));
        emit(waypointsReceived(nullptr, 0));
        return;
    }
    WP *waypoints = new WP[nPoints];
    for (int i = 0; i < nPoints; i++) {
        timeout = true;
        requestAttempt(REQUEST_TYPE::waypoint, i);
        if (timeout){
            emit(waypointsReceived(nullptr, 0));
            return;
        }
        waypoints[i] = savedWP;
    }
    emit(sendAck(0)); // MAV_MISSION_RESULTS=0 "Accepted OK"
    emit(waypointsReceived(waypoints, nPoints));
}

// Not tested
void Waypoint::writeWaypoints(const WP * waypoints, uint16_t size) {
    ackFlag = false;
    currentRequestedMission = std::numeric_limits<uint16_t>::max();
    timeout = true;
    requestAttempt(REQUEST_TYPE::count, size);
    if (timeout){
        qDebug() << "Waypoint::writeWaypoints -> Mission count req timed out";
        emit(waypointsWriteStatus(false));
        return;
    }
    qDebug() << "Waypoint::writeWaypoints ->" << ackFlag << currentRequestedMission << size;
    for (uint16_t i = 0; i<size; i++) {
        if (currentRequestedMission != i) {
            qDebug() << "Waypoint::writeWaypoints -> WP seq not matched:: (Received:" << currentRequestedMission
                     << ") (Sending:" << i << ")";
            emit(waypointsWriteStatus(false));
            return;
        }
        if (ackFlag) {
            qDebug() << "Waypoint::writeWaypoints -> ack before transaction completed";
            emit(waypointsWriteStatus(false));
            return;
        }
        timeout = true;
        sendWaypoint(waypoints[i]);
        qDebug() << "Waypoint::writeWaypoints ->" << i << "waypoint sent";
        if (timeout) {
            qDebug() << "Waypoint::writeWaypoints -> Mission request req timed out";
            emit(waypointsWriteStatus(false));
            return;
        }
    }
    if (ackFlag) {
        emit(waypointsWriteStatus(true));
        return;
    }
    emit(waypointsWriteStatus(false));
    qDebug() << "Waypoint::writeWaypoints -> Mission ack not received";
    return;
}

// Not tested
int Waypoint::setCurrentWaypoint(uint16_t seq) {
    currentRequestedMission = std::numeric_limits<uint16_t>::max();
    missionCurrentTimeout = true;
    requestWaypointSet(seq);
    if (!missionCurrentTimeout && currentRequestedMission == seq) return 1;
    return 0;
}

void Waypoint::requestAttempt(short request_type, uint16_t n) {
    QTimer timer;
    QEventLoop loop;
    for (int i = 0; i < numAttempts && timeout; i++) {
        if (i > 0) qDebug() << "REQUEST TYPE:" << request_type << "FAILED! RETRY ATTEMPT" << i+1;
        switch(request_type) {
        case REQUEST_TYPE::clear: emit(reqClearAll()); break;
        case REQUEST_TYPE::list: emit(reqList()); break;
        case REQUEST_TYPE::waypoint: emit(reqWP(n)); break;
        case REQUEST_TYPE::count: emit(sendWPCount(n)); break;
        default: qDebug() << "Waypoint::requestAttempt() RequestType error";
        }
        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(msTimeout);
        loop.exec();
    }
}

void Waypoint::requestWaypointSet(uint16_t seq) {
    QTimer timer;
    QEventLoop loop;
    for (int i = 0; i < numAttempts && missionCurrentTimeout; i++) {
        if (i > 0) qDebug() << "REQUEST SET WAYPOINT FAILED! RETRY ATTEMPT" << i+1;
        emit(sendWPSetCurrent(seq));
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
        if (i>0) qDebug() << "REQUEST::SENDWP FAILED! RETRY ATTEMPT " << i+1;
        float params[] = {waypoint.param1, waypoint.param2, waypoint.param3, waypoint.param4, (float)waypoint.x, (float)waypoint.y, (float)waypoint.z};
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
    // Problem for write Waypoint: not receiving signal
    qDebug() << "Waypoint::updateMissionRequest";
    timeout = false;
    currentRequestedMission = mission_request.seq;
}

void Waypoint::updateMissionCurrent(mavlink_mission_current_t mCurrent) {
    timeout = false;
    currentRequestedMission = mCurrent.seq;
}
