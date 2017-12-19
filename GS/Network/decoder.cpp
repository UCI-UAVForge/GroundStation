#include "decoder.h"
#include <QDebug>
Decoder::Decoder(QObject *parent) : QObject(parent){}

bool Decoder::setLink(Link * l) {
    return connect(l, &Link::messageReceived, this, &Decoder::parseMessage);
}

void Decoder::parseMessage(mavlink_message_t msg) {
    switch(msg.msgid) {
        case 0:
            mavlink_heartbeat_t heartbeat;
            mavlink_msg_heartbeat_decode(&msg, &heartbeat);
            emit(heartbeatReceived(heartbeat));
            qDebug() << "decoder.cpp::" << heartbeat.custom_mode;
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
        case 32:
            mavlink_local_position_ned_t l_pos;
            mavlink_msg_local_position_ned_decode(&msg, &l_pos);
            emit(localPositionReceived(l_pos));
        break;
        case 33:
            mavlink_global_position_int_t gps_int;
            mavlink_msg_global_position_int_decode(&msg, &gps_int);
        //    qDebug() << gps_int.lat << "," << gps_int.lon;
        break;
        case 40:
            mavlink_mission_request_t mrequest;
            mavlink_msg_mission_request_decode(&msg, &mrequest);
            emit (mrequestReceived(mrequest));
        case 42:
           // qDebug() << "CURRENT MISSION IS";
            mavlink_mission_current_t mcurrent;
            mavlink_msg_mission_current_decode(&msg, &mcurrent);
           // qDebug() << mcurrent.seq;
        break;
        case 44:
            mavlink_mission_count_t mcount;
            mavlink_msg_mission_count_decode(&msg, &mcount);
            qDebug() << mcount.count;
            qDebug() << "DECODER:MISSION COUNT RECEIVED";
            emit(missionCountReceived(mcount));
        break;
        case 45:
            mavlink_mission_clear_all_t mission_clear_all;
            mavlink_msg_mission_clear_all_decode(&msg, &mission_clear_all);
            emit(mClearAllReceived(mission_clear_all));
        break;
        case 47:
            mavlink_mission_ack_t mission_ack;
            mavlink_msg_mission_ack_decode(&msg, &mission_ack);
            emit(mAckReceived(mission_ack));
        break;
        case 62:
            mavlink_nav_controller_output_t nav;
            mavlink_msg_nav_controller_output_decode(&msg, &nav);
            emit(navReceived(nav));
        break;
        case 73:
            mavlink_mission_item_int_t mission_item;
            mavlink_msg_mission_item_int_decode(&msg, &mission_item);
            emit(missionItemReceived(mission_item));
        case 74:
            mavlink_vfr_hud_t vfr_hud;
            mavlink_msg_vfr_hud_decode(&msg, &vfr_hud);
            emit(vfrHudReceived(vfr_hud));
        break;
        case 77:
            qDebug() << "ACK";
            mavlink_command_ack_t cmdack;
            mavlink_msg_command_ack_decode(&msg, &cmdack);
            parseCmdAck(cmdack);
            qDebug() << "CMD: " << cmdack.command << " RESULT: " << cmdack.result;
        break;
        case 87:
            mavlink_position_target_global_int_t pos_target_global;
            mavlink_msg_position_target_global_int_decode(&msg, &pos_target_global);
            // Vx-z data -> 0
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
        case 253:
            mavlink_statustext_t stattext;
            mavlink_msg_statustext_decode(&msg, &stattext);
            emit(statTextReceived(stattext));
        break;
        default:
//            qDebug() << "Message not supported";
//            qDebug() << msg.msgid;
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
