#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include "link.h"


class Decoder : public QObject
{
    Q_OBJECT
public:
    explicit Decoder(QObject *parent = nullptr);
    Link * link;
    bool setLink(Link * l);
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
    void vfrHudReceived(mavlink_vfr_hud_t vfr);
    void localPositionReceived(mavlink_local_position_ned_t l_pos);
    void statTextReceived(mavlink_statustext_t);
    void mrequestReceived(mavlink_mission_request_t mrequest);
    void mAckReceived(mavlink_mission_ack_t mission_ack);
    void mClearAllReceived(mavlink_mission_clear_all_t mission_clear_all);
    void missionCountReceived(mavlink_mission_count_t mcount);
    void missionItemReceived(mavlink_mission_item_t mission_item);
    void missionCurrentReceived(mavlink_mission_current_t mission_current);
    void gps_intReceived(mavlink_global_position_int_t gps_int);
    void armReceived(bool armState);

    void armSuccess();
    void armFailed();
    void modeChanged();

public slots:
    void parseMessage(mavlink_message_t);
};

#endif // DECODER_H
