#include "decoder.h"
#include <QDebug>
Decoder::Decoder(QObject *parent) : QObject(parent){}

bool Decoder::setLink(Link * l) {
    return connect(l, &Link::messageReceived, this, &Decoder::parseMessage);
}

void Decoder::parseMessage(mavlink_message_t msg) {
    switch(msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT: //0
            mavlink_heartbeat_t heartbeat;
            mavlink_msg_heartbeat_decode(&msg, &heartbeat);
            switch(heartbeat.base_mode) {
                case 81: case 89:
                    emit(armReceived(false));     //unarmed
                break;
                case 209: case 217:
                    emit(armReceived(true));      //armed
                break;
            }
            emit(heartbeatReceived(heartbeat));
//            qDebug() << "decoder.cpp:: heartbeat.custom_mode->" << heartbeat.custom_mode;
        break;
        case MAVLINK_MSG_ID_SYS_STATUS: //1
            mavlink_sys_status_t status;
            mavlink_msg_sys_status_decode(&msg , &status);
            emit(statusReceived(status));
        break;
        case MAVLINK_MSG_ID_SYSTEM_TIME: //2
            mavlink_system_time_t systime;
            mavlink_msg_system_time_decode(&msg, &systime);
        break;
        case MAVLINK_MSG_ID_PARAM_VALUE: //22
            mavlink_param_value_t param_value;
            mavlink_msg_param_value_decode(&msg, &param_value);
//            emit(param_valueReceived(param_value));
         /*allows the recipient to keep track of received parameters
         and allows him to re-request missing parameters after
         a loss or timeout.*/
        break;
        case MAVLINK_MSG_ID_GPS_RAW_INT: //24
            mavlink_gps_raw_int_t gps;
            mavlink_msg_gps_raw_int_decode(&msg, &gps);
            emit(gpsReceived(gps));
        break;
        case MAVLINK_MSG_ID_RAW_IMU: //27
            mavlink_raw_imu_t raw_imu;
            mavlink_msg_raw_imu_decode(&msg, &raw_imu);
//            emit(raw_imuReceived(raw_imu));
        break;
        case MAVLINK_MSG_ID_SCALED_PRESSURE: //29
            mavlink_scaled_pressure_t pressure;
            mavlink_msg_scaled_pressure_decode(&msg, &pressure);
            emit(pressureReceived(pressure));
        break;
        case MAVLINK_MSG_ID_ATTITUDE: //30
            mavlink_attitude_t att;
            mavlink_msg_attitude_decode(&msg, &att);
            emit(attReceived(att));
        break;
        case MAVLINK_MSG_ID_LOCAL_POSITION_NED: //32
            mavlink_local_position_ned_t l_pos;
            mavlink_msg_local_position_ned_decode(&msg, &l_pos);
            emit(localPositionReceived(l_pos));
        break;
        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: //33
            mavlink_global_position_int_t gps_int;
            mavlink_msg_global_position_int_decode(&msg, &gps_int);
            emit(gps_intReceived(gps_int));
        break;
        case MAVLINK_MSG_ID_RC_CHANNELS_RAW: //35
            mavlink_rc_channels_raw_t rc_channels_raw;
            mavlink_msg_rc_channels_raw_decode(&msg, &rc_channels_raw);
//            emit(rc_channels_rawReceived(rc_channels_raw));
        break;
        case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW: //36
            mavlink_servo_output_raw_t servo_output;
            mavlink_msg_servo_output_raw_decode(&msg, &servo_output);
//            emit(servo_outputReceived(servo_output));
        break;
        case MAVLINK_MSG_ID_MISSION_ITEM: //39
            mavlink_mission_item_t mission_item;
            mavlink_msg_mission_item_decode(&msg, &mission_item);
            emit(missionItemReceived(mission_item));
        break;
        case MAVLINK_MSG_ID_MISSION_REQUEST: //40
            mavlink_mission_request_t mrequest;
            mavlink_msg_mission_request_decode(&msg, &mrequest);
            emit (mrequestReceived(mrequest));
        case MAVLINK_MSG_ID_MISSION_CURRENT: //42
            mavlink_mission_current_t mcurrent;
            mavlink_msg_mission_current_decode(&msg, &mcurrent);
            emit(missionCurrentReceived(mcurrent));
        break;
        case MAVLINK_MSG_ID_MISSION_COUNT: //44
            mavlink_mission_count_t mcount;
            mavlink_msg_mission_count_decode(&msg, &mcount);
            emit(missionCountReceived(mcount));
        break;
        case MAVLINK_MSG_ID_MISSION_ACK: //47
            mavlink_mission_ack_t mission_ack;
            mavlink_msg_mission_ack_decode(&msg, &mission_ack);
            emit(mAckReceived(mission_ack));
        break;
        case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT: //62
            mavlink_nav_controller_output_t nav;
            mavlink_msg_nav_controller_output_decode(&msg, &nav);
            emit(navReceived(nav));
        break;
        case MAVLINK_MSG_ID_RC_CHANNELS: //65
            mavlink_rc_channels_t rc_channels;
            mavlink_msg_rc_channels_decode(&msg, &rc_channels);
//            emit(rc_channelsReceived(rc_channels));
        break;
        case MAVLINK_MSG_ID_VFR_HUD: //74
            mavlink_vfr_hud_t vfr_hud;
            mavlink_msg_vfr_hud_decode(&msg, &vfr_hud);
            emit(vfrHudReceived(vfr_hud));
        break;
        case MAVLINK_MSG_ID_COMMAND_ACK: //77
            mavlink_command_ack_t cmdack;
            mavlink_msg_command_ack_decode(&msg, &cmdack);
            parseCmdAck(cmdack);
            qDebug() << "decoder.cpp:: CMD: " << cmdack.command << " RESULT: " << cmdack.result;
        break;
        case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT: //87
            mavlink_position_target_global_int_t pos_target_global;
            mavlink_msg_position_target_global_int_decode(&msg, &pos_target_global);
//            emit(pos_target_globalReceived(pos_target_global));
            // Vx-z data -> 0
        break;
        case MAVLINK_MSG_ID_SCALED_IMU2: //116
            mavlink_scaled_imu2_t scaled_imu2;
            mavlink_msg_scaled_imu2_decode(&msg, &scaled_imu2);
//            emit(scaled_imu2Received(scaled_imu2));
        break;
        case MAVLINK_MSG_ID_POWER_STATUS: //125
            mavlink_power_status_t power_status;
            mavlink_msg_power_status_decode(&msg, &power_status);
//            emit(power_statusReceived(power_status));
        break;
        case MAVLINK_MSG_ID_SCALED_IMU3: //129
            mavlink_scaled_imu3_t scaled_imu3;
            mavlink_msg_scaled_imu3_decode(&msg, &scaled_imu3);
//            emit(scaled_imu3Received(scaled_imu3));
        break;
        case MAVLINK_MSG_ID_TERRAIN_REQUEST: //133
            mavlink_terrain_request_t terrain_request;
            mavlink_msg_terrain_request_decode(&msg, &terrain_request);
//            emit(terrain_requestReceived(terrain_request));
        break;
        case MAVLINK_MSG_ID_TERRAIN_REPORT: //136
            mavlink_terrain_report_t terrain_report;
            mavlink_msg_terrain_report_decode(&msg, &terrain_report);
//            emit(terrain_reportReceived(terrain_report));
        break;
        case MAVLINK_MSG_ID_SCALED_PRESSURE2: //137
            mavlink_scaled_pressure2_t scaled_pressure2;
            mavlink_msg_scaled_pressure2_decode(&msg, &scaled_pressure2);
//            emit(scaled_pressure2Received(scaled_pressure2));
        break;
        case MAVLINK_MSG_ID_SENSOR_OFFSETS: //150
            mavlink_sensor_offsets_t sensor_offsets;
            mavlink_msg_sensor_offsets_decode(&msg, &sensor_offsets);
//            emit(sensor_offsetsReceived(sensor_offsets));
        break;
        case MAVLINK_MSG_ID_MEMINFO: //152
            mavlink_meminfo_t meminfo;
            mavlink_msg_meminfo_decode(&msg, &meminfo);
//            emit(meminfoReceived(meminfo));
        break;
        case MAVLINK_MSG_ID_AHRS: //163
            mavlink_ahrs_t ahrs;
            mavlink_msg_ahrs_decode(&msg, &ahrs);
//            emit(ahrsReceived(ahrs));
        break;
        case MAVLINK_MSG_ID_HWSTATUS: //165
            mavlink_hwstatus_t hwstatus;
            mavlink_msg_hwstatus_decode(&msg, &hwstatus);
//            emit(hwstatusReceived(hwstatus));
        break;
        case MAVLINK_MSG_ID_WIND: //168
            mavlink_wind_t wind;
            mavlink_msg_wind_decode(&msg, &wind);
            emit(windReceived(wind));
        break;
        case MAVLINK_MSG_ID_AHRS2: //178
            mavlink_ahrs2_t ahrs2;
            mavlink_msg_ahrs2_decode(&msg, &ahrs2);
//            emit(ahrs2Received(ahrs2));
        break;
        case MAVLINK_MSG_ID_AHRS3: //182
            mavlink_ahrs3_t ahrs3;
            mavlink_msg_ahrs3_decode(&msg, &ahrs3);
//            emit(ahrs3Received(ahrs3));
        break;
        case MAVLINK_MSG_ID_EKF_STATUS_REPORT: //193
            mavlink_ekf_status_report_t ekf_status_report;
            mavlink_msg_ekf_status_report_decode(&msg, &ekf_status_report);
//            emit(ekf_status_reportReceived(ekf_status_report));
        // EKF status messaage including flags and variances
        break;
        case MAVLINK_MSG_ID_VIBRATION: //241
            mavlink_vibration_t vibration;
            mavlink_msg_vibration_decode(&msg, &vibration);
//            emit(vibrationReceived(vibration));
        break;
        case MAVLINK_MSG_ID_HOME_POSITION: //242
            mavlink_home_position_t home_position;
            mavlink_msg_home_position_decode(&msg, &home_position);
//            emit(home_positionReceived(home_position));
        break;
        case MAVLINK_MSG_ID_STATUSTEXT: //253
            mavlink_statustext_t stattext;
            mavlink_msg_statustext_decode(&msg, &stattext);
            emit(statTextReceived(stattext));
        break;
        case MAVLINK_MSG_ID_HIGHRES_IMU:
            mavlink_highres_imu_t hrimu;
            mavlink_msg_highres_imu_decode(&msg, &hrimu);
            emit(hrimu);
        break;
        default:
//            qDebug() << "!*** Message not supported::msgid=" << msg.msgid << "***!";
            break;
    }
}

void Decoder::parseCmdAck(mavlink_command_ack_t cmdAck) {
    switch(cmdAck.command) {
        case MAV_CMD_DO_SET_MODE:
            if(cmdAck.result == MAV_RESULT_ACCEPTED)
                emit(modeChanged());
        break;
        case MAV_CMD_COMPONENT_ARM_DISARM:
            if(cmdAck.result == MAV_RESULT_ACCEPTED)
                emit(armSuccess());
            else
                emit(armFailed());
        break;
    default:
        break;

    }
}
