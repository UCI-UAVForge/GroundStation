#include "wyp.h"
#include <QDebug>

/*
 * Waypoint/Mission Protocol
 * Default number of connection attempts = 10
 * Default number of ms for timeout = 50
*/

// TODO: set current waypoint!

Waypoint::Waypoint() {


}

// Public

void Waypoint::clearAllWaypoints() {
    clearTimeout = true;
    requestClear();
    if (!clearTimeout) emit(waypointsClearStatus(true));
    else {
        emit(waypointsClearStatus(false));
    }
}

void Waypoint::writeWaypoints(const QVector<WP>& waypoints, uint16_t size) {
    writeAck = false;
    currentRequestedMission = std::numeric_limits<uint16_t>::max();
    // Note: will not work if the size is equal to uint16 max

    // Send number of waypoints to emit
    reqFlag = true;
    sendCount(size);
    if (reqFlag) {
        qDebug() << "Send Mission count timed out.";
        emit(waypointsWriteStatus(false));
        return;
    }

    // Send Missions
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
        if (i != size-1 && reqFlag) {   // ackFlag set instead at last waypoint
            qDebug () << "Write mission timed out.";
            emit(waypointsWriteStatus(false));
            return;
        }
    }

    // Check for mission ack
    for (short i = 0; i < numAttempts && !writeAck; i++)
        pause();
    if (!writeAck) {
        qDebug() << "Post-write mission ack not received.";
        emit(waypointsWriteStatus(false));
        return;
    }
    emit(waypointsWriteStatus(true));
}

void Waypoint::readWaypointsList() {
    nPoints = 0;
    countFlag = true;

    // Request mission count
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

    qDebug() << "Read count received::" << nPoints;

    // Request each mission
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
    emit(waypointsReceived(waypoints, nPoints)); // Successful read
}
/*
 * Problem: Waypoint read will still receive mission items even when there
 * is no mission request. First mission it receives is its current position
*/

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
