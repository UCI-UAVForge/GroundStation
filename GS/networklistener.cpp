#include "networklistener.h"
#include "net.h"
#include <QtCore>
#include <QDebug>
#include <iostream>
#include <QString>
#include "gsserver.h"

#include "AckPacket.h"
#include "ActionPacket.h"
#include "TelemetryPacket.h"
#include "InfoPacket.h"
#include "Packet.h"

#define BUFSIZE 4096

using namespace std;

#ifdef _WIN32
#include <windows.h>
    void NetworkListener::netWait(int millis) {
        Sleep(millis);
    }

#else

#include <unistd.h>
   void NetworkListener::netWait(int millis) {
       usleep(millis*1000);
   }

#endif

NetworkListener::NetworkListener(messagebox *myMessagebox, GsServer* server){
    this->myMessageBox = myMessagebox;
    this->server = server;
    std::cout << "New NetworkListener created." << std::endl;
    bind(NetworkListener::LISTEN_PORT);
    listening = true;

    //connect(server,SIGNAL(shutdownListener()),this,SLOT(stop()));

    //connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

NetworkListener::NetworkListener(messagebox *myMessagebox, int UAVid, GsServer* server):NetworkListener(myMessagebox, server) {
    this->UAVid = UAVid;
    listening = true;
}

NetworkListener::~NetworkListener() {
    stop();
}

void NetworkListener::processPendingDatagrams(){
    static int pack_number = 1;
    QByteArray datagram;
    datagram.resize(pendingDatagramSize());
    readDatagram(datagram.data(), datagram.size());

    Protocol::Packet* incPack = Protocol::Packet::Parse((uint8_t*)datagram.data(), datagram.size());
    Protocol::PacketType type = incPack->get_type();
    if (type == Protocol::PacketType::Ack){
        std::cout<< "AckPacket Received" << std::endl;
        Protocol::AckPacket *ackPacket = (Protocol::AckPacket*)incPack;
        myMessageBox->addAckPacket(*ackPacket);
    } else if (type == Protocol::PacketType::Action){
        std::cout<< "ActionPacket Received" << std::endl;
        Protocol::ActionPacket *actionPacket = (Protocol::ActionPacket*)incPack;
        Protocol::Waypoint test_wp;
        test_wp = actionPacket->GetWaypoint();
        std::cout << pack_number << " Latitude: " << test_wp.lat << " Longitude: " << test_wp.lon << std::endl;
        ++pack_number;

        if (actionPacket->GetAction() == Protocol::ActionType::AddWaypoint){
            Protocol::TelemetryPacket telem;
            telem.SetLocation(test_wp.lat,test_wp.lon,200);
            myMessageBox->addTelemetryPacket(telem);
        }

        myMessageBox->addActionPacket(*actionPacket);
    } else if (type == Protocol::PacketType::Telem){
        std::cout<< "TelemPacket Recieved" << std::endl;
        Protocol::TelemetryPacket *telemPacket = (Protocol::TelemetryPacket*)incPack;
        //std::cout << pack_number << " Latitude: " << telemPacket << " Longitude: " << telemPacket->lon << std::endl;
        ++pack_number;
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
void NetworkListener::start(){
    connect(this,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
}

void NetworkListener::stop(){
    //if(isOpen()){
        abort();
    //}
    disconnect(this,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
    listening = false;
    std::cout << "Stopping NetworkListener...";
}
