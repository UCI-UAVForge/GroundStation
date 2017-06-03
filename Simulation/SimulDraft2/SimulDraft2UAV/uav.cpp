#include "uav.h"

uav::uav(QWidget *parent)
{
    //Initialize UAV properties
    uavOn = true;
    uavWaypointsReady = false;
    uavFlying = false;
    uavFlyingHome = false;
    batteryStatus.battery_remaining = 100;
    storageStatus.total_capacity = 20;
    storageStatus.used_capacity = 0;
    telemSeqNumber = 0;
    uavStatus.lat = 33.6454;
    uavStatus.lon = -117.8426;
    homePoint.lat = uavStatus.lat;
    homePoint.lon = uavStatus.lon;
    latLngSpd = .02;

    //Connect udpLink
    connect(&udpLink, SIGNAL(messageReceived(mavlink_message_t)), this, SLOT(parseCommand(mavlink_message_t)));
    sendFlightInfo();
    QTextStream(stdout) << "Link created. Listening for packets.." << endl;

    //Create timer, send telemetry packets every 200ms
    timer = new QTimer(this);
    timeSinceBoot  = new QTime();
    connect(timer, SIGNAL(timeout()), this, SLOT(sendCurrentTelem()));
    timer->start(200);
    timeSinceBoot->start();
}


uint16_t uav::parseCommand(mavlink_message_t msg) {
    mavlink_command_long_t cmd;
    mavlink_msg_command_long_decode(&msg, &cmd);
    uint8_t result = MAV_RESULT_FAILED;
    switch(cmd.command) {
        case MAV_CMD_REQUEST_FLIGHT_INFORMATION:
            //Send flight information
            if(uavOn)
                sendFlightInfo();
        break;
        case MAV_CMD_NAV_WAYPOINT:
            //Add new waypoint
            if (uavOn && storageStatus.used_capacity < storageStatus.total_capacity) {
                Waypoint wp;
                wp.lat = cmd.param5;
                wp.lon = cmd.param6;
                wp.alt = cmd.param7;
                uavWaypointsReady = true;
                ++storageStatus.used_capacity;
                QTextStream(stdout) << "Adding new waypoint: " << wp.lat << ", " << wp.lon << endl;
                pointOfInterest.enqueue(wp);
                result = MAV_RESULT_ACCEPTED;
            }
            else {
                QTextStream(stdout) << "Capacity reached/UAV isn't on";
            }
        break;
        case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            //Return home
            pointOfInterest.clear();
            pointOfInterest.enqueue(homePoint);
            QTextStream(stdout) << "Returning Home: (" << homePoint.lat << "," << homePoint.lon << ")" << endl;
        break;
        case MAV_CMD_DO_SET_HOME:
            //Set UAV home location
            homePoint.lat = cmd.param5;
            homePoint.lon = cmd.param6;
            result = MAV_RESULT_ACCEPTED;
            QTextStream(stdout) << "Set Home: (" << homePoint.lat << "," << homePoint.lon << ")" << endl;
        break;
        case MAV_CMD_DO_ENGINE_CONTROL:
            //Start or shut down UAV engine
            if(cmd.param1 == 0 && uavOn) {
                QTextStream(stdout) << "SHUTTING DOWN" << endl;
                shutdownAction = true;
                uavOn = false;
                timer->stop();
            }
            else if(cmd.param1 == 1 && !uavOn) {
                QTextStream(stdout) << "STARTING... "<< endl;
                uavOn = true;
                uavFlying = true;
                receivedInfoPacketReq = true;
                timer->start(200);
            }
            result = MAV_RESULT_ACCEPTED;
        break;
    }
    sendCmdAck(cmd.command, result);
    return cmd.command;
}


void uav::sendFlightInfo() {
    mavlink_message_t msg;
    mavlink_msg_flight_information_pack(SYSID, COMPID, &msg,
                                        flightInfo.time_boot_ms,
                                        flightInfo.arming_time_utc,
                                        flightInfo.takeoff_time_utc,
                                        flightInfo.flight_uuid);
    udpLink.sendMAVLinkMsg(msg);
    QTextStream(stdout) << "Info Packet Sent" << endl;
}

void uav::sendCmdAck(uint16_t commandID, uint8_t result) {
    mavlink_message_t ackMsg;
    mavlink_msg_command_ack_pack(SYSID, COMPID, &ackMsg, commandID, result);
    udpLink.sendMAVLinkMsg(ackMsg);
    QTextStream(stdout) << "Ack Packet Sent" << endl;
}

