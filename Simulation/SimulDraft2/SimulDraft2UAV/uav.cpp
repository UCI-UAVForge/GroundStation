#include "uav.h"
#include "common/common/mavlink_msg_global_position_int.h"

#define NULL_TIME QTime(0,0,0,0)

uav::uav(QWidget *parent)
{   
    //Variables only for this scope. Initialized to meaningless default values.
    QTime currentTimeTemp = NULL_TIME;

    //Initialize UAV properties
    uavOn = true;
    uavWaypointsReady = false;
    uavFlying = false;
    uavFlyingHome = false;
    batteryStatus.battery_remaining = 100;
    storageStatus.total_capacity = 20;
    storageStatus.used_capacity = 0;
    telemSeqNumber = 1;
    uavStatus.lat = 33.6454;
    uavStatus.lon = -117.8426;
    home.latitude = uavStatus.lat;
    home.longitude = uavStatus.lon;
    latLngSpd = .02;

    //Create timer, send telemetry packets every 200ms
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendCurrentTelem()));
    timer->start(200);

    //Create a QTime object. Keeps track of the timestamp since the system started up.
    currentTimeTemp = QTime::currentTime();
    timeSinceBoot = new QTime(currentTimeTemp.hour(),
                              currentTimeTemp.minute(),
                              currentTimeTemp.second(),
                              currentTimeTemp.msec());
    timeSinceBoot->start();

    //Connect receiving socket to packet processing method
    recvUdpSocket.bind(uav::UAV_PORT_NUM);
    connect(&recvUdpSocket, SIGNAL(readyRead()),
                this, SLOT(processPendingDatagrams()));
    QTextStream(stdout) << "Listening for packets.." << endl;
}

void uav::sendAllPackets(std::queue<mavlink_message_t> packets) {
    int size = packets.size();
    QTextStream(stdout) << "The size of the vector is " << size << endl;
    for(int i = 0; i < size; ++i) {
        sendAPacket(packets.front());
        packets.pop();
    }
}

void uav::sendAllPackets(std::vector<mavlink_message_t> packets) {
    QTextStream(stdout) << "The size of the vector is " << packets.size() << endl;
    for(auto i = packets.begin(); i != packets.end(); ++i)
        sendAPacket(*i);
}

void uav::sendAPacket(mavlink_message_t msg) {
    QByteArray datagram;
    uint8_t buf[MAVLINK_MAX_PAYLOAD_LEN];

    //Put mavlink message in buf
    mavlink_msg_to_send_buffer(buf, &msg);
    //Put buf in QByteArray datagram
    datagram = QByteArray((char*)buf, MAVLINK_MAX_PAYLOAD_LEN);

    qDebug() << "Just put packet to be sent into a datagram buffer." ;
    int newMessageId = ( (int)0 ) | ( buf[9] << 16 ) | ( buf[8] << 8 ) | ( buf[7] ) ;
    qDebug() << "The message id is now" << newMessageId ;

    //Send datagram through sendUdpSocket
    sendUdpSocket.writeDatagram(datagram.data(), datagram.size(), QHostAddress::LocalHost, uav::GS_PORT_NUM);
}

void uav::processPendingDatagrams() {
    QTextStream(stdout) << "Data received" << endl;
    while (recvUdpSocket.hasPendingDatagrams()) {
        //Initialize vars for receiving message
        QByteArray datagram;
        mavlink_message_t msg;
        mavlink_status_t status;
        //Resize datagram and read data from recvUdpSocket
        datagram.resize(recvUdpSocket.pendingDatagramSize());
        recvUdpSocket.readDatagram(datagram.data(), datagram.size());

        //Parse using mavlink library
        for (int i = 0; i < datagram.size(); i++) {
            if(mavlink_parse_char(1, datagram.data()[i], &msg, &status)) {
                QTextStream(stdout) << "Message received" << endl;
                //If msg is a command, decode. Otherwise, use apm_planner decoder
                if (msg.msgid == MAVLINK_MSG_ID_COMMAND_LONG) {
                    sendCmdAck(parseCommand(msg));
                }
                else {
                    //QTextStream(stdout) << decoder.receiveMessage(*msg);
                }
            }
        }
    }
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
    sendAPacket(msg);
    QTextStream(stdout) << "Info Packet Sent" << endl;
}

void uav::sendCmdAck(mavlink_command_long_t cmdMsg) {
    mavlink_message_t ackMsg;
    mavlink_msg_command_ack_pack(190, 1, &ackMsg, cmdMsg.command, MAV_CMD_ACK_OK);
    sendAPacket(ackMsg);
    QTextStream(stdout) << "Ack Packet Sent" << endl;
}

void uav::sendCurrentTelem() {

    updateUAVStatus();
    mavlink_message_t msg;

    mavlink_msg_global_position_int_pack(1,190,&msg,timeSinceBoot->elapsed(),
                                         uavStatus.lat, uavStatus.lon, uavStatus.alt,
                                         /* NOTE: RELATIVE ALTITUDE IS NOT THE SAME! PLEASE ADJUST! */
                                         uavStatus.alt,
                                         /* NOTE: SUPPOSED TO BE X,Y,Z NOT N,E,D! PLEASE ADJUST! */
                                         uavStatus.vn, uavStatus.ve, uavStatus.vd,
                                         /* NOTE: CHECK IF YAW IS THE SAME AS HDG!!! */
                                         uavStatus.yaw);

/*
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
*/
    sendAPacket(msg);
    qDebug() << "Just sent message with message id: " << msg.msgid ;
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
