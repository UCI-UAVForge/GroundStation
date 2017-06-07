#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T13:10:01
#
#-------------------------------------------------

QT       += core \
            gui \
            multimedia \
            multimediawidgets \
            network
QT       += svg
QT       += sql
QT       += webengine
QT       += webenginewidgets
QT       += webchannel
QT       += websockets
QT       += widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

#CONFIG += console

CONFIG += c++11
#win32{
#    LIBS += -lws2_32
#}
macx {
    QMAKE_MAC_SDK = macosx10.12
}
TARGET = UAV-Forge-New
TEMPLATE = app

#PRECOMPILED_HEADER = qcustomplot.h

SOURCES += main.cpp\
    tablemodel.cpp \
    qcomboboxdelegate.cpp \
    gsserver.cpp \
    gscontrolpanel.cpp \
    qcustomplot.cpp\
    networklistener.cpp \
    messagebox.cpp \
    ActionPacket.cpp \
    InfoPacket.cpp \
    TelemetryPacket.cpp \
    Packet.cpp \
    #digitalclock.cpp \
    mapvalidator.cpp \
    serverqueue.cpp \
    mission.cpp \
    flightpath.cpp \
    qttabtest.cpp \
    mainmdidisplay.cpp \
    missionplanningwindow.cpp \
    dbmanager.cpp \
    mapwidget.cpp \
    websocketclientwrapper.cpp \
    websockettransport.cpp \
    tablewidget.cpp \
    statuswidget.cpp \
    graphwidget.cpp \
    timerwidget.cpp \
    missionstatuswindow.cpp \
    mavlinkdecoder.cpp \
    receiver.cpp \
    sender.cpp \
    dataobjects.cpp

