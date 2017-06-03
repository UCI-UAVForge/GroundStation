#ifndef UAV_H
#define UAV_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QTextStream>
#include <QQueue>

#include "mavlink.h"
#include "link.h"

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

    Waypoint homePoint;

    uint8_t SYSID;
    uint8_t COMPID;

    QQueue<Waypoint> pointOfInterest;
    int telemSeqNumber;
    double latLngSpd;
    QTimer *timer;
    QTime *timeSinceBoot;

    void addWaypoint(Waypoint wp);
    void clearWaypoints();

    void updateUAVTelem();
    void sendFlightInfo();
    void sendSimState();
    void sendCmdAck(uint16_t commandID, uint8_t result);

private slots:
    void sendCurrentTelem();
    uint16_t parseCommand(mavlink_message_t msg);

};


#endif // UAV_H
