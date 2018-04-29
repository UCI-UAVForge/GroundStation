#include "encoder.h"
#include <QDebug>
Encoder::Encoder(QObject *parent) : QObject(parent){
    //Waypoint::WP* waypoints = new Waypoint::WP[missions->length()];
}
void Encoder::setLink(Link *l) {
    link = l;
}

void Encoder::sendArm(bool armed) {
    mavlink_message_t msg;
    mavlink_msg_command_long_pack(SYS, COM, &msg, 1, 0, 400, 1, !armed, 0, 0, 0, 0, 0, 0);
    link->sendData(msg);
}

void Encoder::sendMode(int mode){
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS,  COM , &msg, 1, 1, mode);
    link->sendData(msg);
}

void Encoder::sendMissionCount(uint16_t count) {
    mavlink_message_t msg;
    mavlink_msg_mission_count_pack(SYS, COM, &msg, 1, 0, count);
    link->sendData(msg);
}

void Encoder::sendMissionItem(Waypoint::WP waypoint) {
    mavlink_message_t msg;
    mavlink_msg_mission_item_pack(SYS, COM, &msg, 1, 0, waypoint.id, 3, waypoint.command,
                                  waypoint.current, waypoint.autocontinue, waypoint.param1,
                                  waypoint.param2, waypoint.param3, waypoint.param4, waypoint.x,
                                  waypoint.y, waypoint.z);
    link->sendData(msg);
}

void Encoder::sendClearAll() {
    mavlink_message_t msg;
    mavlink_msg_mission_clear_all_pack(SYS, COM, &msg, 1, 0);
    link->sendData(msg);
}

void Encoder::sendMissionRequestList() {
    mavlink_message_t msg;
    mavlink_msg_mission_request_list_pack(SYS, COM, &msg, 1, 0);
    link->sendData(msg);
}

void Encoder::sendMissionRequest(uint16_t i) {
    mavlink_message_t msg;
    mavlink_msg_mission_request_pack(SYS, COM, &msg, 1, 0, i);
    link->sendData(msg);
}

void Encoder::sendMissionACK(uint16_t type) {
    mavlink_message_t msg;
    mavlink_msg_mission_ack_pack(SYS, COM, &msg, 1, 0, type);
    link->sendData(msg);
}


void Encoder::sendMissionSetCurrent(uint16_t seq) {
    mavlink_message_t msg;
    mavlink_msg_mission_set_current_pack(SYS, COM, &msg, 1, 0, seq);
    link->sendData(msg);
}

void Encoder::sendSetServo(int pwm) {
    mavlink_message_t msg;
    mavlink_msg_command_long_pack(SYS, COM, &msg, 1, 0, 183, 1, 6, pwm, 3, 3, 0, 0, 0);
    link->sendData(msg);
}
