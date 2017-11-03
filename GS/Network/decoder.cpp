#include "decoder.h"
#include <QDebug>
Decoder::Decoder(QObject *parent) : QObject(parent){}

bool Decoder::setLink(Link * l) {
    link = l;
    return connect(link, &Link::messageReceived,  this, &Decoder::parseMessage);
}

void Decoder::parseMessage(mavlink_message_t msg) {
    switch(msg.msgid) {
        case 1:
            mavlink_sys_status_t status;
            mavlink_msg_sys_status_decode(&msg , &status);
            emit(statusReceived(status));
            break;
        case 24:
            mavlink_gps_raw_int_t gps;
            mavlink_msg_gps_raw_int_decode(&msg, &gps);
            emit(gpsReceived(gps));
            break;
        case 30:
            mavlink_attitude_t att;
            mavlink_msg_attitude_decode(&msg, &att);
            emit(attReceived(att));
            break;
        default:
            qDebug() << "Message not supported";
            break;
    }
}
