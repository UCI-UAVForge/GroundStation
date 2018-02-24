#ifndef WYP_H
#define WYP_H

#include <QObject>
#include <QTimer>
#include <QEventLoop>
#include <limits>
#include <QVector>
#include "mavlink.h"

class Waypoint : public QObject
{
    Q_OBJECT
    enum REQUEST_TYPE {
        clear = 0,
        list = 1,
        waypoint = 2,
        count = 3,
    };

public:
    struct WP {
        // Note: id refers to seq
        uint16_t id;
        uint8_t frame;
        uint16_t command;
        uint8_t current;
        uint8_t autocontinue;
        float param1;
        float param2;
        float param3;
        float param4;
        float x;
        float y;
        float z;
    };
    Waypoint();
    void clearAllWaypoints();
    void readWaypointsList();
    void writeWaypoints(const QVector<WP>& waypoints, uint16_t size);
//    int setCurrentWaypoint(uint16_t seq);

signals:
    void reqClearAll();
    void reqList();
    void reqWP(uint16_t i);
    void sendAck(uint16_t type);
    void sendWPCount(uint16_t count);
    void sendWP(WP waypoint);
//    void sendWPSetCurrent(uint16_t seq);

    void waypointsReceived(WP * waypoints, uint16_t size);
    void waypointsWriteStatus(bool success);

public slots:
    void updateMissionAck(mavlink_mission_ack_t mission_ack);
    void updateMissionCount(mavlink_mission_count_t mCount);
    void updateMissionItem(mavlink_mission_item_t mission_item);
    void updateMissionRequest(mavlink_mission_request_t mission_request);
//    void updateMissionCurrent(mavlink_mission_current_t mCurrent);

private:
    bool clearTimeout;
    bool writeAck;
    bool reqFlag;
    bool countFlag;
    bool readFlag;
    bool writeFlag;
    bool missionCurrentTimeout = false;
    bool ackFlag = false;
    int numAttempts = 10;
    int msTimeout = 50;
    uint16_t nPoints = 0;
    uint16_t currentRequestedMission;
    WP savedWP;

    void sendWaypoint(const WP& waypoint);
    void requestClear();
    void sendCount(uint16_t n);
    void requestWaypoint(uint16_t n);
    void requestCount();
    void pause();
};

#endif // WYP_H
