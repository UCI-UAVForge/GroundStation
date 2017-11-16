#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include "udplink.h"
#include "tcplink.h"

class Decoder : public QObject
{
    Q_OBJECT
public:
    UdpLink * link;
    explicit Decoder(QObject *parent = nullptr);

    bool setLink(UdpLink * l);
    bool setLink(TcpLink * l);
    void parseCmdAck(mavlink_command_ack_t);


signals:
    void heartbeatReceived(mavlink_heartbeat_t heartbeat);
    void gpsReceived(mavlink_gps_raw_int_t gps);
    void infoReceived(mavlink_field_info_t info);
    void statusReceived(mavlink_sys_status_t status);
    void sysTimeReceived(mavlink_system_time_t sysTime);
    void attReceived(mavlink_attitude_t att);
    void batteryReceived(mavlink_battery_status_t battery);
    void windReceived(mavlink_wind_t wind);
    void pressureReceived(mavlink_scaled_pressure_t pressure);
    void navReceived(mavlink_nav_controller_output_t nav);

    void armSuccess();
    void armFailed();
    void modeChanged();

public slots:
    void parseMessage(mavlink_message_t);
};

#endif // DECODER_H
