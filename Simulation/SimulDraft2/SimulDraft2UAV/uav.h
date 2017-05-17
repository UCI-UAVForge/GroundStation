#ifndef UAV_H
#define UAV_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include <QTextStream>
#include "mavlink.h"

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
    const static int GS_PORT_NUM = 20725;
    const static int UAV_PORT_NUM = 20735;
    uav(QWidget *parent = 0);

    void sendAllPackets(std::vector<mavlink_message_t>);
    void sendAllPackets(std::queue<mavlink_message_t>);
    void sendAPacket(mavlink_message_t);

private:
    bool receivedInfoPacketReq, uavWaypointsReady, uavFlying, stopAction, shutdownAction,
         uavOn, uavFlyingHome;
    QUdpSocket sendUdpSocket;
    QUdpSocket recvUdpSocket;

    mavlink_sim_state_t uavStatus;
    mavlink_battery_status_t batteryStatus;
    mavlink_storage_information_t storageStatus;
    mavlink_flight_information_t flightInfo;
    mavlink_home_position_t home;

    std::queue<Waypoint> pointOfInterest;
    int telemSeqNumber;
    double latLngSpd;
    QTimer *timer;

    mavlink_command_long_t parseCommand(mavlink_message_t);
    void addWaypoint(Waypoint);
    void updateUAVStatus();
    void sendCmdAck(mavlink_command_long_t);
    void sendFlightInfo();

private slots:
    void processPendingDatagrams();
    void sendCurrentTelem();

};


#endif // UAV_H
