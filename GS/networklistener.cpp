#include "networklistener.h"
#include "net.h"
#include <QtCore>
#include <QDebug>
#include <QString>
#include "gsserver.h"

#include "ackpacket.h"
#include "actionpacket.h"
#include "telemetrypacket.h"
#include "infopacket.h"
#include "packet.h"

#define BUFSIZE 4096
#define NOT_LISTENING false
#define LISTENING true

using namespace std;

NetworkListener::NetworkListener(messagebox *myMessagebox, GsServer* server){
    this->listening = NOT_LISTENING;
    this->myMessageBox = myMessagebox;
    this->server = server;
    qDebug() << "New NetworkListener created." ;
    groupAddress = QHostAddress("239.255.43.21");
    this->bind(QHostAddress::AnyIPv4, NET::LISTEN_PORT, QUdpSocket::ShareAddress);
    this->joinMulticastGroup(groupAddress);
}

NetworkListener::NetworkListener(messagebox *myMessagebox, int UAVid, GsServer* server):NetworkListener(myMessagebox, server) {
    this->UAVid = UAVid;
    this->listening = LISTENING;
}

NetworkListener::~NetworkListener() {
    stop();
}

void NetworkListener::processPendingDatagrams(){
    static int pack_number = 1;
    QByteArray datagram;

    //NEW CODE
    mavlink_message_t msg;
    mavlink_command_long_t cmd;
    mavlink_status_t status;

    datagram.resize(this->pendingDatagramSize());
    this->readDatagram(datagram.data(), datagram.size());

    for (int i = 0; i < datagram.size(); i++) {
        if(mavlink_parse_char(1, datagram.data()[i], &msg, &status)) {
                qDebug() << "Just successfully read a message from the receive udp socket on GS end." ;
                qDebug() << "Its message id issssss: " << msg.msgid;
                if (msg.msgid == MAVLINK_MSG_ID_COMMAND_LONG) {
                    mavlink_msg_command_long_decode(&msg, &cmd);
                }
                qDebug() << "--------------------------------" ;
                qDebug() << "Received message";

                QList<QPair<QString,QVariant>> listOfValues = decoder.receiveMessage(msg);

                qDebug() << listOfValues ;
                qDebug() << "--------------------------------" ;
        }
    }

/*
    statusLabel->setText(tr("Received datagram: \"%1\"")
                         .arg(datagram.data()));
    //

    datagram.resize(pendingDatagramSize());
    readDatagram(datagram.data(), datagram.size());

    Protocol::Packet* incPack = Protocol::Packet::Parse((uint8_t*)datagram.data(), datagram.size());
    Protocol::PacketType type = incPack->get_type();
    if (type == Protocol::PacketType::Ack){
        std::cout<< "AckPacket Recieved" << std::endl;
        Protocol::AckPacket *ackPacket = (Protocol::AckPacket*)incPack;
        myMessageBox->addAckPacket(*ackPacket);
        server->recieveAckPacket(ackPacket);
    } else if (type == Protocol::PacketType::Action){
        std::cout<< "ActionPacket Recieved" << std::endl;
        Protocol::ActionPacket *actionPacket = (Protocol::ActionPacket*)incPack;
        Protocol::Waypoint test_wp;
        test_wp = actionPacket->GetWaypoint();
        std::cout << pack_number << " Latitude: " << test_wp.lat << " Longitude: " << test_wp.lon <<  " Alt: " <<  test_wp.alt  << std::endl;
        ++pack_number;

        ///\todo remove this so that the red line is dependent on telem packets rather than action packets
        myMessageBox->addActionPacket(*actionPacket);
    } else if (type == Protocol::PacketType::Telem){
        std::cout<< "TelemPacket Recieved" << std::endl;
        Protocol::TelemetryPacket *telemPacket = (Protocol::TelemetryPacket*)incPack;
        //std::cout << pack_number << " Latitude: " << telemPacket << " Longitude: " << telemPacket->lon << std::endl;
        ++pack_number;
        myMessageBox->addTelemetryPacket(*telemPacket);
        server->addPacketToMission(*telemPacket);
        //emit this->packetRecieved(telemPacket);

        TelemetryData td(telemPacket);
        emit telemDataRecieved(td);
    } else if (type == Protocol::PacketType::Info){
        std::cout<< "InfoPacket Recieved" << std::endl;
        Protocol::InfoPacket *infoPacket = (Protocol::InfoPacket*)incPack;
        myMessageBox->addInfoPacket(*infoPacket);
    } else {
        std::cout<< "UNKNOWN PACKET TYPE RECIEVED!" << std::endl;
    }
*/
    return;
}
void NetworkListener::start(){
    qDebug() << "Starting NetworkListener." ;
    connect(this,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
    this->listening = LISTENING;
    qDebug() << "NetworkListener successfully started." ;
}

void NetworkListener::stop(){
    std::cout << "Stopping NetworkListener.";
    //if(isOpen()){
        abort();
    //}
    if ( this->listening == LISTENING ) {
        disconnect(this,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
    }
    this->listening = NOT_LISTENING;
    std::cout << "NetworkListener successfully stopped.";
}
