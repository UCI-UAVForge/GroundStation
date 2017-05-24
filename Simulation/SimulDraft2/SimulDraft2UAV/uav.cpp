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
    home.latitude = uavStatus.lat;
    home.longitude = uavStatus.lon;
    latLngSpd = .02;

    //Connect udpLink
    connect(&udpLink, SIGNAL(messageReceived(mavlink_message_t)), this, SLOT(parseCommand(mavlink_message_t)));
    qDebug() << "Link created. Listening for packets..";

    //Create timer, send telemetry packets every 200ms
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendCurrentTelem()));
    timer->start(1000);


}

void uav::addWaypoint(Waypoint wp) {
    pointOfInterest.push(wp);
}

mavlink_command_long_t uav::parseCommand(mavlink_message_t msg) {
    mavlink_command_long_t cmd;
    mavlink_msg_command_long_decode(&msg, &cmd);
    switch(cmd.command) {
        case MAV_CMD_REQUEST_FLIGHT_INFORMATION:
            //Send flight information
            if(uavOn)
                sendFlightInfo();
        break;
        case MAV_CMD_NAV_WAYPOINT:
            //Add new waypoint
            if (uavOn && storageStatus.used_capacity < storageStatus.total_capacity) {
                QTextStream(stdout) << "Adding new waypoint" << endl;
                Waypoint wp;
                wp.lat = cmd.param5;
                wp.lon = cmd.param6;
                wp.alt = cmd.param7;
                uavWaypointsReady = true;
                ++storageStatus.used_capacity;
                addWaypoint(wp);
            }
            else {
                QTextStream(stdout) << "Capacity reached/UAV isn'ton";
            }
        break;
        case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            //Return home
            QTextStream(stdout) << "Returning Home: (" << home.latitude << "," << home.longitude << ")" << endl;
        break;
        case MAV_CMD_DO_SET_HOME:
            //Set UAV home location
            home.latitude = cmd.param5;
            home.longitude = cmd.param6;
            QTextStream(stdout) << "Set Home: (" << home.latitude << "," << home.longitude << ")" << endl;
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
        break;
    }
    return cmd;
}


void uav::sendFlightInfo() {
    mavlink_message_t msg;
    mavlink_msg_flight_information_pack(190, 1, &msg,
                                        flightInfo.time_boot_ms,
                                        flightInfo.arming_time_utc,
                                        flightInfo.takeoff_time_utc,
                                        flightInfo.flight_uuid);
    udpLink.sendMAVLinkMsg(msg);
    QTextStream(stdout) << "Info Packet Sent" << endl;
}

void uav::sendCmdAck(mavlink_command_long_t cmdMsg) {
    mavlink_message_t ackMsg;
    mavlink_msg_command_ack_pack(190, 1, &ackMsg, cmdMsg.command, MAV_CMD_ACK_OK);
    udpLink.sendMAVLinkMsg(ackMsg);
    QTextStream(stdout) << "Ack Packet Sent" << endl;
}

void uav::sendCurrentTelem() {
    timer->setInterval(200);
    updateUAVStatus();
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
    telemSeqNumber++;
    QTextStream(stdout) << "Telem Packet #" << telemSeqNumber << " Sent. "
                        << "UAV(Lat,Lon): " << "(" << uavStatus.lat << ", " << uavStatus.lon << ")" << endl;
}

void uav::updateUAVStatus() {
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
        pointOfInterest.pop();
        --storageStatus.used_capacity;
        if(!uavFlyingHome) {
            QTextStream(stdout) << "Destination reached: (" << nextPoint.lat << ", " << nextPoint.lon << "). Sent waypoint packet" << endl;
            QTextStream(stdout) << "Next destination: (" << pointOfInterest.front().lat << ", " << pointOfInterest.front().lon << ")." << endl;
        }
        else
            QTextStream(stdout) << "Home reached. Sent waypoint packet" << endl;
    }

    //After popping, check again whether queue is empty.
    //If queue is empty, go home. If already home, stop UAV.
    if (pointOfInterest.empty()) {
        if (!uavFlyingHome) {
            QTextStream(stdout) << "Nowhere else to go... Heading Home." << endl;
            uavFlyingHome = true;
            Waypoint homePoint;
            homePoint.lat = home.latitude;
            homePoint.lon = home.longitude;
            pointOfInterest.push(homePoint);
            ++storageStatus.used_capacity;
        }
        else {
            timer->stop();
            uavFlying = false;
            uavWaypointsReady = false;
        }
    }
}
