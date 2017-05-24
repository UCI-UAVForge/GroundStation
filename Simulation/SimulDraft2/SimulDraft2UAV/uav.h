#ifndef UAV_H
#define UAV_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include <QTextStream>

#include "mavlink.h"
#include "link.h"

#include <queue>
#include <vector>

typedef struct
{
    double lat;// = 0;
    double lon;// = 0;
    float alt;// = 0;
    float speed;// = 0;
} Waypoint;


class uav : public QObject
{
    Q_OBJECT

public:
    uav(QWidget *parent = 0);
    link udpLink;

private:
    bool receivedInfoPacketReq, uavWaypointsReady, uavFlying, stopAction, shutdownAction,
         uavOn, uavFlyingHome;

    mavlink_sim_state_t uavStatus;
    mavlink_battery_status_t batteryStatus;
    mavlink_storage_information_t storageStatus;
    mavlink_flight_information_t flightInfo;
    mavlink_home_position_t home;

    std::queue<Waypoint> pointOfInterest;
    int telemSeqNumber;
    double latLngSpd;
    QTimer *timer;

    void addWaypoint(Waypoint);
    void updateUAVStatus();
    void sendCmdAck(mavlink_command_long_t);
    void sendFlightInfo();

private slots:
    void sendCurrentTelem();
    mavlink_command_long_t parseCommand(mavlink_message_t);

};


#endif // UAV_H