void uav::sendCurrentTelem() {
    updateUAVTelem();
    mavlink_message_t msg;
    mavlink_msg_global_position_int_pack(SYSID, COMPID, &msg, timeSinceBoot->elapsed(),
                                         uavStatus.lat, uavStatus.lon, uavStatus.alt,
                                         uavStatus.alt, 10, 10, 10, UINT16_MAX);
    udpLink.sendMAVLinkMsg(msg);
    telemSeqNumber++;
    QTextStream(stdout) << "Telem Packet #" << telemSeqNumber << " Sent. " << "Time :" << timeSinceBoot->elapsed()
                        << " UAV(Lat,Lon): " << "(" << uavStatus.lat << ", " << uavStatus.lon << ")" << endl;
}

void uav::sendSimState() {
    mavlink_message_t msg;
    mavlink_msg_sim_state_pack(1, 190, &msg, uavStatus.q1,
                               uavStatus.q2, uavStatus.q3,
                               uavStatus.q4, uavStatus.roll,
                               uavStatus.pitch, uavStatus.yaw,
                               uavStatus.xacc, uavStatus.yacc,
                               uavStatus.zacc, uavStatus.xgyro,
                               uavStatus.ygyro, uavStatus.zgyro,
                               uavStatus.lat, uavStatus.lon,
                               uavStatus.alt, uavStatus.std_dev_horz,
                               uavStatus.std_dev_vert, uavStatus.vn,
                               uavStatus.ve, uavStatus.vd);
    udpLink.sendMAVLinkMsg(msg);
    QTextStream(stdout) << "Simulation State Sent" << endl;
}

void uav::updateUAVTelem() {
    //Create simulated telemetry info
    uavStatus.vn = qrand() % 30 + 80;
    uavStatus.vd = qrand() % 30 + 80;
    uavStatus.ve = qrand() % 30 + 80;
    uavStatus.alt = qrand() % 75 + 150;

    //If no waypoints, keep listening
    if (pointOfInterest.empty()) {
        return;
    }

    Waypoint nextPoint = pointOfInterest.front();

    //If uav is within a certain range of nextPoint, uav goes to nextPoint.
    //Else it moves towards nextPoint by latLngSpd
    if (uavStatus.lat + latLngSpd >= nextPoint.lat && uavStatus.lat - latLngSpd <= nextPoint.lat)
        uavStatus.lat = nextPoint.lat;
    else if (uavStatus.lat > nextPoint.lat)
        uavStatus.lat -= latLngSpd;
    else if (uavStatus.lat < nextPoint.lat)
        uavStatus.lat += latLngSpd;

    if (uavStatus.lon + latLngSpd >= nextPoint.lon && uavStatus.lon - latLngSpd <= nextPoint.lon)
        uavStatus.lon = nextPoint.lon;
    else if (uavStatus.lon > nextPoint.lon)
        uavStatus.lon -= latLngSpd;
    else if (uavStatus.lon < nextPoint.lon)
        uavStatus.lon += latLngSpd;

    //If uav is at the nextPoint, send packet telling GS that it has reached it's destination
    if (uavStatus.lon == nextPoint.lon && uavStatus.lat == nextPoint.lat) {
        pointOfInterest.dequeue();
        --storageStatus.used_capacity;
        if(!uavFlyingHome && !pointOfInterest.empty()) {
            QTextStream(stdout) << "Destination reached: (" << nextPoint.lat << ", " << nextPoint.lon << "). Sent waypoint packet" << endl;
            QTextStream(stdout) << "Next destination: (" << pointOfInterest.front().lat << ", " << pointOfInterest.front().lon << ")." << endl;
        }
        else if (uavFlyingHome && pointOfInterest.empty())  {
            QTextStream(stdout) << "Home reached. Sent waypoint packet" << endl;
        }
    }

    //After popping, check again whether queue is empty.
    //If queue is empty, go home. If already home, stop UAV.
    if (pointOfInterest.empty()) {
        if (!uavFlyingHome) {
            QTextStream(stdout) << "Destination reached: (" << nextPoint.lat << ", " << nextPoint.lon << "). Sent waypoint packet" << endl;
            QTextStream(stdout) << "Nowhere else to go... Heading Home." << endl;
            uavFlyingHome = true;
            pointOfInterest.enqueue(homePoint);
            ++storageStatus.used_capacity;
        }
        else {
            QTextStream(stdout) << "UAV Stopped";
            timer->stop();
            uavFlying = false;
            uavWaypointsReady = false;
        }
    }
}
