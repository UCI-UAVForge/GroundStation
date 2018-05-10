#include "waypoint.h"
#include <QDebug>

/*
 * Waypoint/Mission Protocol
 * Default number of connection attempts = 10
 * Default number of ms for timeout = 50
*/

Waypoint::Waypoint() {}

// Public

void Waypoint::clearAllWaypoints() {
//    emit(ongoingMission(true));
    clearTimeout = true;
    requestClear();
    if (!clearTimeout) emit(waypointsClearStatus(true));
    else {
        emit(waypointsClearStatus(false));
    }
//    emit(ongoingMission(false));
}

void Waypoint::writeWaypoints(const QVector<WP>& waypoints) {
//    emit(ongoingMission(true));
    uint16_t size = waypoints.length();
    writeAck = false;
    currentRequestedMission = std::numeric_limits<uint16_t>::max();
    reqFlag = true;
    sendCount(size);
    if (reqFlag) {
        qDebug() << "Send Mission count timed out.";
        emit(waypointsWriteStatus(false));
        return;
    }
    for (uint16_t i = 0; i < size; i++) {
        if (currentRequestedMission != i) {
            qDebug() << "Send mission out of sync! (Received:"
                << currentRequestedMission << ") (Sending:" << i << ")";
            emit(waypointsWriteStatus(false));
            return;
        }
        if (writeAck) {
            qDebug() << "Received mission ack before transaction completed.";
            emit(waypointsWriteStatus(false));
            return;
        }

        reqFlag = true;
        sendWaypoint(waypoints.at(i));
        if (i != size-1 && reqFlag) {
            qDebug () << "Write mission timed out.";
            emit(waypointsWriteStatus(false));
            return;
        }
    }
    for (short i = 0; i < numAttempts && !writeAck; i++)
        pause();
    if (!writeAck) {
        qDebug() << "Post-write mission ack not received.";
        emit(waypointsWriteStatus(false));
        return;
    }
    emit(waypointsWriteStatus(true));
//    emit(ongoingMission(false));
}

void Waypoint::readWaypointsList() {
    // * Bug: Still receive missions in multiples of 5
//    emit(ongoingMission(true));
    nPoints = 0;
    countFlag = true;
    requestCount();
    if (countFlag) {
        emit(waypointsReceived(nullptr, 0));
        return;
    }
    if (nPoints == 0) {
        emit(sendAck(0));
        emit(waypointsReceived(nullptr, 0));
        return;
    }
    WP * waypoints = new WP[nPoints];
    for (uint16_t i = 0; i < nPoints; i++) {
        readFlag = true;
        requestWaypoint(i);
        if (readFlag) {
            emit(waypointsReceived(nullptr, 0));
            return;
        }
        waypoints[i] = savedWP;
    }
    emit(sendAck(0));
    emit(waypointsReceived(waypoints, nPoints));
//    emit(ongoingMission(false));
}

void Waypoint::setCurrentWaypoint(uint16_t index) {
//    emit(ongoingMission(true));
    setCurrentWaypointFlag = false;
    setCurrentIndex = index;
    for (short i = 0;i < numAttempts && !setCurrentWaypointFlag; i++) {
        if (i > 0) qDebug() << "Count request failed.. Retry attempt" << i+1;
        emit(sendWPSetCurrent(index));
        pause();
    }
    if (!setCurrentWaypointFlag) {
        // didn't work
    }
    else {
        // it worked
        setCurrentIndex = UINT16_MAX;
    }
//    emit(ongoingMission(false));
}

// Private and Signaling

void Waypoint::requestClear() {
    for (short i = 0; i < numAttempts && clearTimeout; i++) {
        if (i > 0) qDebug() << "Clear Missions request failed... Retry attempt" << i+1;
        emit(reqClearAll());
        pause();
    }
}

void Waypoint::sendCount(uint16_t n) {
    for (short i = 0; i < numAttempts && reqFlag; i++) {
        if (i > 0) qDebug() << "Send Mission Count request failed... Retry attempt" << i+1;
        emit(sendWPCount(n));
        pause();
    }
}

void Waypoint::sendWaypoint(const WP &waypoint) {
    for (short i = 0; i < numAttempts && reqFlag && !writeAck; i++) {
        if (i > 0) qDebug() << "Send Mission failed... Retry attempt" << i+1;
        emit(sendWP(waypoint));
        pause();
    }
}

void Waypoint::requestWaypoint(uint16_t n) {
    for (short i = 0; i < numAttempts && readFlag; i++) {
        if (i > 0) qDebug() << "Mission" << n << "request failed... Retry attempt" << i+1;
        emit(reqWP(n));
        pause();
    }
}

void Waypoint::requestCount() {
    for (short i = 0;i < numAttempts && countFlag; i++) {
        if (i > 0) qDebug() << "Count request failed.. Retry attempt" << i+1;
        emit(reqList());
        pause();
    }
}

void Waypoint::pause() {
    QTimer timer;
    QEventLoop loop;
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(msTimeout);
    loop.exec();
}

void Waypoint::updateMissionAck(mavlink_mission_ack_t mission_ack) {
    if (mission_ack.type == 0) {
//        qDebug() << "! * mission ack";
        clearTimeout = false;
        writeAck = true;
    }
}

void Waypoint::updateMissionRequest(mavlink_mission_request_t mission_request) {
    if (currentRequestedMission != mission_request.seq) {
//        qDebug() << "! * Updated mission req" << mission_request.seq;
        currentRequestedMission = mission_request.seq;
        reqFlag = false;
    }
}

void Waypoint::updateMissionItem(mavlink_mission_item_t mission_item) {
//    qDebug() << "! * Updated mission item";
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
    readFlag = false;
}

void Waypoint::updateMissionCount(mavlink_mission_count_t mCount) {
//    qDebug() << "! * update mission count" << mCount.count;
    nPoints = mCount.count;
    countFlag = false;
}

void Waypoint::updateCurrent(mavlink_mission_current_t curr) {
    if (curr.seq == setCurrentIndex)
        setCurrentWaypointFlag = true;
}
