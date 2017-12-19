#ifndef WYP_H
#define WYP_H

#include <QObject>
#include <QTimer>
#include <QEventLoop>
#include "encoder.h"
#include "decoder.h"
#include "mavlink.h"


class Waypoint : public QObject
{
    Q_OBJECT
    enum REQUEST_TYPE {
        clear = 0,
        list = 1,
        waypoint = 2
    };
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

public:
    Waypoint(QObject *parent);
    void setEncoder(Encoder& encoder);
    int clearAllWaypoints();
    WP* readWaypointsList();

signals:
    void reqClearAll();
    void reqList();
    void reqWP(uint16_t i);
    void sendAck(uint16_t type);

public slots:
    void updateMissionAck(mavlink_mission_ack_t mission_ack);
    void updateMissionCount(mavlink_mission_count_t mCount);
    void updateMissionItem(mavlink_mission_item_int_t mission_item);

private:
    bool timeout = false;
    int numAttempts = 10;
    int msTimeout = 50;
    int nPoints = 0;
    WP savedWP;
    void requestAttempt(int request_type, uint16_t waypoint_i = 0);
};

#endif // WYP_H
