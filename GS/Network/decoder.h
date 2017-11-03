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
    mavlink_sys_status_t parseStatus(mavlink_message_t msg);
    mavlink_system_time_t parseSysTime(mavlink_message_t msg);


signals:
    void gpsReceived(mavlink_gps_raw_int_t gps);
    void infoReceived(mavlink_field_info_t info);
    void statusReceived(mavlink_sys_status_t status);
    void sysTimeReceived(mavlink_system_time_t sysTime);
    void attReceived(mavlink_attitude_t att);

public slots:
    void parseMessage(mavlink_message_t);
};

#endif // DECODER_H
