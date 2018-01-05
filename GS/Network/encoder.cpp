#include "encoder.h"
#include <QDebug>
Encoder::Encoder(QObject *parent) : QObject(parent){

}
void Encoder::setLink(Link *l) {
    link = l;
}

void Encoder::sendArm(bool armed) {
    mavlink_message_t msg;
    mavlink_msg_command_long_pack(SYS, COM, &msg, 1, 0, 400, 1, !armed, 0, 0, 0, 0, 0, 0);
    link->sendData(msg);
}

void Encoder::sendSetGuided() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS,  COM , &msg, 1, 1, 15);
    link->sendData(msg);
}
void Encoder::sendSetManual() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM , &msg, 1, 1, 0);
    link->sendData(msg);
}

void Encoder::sendSetAuto() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM, &msg, 1, 1, 10);
    link->sendData(msg);
}

void Encoder::sendSetCircle() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM, &msg, 1, 1, 1);
    link->sendData(msg);
}

void Encoder::sendSetStabilize() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM, &msg, 1, 1, 2);
    link->sendData(msg);
}

void Encoder::sendSetFBWA() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM, &msg, 1, 1, 5);
    link->sendData(msg);
}

void Encoder::sendSetFBWB() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM, &msg, 1, 1, 6);
    link->sendData(msg);
}

void Encoder::sendSetCruise() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM, &msg, 1, 1, 7);
    link->sendData(msg);
}

void Encoder::sendSetRTL() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM, &msg, 1, 1, 11);
    link->sendData(msg);
}

void Encoder::sendSetLoiter() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM, &msg, 1, 1, 12);
    link->sendData(msg);
}

void Encoder::sendSetInitialising() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(SYS, COM, &msg, 1, 1, 16);
    link->sendData(msg);
}

void Encoder::sendMissionCount(uint16_t count) {
    mavlink_message_t msg;
    mavlink_msg_mission_count_pack(SYS, COM, &msg, 1, 0, count);
    link->sendData(msg);
}

void Encoder::sendMissionItem(int seq, int cmd, float params[]) {
    mavlink_message_t msg;
    int curr = 0;
    if (seq == 0) {
        curr = 1;
    }
    qDebug() << "Encoder::sendMissionItem ->" << seq << "," << cmd << "," << curr;
    mavlink_msg_mission_item_pack(SYS, COM, &msg, 1, 0, seq, 3, cmd, curr, 1, params[0],
                                  params[1], params[2], params[3], params[4], params[5], params[6]);
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