HEADERS  += tablemodel.h \
    qcomboboxdelegate.h \
    net.h \
    gscontrolpanel.h \
    gsserver.h \
    qcustomplot.h\
    networklistener.h \
    messagebox.h \
    actionpacket.h \
    infopacket.h \
    telemetrypacket.h \
    ackpacket.h \
    packet.h \
    #digitalclock.h \
    mapvalidator.h \
    serverqueue.h \
    mission.h \
    flightpath.h \
    qttabtest.h \
    mainmdidisplay.h \
    missionplanningwindow.h \
    dbmanager.h \
    mapwidget.h \
    websocketclientwrapper.h \
    websockettransport.h \
    tablewidget.h \
    graphwidget.h \
    statuswidget.h \
    timerwidget.h \
    common/common/common.h \
    common/common/mavlink.h \
    common/common/mavlink_msg_actuator_control_target.h \
    common/common/mavlink_msg_adsb_vehicle.h \
    common/common/mavlink_msg_altitude.h \
    common/common/mavlink_msg_att_pos_mocap.h \
    common/common/mavlink_msg_attitude.h \
    common/common/mavlink_msg_attitude_quaternion.h \
    common/common/mavlink_msg_attitude_quaternion_cov.h \
    common/common/mavlink_msg_attitude_target.h \
    common/common/mavlink_msg_auth_key.h \
    common/common/mavlink_msg_autopilot_version.h \
    common/common/mavlink_msg_battery_status.h \
    common/common/mavlink_msg_camera_trigger.h \
    common/common/mavlink_msg_change_operator_control.h \
    common/common/mavlink_msg_change_operator_control_ack.h \
    common/common/mavlink_msg_collision.h \
    common/common/mavlink_msg_command_ack.h \
    common/common/mavlink_msg_command_int.h \
    common/common/mavlink_msg_command_long.h \
    common/common/mavlink_msg_control_system_state.h \
    common/common/mavlink_msg_data_stream.h \
    common/common/mavlink_msg_data_transmission_handshake.h \
    common/common/mavlink_msg_debug.h \
    common/common/mavlink_msg_debug_vect.h \
    common/common/mavlink_msg_distance_sensor.h \
    common/common/mavlink_msg_encapsulated_data.h \
    common/common/mavlink_msg_estimator_status.h \
    common/common/mavlink_msg_extended_sys_state.h \
    common/common/mavlink_msg_file_transfer_protocol.h \
    common/common/mavlink_msg_follow_target.h \
    common/common/mavlink_msg_global_position_int.h \
    common/common/mavlink_msg_global_position_int_cov.h \
    common/common/mavlink_msg_global_vision_position_estimate.h \
    common/common/mavlink_msg_gps_global_origin.h \
    common/common/mavlink_msg_gps_inject_data.h \
    common/common/mavlink_msg_gps_input.h \
    common/common/mavlink_msg_gps_raw_int.h \
    common/common/mavlink_msg_gps_rtcm_data.h \
    common/common/mavlink_msg_gps_rtk.h \
    common/common/mavlink_msg_gps_status.h \
    common/common/mavlink_msg_gps2_raw.h \
    common/common/mavlink_msg_gps2_rtk.h \
    common/common/mavlink_msg_heartbeat.h \
    common/common/mavlink_msg_high_latency.h \
    common/common/mavlink_msg_highres_imu.h \
    common/common/mavlink_msg_hil_actuator_controls.h \
    common/common/mavlink_msg_hil_controls.h \
    common/common/mavlink_msg_hil_gps.h \
    common/common/mavlink_msg_hil_optical_flow.h \
    common/common/mavlink_msg_hil_rc_inputs_raw.h \
    common/common/mavlink_msg_hil_sensor.h \
    common/common/mavlink_msg_hil_state.h \
    common/common/mavlink_msg_hil_state_quaternion.h \
    common/common/mavlink_msg_home_position.h \
    common/common/mavlink_msg_landing_target.h \
    common/common/mavlink_msg_local_position_ned.h \
    common/common/mavlink_msg_local_position_ned_cov.h \
    common/common/mavlink_msg_local_position_ned_system_global_offset.h \
    common/common/mavlink_msg_log_data.h \
    common/common/mavlink_msg_log_entry.h \
    common/common/mavlink_msg_log_erase.h \
    common/common/mavlink_msg_log_request_data.h \
    common/common/mavlink_msg_log_request_end.h \
    common/common/mavlink_msg_log_request_list.h \
    common/common/mavlink_msg_manual_control.h \
    common/common/mavlink_msg_manual_setpoint.h \
    common/common/mavlink_msg_memory_vect.h \
    common/common/mavlink_msg_message_interval.h \
    common/common/mavlink_msg_mission_ack.h \
    common/common/mavlink_msg_mission_clear_all.h \
    common/common/mavlink_msg_mission_count.h \
    common/common/mavlink_msg_mission_current.h \
    common/common/mavlink_msg_mission_item.h \
    common/common/mavlink_msg_mission_item_int.h \
    common/common/mavlink_msg_mission_item_reached.h \
    common/common/mavlink_msg_mission_request.h \
    common/common/mavlink_msg_mission_request_int.h \
    common/common/mavlink_msg_mission_request_list.h \
    common/common/mavlink_msg_mission_request_partial_list.h \
    common/common/mavlink_msg_mission_set_current.h \
    common/common/mavlink_msg_mission_write_partial_list.h \
    common/common/mavlink_msg_named_value_float.h \
    common/common/mavlink_msg_named_value_int.h \
    common/common/mavlink_msg_nav_controller_output.h \
    common/common/mavlink_msg_optical_flow.h \
    common/common/mavlink_msg_optical_flow_rad.h \
    common/common/mavlink_msg_param_map_rc.h \
    common/common/mavlink_msg_param_request_list.h \
    common/common/mavlink_msg_param_request_read.h \
    common/common/mavlink_msg_param_set.h \
    common/common/mavlink_msg_param_value.h \
    common/common/mavlink_msg_ping.h \
    common/common/mavlink_msg_position_target_global_int.h \
    common/common/mavlink_msg_position_target_local_ned.h \
    common/common/mavlink_msg_power_status.h \
    common/common/mavlink_msg_radio_status.h \
    common/common/mavlink_msg_raw_imu.h \
    common/common/mavlink_msg_raw_pressure.h \
    common/common/mavlink_msg_rc_channels.h \
    common/common/mavlink_msg_rc_channels_override.h \
    common/common/mavlink_msg_rc_channels_raw.h \
    common/common/mavlink_msg_rc_channels_scaled.h \
    common/common/mavlink_msg_request_data_stream.h \
    common/common/mavlink_msg_resource_request.h \
    common/common/mavlink_msg_safety_allowed_area.h \
    common/common/mavlink_msg_safety_set_allowed_area.h \
    common/common/mavlink_msg_scaled_imu.h \
    common/common/mavlink_msg_scaled_imu2.h \
    common/common/mavlink_msg_scaled_imu3.h \
    common/common/mavlink_msg_scaled_pressure.h \
    common/common/mavlink_msg_scaled_pressure2.h \
    common/common/mavlink_msg_scaled_pressure3.h \
    common/common/mavlink_msg_serial_control.h \
    common/common/mavlink_msg_servo_output_raw.h \
    common/common/mavlink_msg_set_actuator_control_target.h \
    common/common/mavlink_msg_set_attitude_target.h \
    common/common/mavlink_msg_set_gps_global_origin.h \
    common/common/mavlink_msg_set_home_position.h \
    common/common/mavlink_msg_set_mode.h \
    common/common/mavlink_msg_set_position_target_global_int.h \
    common/common/mavlink_msg_set_position_target_local_ned.h \
    common/common/mavlink_msg_sim_state.h \
    common/common/mavlink_msg_statustext.h \
    common/common/mavlink_msg_sys_status.h \
    common/common/mavlink_msg_system_time.h \
    common/common/mavlink_msg_terrain_check.h \
    common/common/mavlink_msg_terrain_data.h \
    common/common/mavlink_msg_terrain_report.h \
    common/common/mavlink_msg_terrain_request.h \
    common/common/mavlink_msg_timesync.h \
    common/common/mavlink_msg_v2_extension.h \
    common/common/mavlink_msg_vfr_hud.h \
    common/common/mavlink_msg_vibration.h \
    common/common/mavlink_msg_vicon_position_estimate.h \
    common/common/mavlink_msg_vision_position_estimate.h \
    common/common/mavlink_msg_vision_speed_estimate.h \
    common/common/mavlink_msg_wind_cov.h \
    common/common/testsuite.h \
    common/common/version.h \
    common/mavlink_conversions.h \
    common/mavlink_helpers.h \
    common/mavlink_types.h \
    common/checksum.h \
    common/protocol.h \
    common/mavlink_sha256.h \
    common/mavlink_get_info.h \
    mavlinkdecoder.h \
    receiver.h \
    sender.h \
    missionstatuswindow.h \
    dataobjects.h

FORMS    += gscontrolpanel.ui \
    qttabtest.ui \
    mainmdidisplay.ui \
    graphwidget.ui\
    missionstatuswindow.ui

OTHER_FILES +=

RESOURCES += \
    Resources.qrc
