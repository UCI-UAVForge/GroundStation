#include "networklistener.h"
#include "net.h"
#include <QtCore>
#include <QDebug>
#include <iostream>
#include <QString>

#include "ackpacket.h"
#include "actionpacket.h"
#include "telemetrypacket.h"
#include "infopacket.h"
#include "packet.h"

#define BUFSIZE 4096

using namespace std;

#ifdef _WIN32
    void NetworkListener::netWait(int millis) {
        Sleep(millis);
    }

#else

#include <unistd.h>
   void NetworkListener::netWait(int millis) {
       usleep(millis*1000);
   }

#endif

NetworkListener::NetworkListener(messagebox *myMessagebox){
     this->myMessageBox = myMessagebox;

    std::cout << "New NetworkListener created." << std::endl;
    udpSocket.bind(NetworkListener::LISTEN_PORT);
    listening = true;

    //connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

NetworkListener::NetworkListener(messagebox *myMessagebox, int UAVid):NetworkListener(myMessagebox) {
    this->UAVid = UAVid;
    listening = true;
}

NetworkListener::~NetworkListener() {
}

void NetworkListener::processPendingDatagrams(){
    static int pack_number = 1;
    QByteArray datagram;
    datagram.resize(udpSocket.pendingDatagramSize());
    udpSocket.readDatagram(datagram.data(), datagram.size());

    Protocol::Packet* incPack = Protocol::Packet::Parse((uint8_t*)datagram.data(), datagram.size());
    Protocol::PacketType type = incPack->get_type();
    if (type == Protocol::PacketType::Ack){
        std::cout<< "AckPacket Recieved" << std::endl;
        Protocol::AckPacket *ackPacket = (Protocol::AckPacket*)incPack;
        myMessageBox->addAckPacket(*ackPacket);
    } else if (type == Protocol::PacketType::Action){
        std::cout<< "ActionPacket Recieved" << std::endl;
        Protocol::ActionPacket *actionPacket = (Protocol::ActionPacket*)incPack;
        Protocol::Waypoint test_wp;
        test_wp = actionPacket->GetWaypoint();
        std::cout << pack_number << " Latitude: " << test_wp.lat << " Longitude: " << test_wp.lon << std::endl;
        ++pack_number;
        myMessageBox->addActionPacket(*actionPacket);
    } else if (type == Protocol::PacketType::Telem){
        std::cout<< "TelemPacket Recieved" << std::endl;
        Protocol::TelemetryPacket *telemPacket = (Protocol::TelemetryPacket*)incPack;
        myMessageBox->addTelemetryPacket(*telemPacket);
    } else if (type == Protocol::PacketType::Info){
        std::cout<< "InfoPacket Recieved" << std::endl;
        Protocol::InfoPacket *infoPacket = (Protocol::InfoPacket*)incPack;
        myMessageBox->addInfoPacket(*infoPacket);
    } else {
        std::cout<< "UNKNOWN PACKET TYPE RECIEVED!" << std::endl;
    }
    return;
}
void NetworkListener::run() {
    std::cout << "NetworkListener started listening!" << std::endl;
    while (listening){
        if (udpSocket.isValid()){
            if (udpSocket.hasPendingDatagrams()) {
                processPendingDatagrams();
            }
        }
    }
    std::cout << "NetworkListener stopped listening!" << std::endl;
}

void NetworkListener::stop(){
    listening = false;
    std::cout << "Stopping NetworkListener...";
}
