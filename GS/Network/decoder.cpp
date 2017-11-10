#include "decoder.h"
#include <QDebug>
Decoder::Decoder(QObject *parent) : QObject(parent){}

bool Decoder::setLink(UdpLink * l) {
    return connect(l, &UdpLink::messageReceived,  this, &Decoder::parseMessage);
}

bool Decoder::setLink(TcpLink * l) {
    return connect(l, &TcpLink::messageReceived,  this, &Decoder::parseMessage);
}

void Decoder::parseMessage(mavlink_message_t msg) {
    switch(msg.msgid) {
        case 0:
            mavlink_heartbeat_t heartbeat;
            mavlink_msg_heartbeat_decode(&msg, &heartbeat);
            emit(heartbeatReceived(heartbeat));
        break;
        case 1:
            mavlink_sys_status_t status;
            mavlink_msg_sys_status_decode(&msg , &status);
            emit(statusReceived(status));
        break;
        case 2:
            mavlink_system_time_t systime;
            mavlink_msg_system_time_decode(&msg, &systime);
        break;
        case 24:
            mavlink_gps_raw_int_t gps;
            mavlink_msg_gps_raw_int_decode(&msg, &gps);
            emit(gpsReceived(gps));
        break;
        case 27:
            mavlink_raw_imu_t imu;
            mavlink_msg_raw_imu_decode(&msg, &imu);
        break;
        case 30:
            mavlink_attitude_t att;
            mavlink_msg_attitude_decode(&msg, &att);
            emit(attReceived(att));
        break;
        case 44:
            qDebug() << "MISSION COUNT RECEIVED";
            mavlink_mission_count_t mcount;
            mavlink_msg_mission_count_decode(&msg, &mcount);
            qDebug() << mcount.count;



        default:
            //qDebug() << "Message not supported";
          //  qDebug() << msg.msgid;
            break;
    }
}
