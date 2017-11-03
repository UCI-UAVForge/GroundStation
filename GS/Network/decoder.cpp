#include "decoder.h"
#include <QDebug>
Decoder::Decoder(QObject *parent) : QObject(parent){}

bool Decoder::setLink(Link * l) {
    link = l;
    return connect(link, &Link::messageReceived,  this, &Decoder::parseMessage);

}

void Decoder::parseMessage(mavlink_message_t msg) {
    qDebug() << msg.msgid;
    switch(msg.msgid) {
        case 24:
            emit(gpsMsgReceived(parseGPS(msg)));
            break;
        default:
            qDebug() << "Message not supported";
            break;
    }
}

mavlink_gps_raw_int_t Decoder::parseGPS(mavlink_message_t msg){
    mavlink_gps_raw_int_t gps;
    mavlink_msg_gps_raw_int_decode(&msg, &gps);
    return gps;
}
