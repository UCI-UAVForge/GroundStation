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

void Encoder::sendMissionCount(int count) {
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
    qDebug() << seq << "," << cmd << "," << curr;
    mavlink_msg_mission_item_pack(SYS, COM, &msg, 1, 0, seq, 3, cmd, curr, 1, params[0],
                                  params[1], params[2], params[3], params[4], params[5], params[6]);
    link->sendData(msg);
}

