#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include "link.h"

class Decoder : public QObject
{
    Q_OBJECT
public:
    Link * link;
    explicit Decoder(QObject *parent = nullptr);

    bool setLink(Link * l);
    mavlink_gps_raw_int_t parseGPS(mavlink_message_t msg);


signals:
    void gpsMsgReceived(mavlink_gps_raw_int_t gps);
    void infoMsgReceived(mavlink_field_info_t info);

public slots:
    void parseMessage(mavlink_message_t);
};

#endif // DECODER_H
