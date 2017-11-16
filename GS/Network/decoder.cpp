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
        case 29:
            mavlink_scaled_pressure_t pressure;
            mavlink_msg_scaled_pressure_decode(&msg, &pressure);
            emit(pressureReceived(pressure));
        break;
        case 30:
            mavlink_attitude_t att;
            mavlink_msg_attitude_decode(&msg, &att);
            emit(attReceived(att));
        break;
        case 33:
            mavlink_global_position_int_t gps_int;
            mavlink_msg_global_position_int_decode(&msg, &gps_int);
        //    qDebug() << gps_int.lat << "," << gps_int.lon;
        case 42:
           // qDebug() << "CURRENT MISSION IS";
            mavlink_mission_current_t mcurrent;
            mavlink_msg_mission_current_decode(&msg, &mcurrent);
          //  qDebug() << mcurrent.seq;
        break;
        case 44:
            qDebug() << "MISSION COUNT RECEIVED";
            mavlink_mission_count_t mcount;
            mavlink_msg_mission_count_decode(&msg, &mcount);
            qDebug() << mcount.count;
        break;
        case 62:
            mavlink_nav_controller_output_t nav;
            mavlink_msg_nav_controller_output_decode(&msg, &nav);
            emit(navReceived(nav));
        case 77:
            qDebug() << "ACK";
            mavlink_command_ack_t cmdack;
            mavlink_msg_command_ack_decode(&msg, &cmdack);
            parseCmdAck(cmdack);
            qDebug() << "CMD: " << cmdack.command << " RESULT: " << cmdack.result;
        break;
        case 87:
            //pos stuff
        break;
        case 147:
            mavlink_battery_status_t battery;
            mavlink_msg_battery_status_decode(&msg, &battery);
            emit(batteryReceived(battery));
        break;
        case 152:
            //qDebug() << "mem";
        break;
        case 168:
            mavlink_wind_t wind;
            mavlink_msg_wind_decode(&msg, &wind);
            emit(windReceived(wind));
        break;
        default:
            //qDebug() << "Message not supported";
           qDebug() << msg.msgid;
            break;
    }
}

void Decoder::parseCmdAck(mavlink_command_ack_t cmdAck) {
    switch(cmdAck.command) {
        case 11:
            if(cmdAck.result == 0)
                emit(modeChanged());
        break;
        case 400:
            if(cmdAck.result == 0)
                emit(armSuccess());
            else
                emit(armFailed());
        break;
    default:
        break;

    }
}
