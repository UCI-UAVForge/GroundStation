#ifndef WYP_H
#define WYP_H

#include <QObject>
#include <QTimer>
#include <QEventLoop>
#include <limits>
#include "encoder.h"
#include "decoder.h"
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
        uint16_t id;
        uint8_t frame;
        uint16_t command;
        uint8_t current;
        uint8_t autocontinue;
        float param1;
        float param2;
        float param3;
        float param4;
        int32_t x;
        int32_t y;
        float z;
    };

    Waypoint();
    void clearAllWaypoints();
    void readWaypointsList();
    void writeWaypoints(const WP * waypoints, uint16_t size);
    int setCurrentWaypoint(uint16_t seq);

signals:
    void reqClearAll();
    void reqList();
    void reqWP(uint16_t i);
    void sendAck(uint16_t type);
    void sendWPCount(uint16_t count);
    void sendWP(int seq, int cmd, float params[]);
    void sendWPSetCurrent(uint16_t seq);

    void waypointsReceived(WP * waypoints, uint16_t size);
    void waypointsWriteStatus(bool success);

public slots:
    void updateMissionAck(mavlink_mission_ack_t mission_ack);
    void updateMissionCount(mavlink_mission_count_t mCount);
    void updateMissionItem(mavlink_mission_item_int_t mission_item);
    void updateMissionRequest(mavlink_mission_request_int_t mission_request);
    void updateMissionCurrent(mavlink_mission_current_t mCurrent);

private:
    bool timeout = false;
    bool missionCurrentTimeout = false;
    bool ackFlag = false;
    int numAttempts = 10;
    int msTimeout = 50;
    int nPoints = 0;
    uint16_t currentRequestedMission;
    WP savedWP;
    void requestAttempt(short request_type, uint16_t n = std::numeric_limits<uint16_t>::max());
    void requestWaypointSet(uint16_t seq);
    void sendWaypoint(const WP& waypoint);
};

#endif // WYP_H
