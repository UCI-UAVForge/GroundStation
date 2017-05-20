#include "gsserver.h"
#include "net.h"
#include <errno.h>
#include <signal.h>
#include <iostream>
#include <string>

GsServer::GsServer(messagebox *myMessageBox, Mission *myMission):
    networkListener(myMessageBox,this){

    this->myMessageBox = myMessageBox;
    this->myMission = myMission;
    port = NET::TARGET_PORT;
    target = NET::TARGET_ADDR;
    //connect(&networkListener, &NetworkListener::packetRecieved, this, &GsServer::recivePacket);
    connect(&networkListener, &NetworkListener::telemDataRecieved, this, &GsServer::recieveTelemData);
}

GsServer::~GsServer(){
    closeServer();
}

void GsServer::openServer(){
    running = true;
}

void GsServer::openServer(QHostAddress target, unsigned int port){
    this->target = target;
    this->port = port;
    openServer();
}

void GsServer::startServer(){
    if (running == false){
        std::cout << "Need to open server before it can start" << std::endl;
        return;
    }
    start();
}

void GsServer::closeServer(){
    networkListener.stop();
    running = false;
}

void GsServer::sendStartSequence() {

}

void GsServer::sendStopSequence() {
    Protocol::ActionPacket a1,a2;
    a1.SetAction(Protocol::ActionType::Stop);
    //a2.SetAction(Protocol::ActionType::Shutdown);
    sendPacket(&a1);
    //sendPacket(&a2);
}

void GsServer::sendFlightPath(FlightPath* fp) {
    for(TimedAction *a: *fp){
        a->first->SetAction(Protocol::ActionType::AddWaypoint);
        sendPacket(a->first);
    }
}

void GsServer::recieveAckPacket(Protocol::AckPacket* ack){
    outPackets.recieveAckPacket(ack);
}

void GsServer::run(){
    std::cout << "Server starting..." << std::endl;
    running = true;

    outSocket = new QUdpSocket();

    networkListener.startListening();

    Protocol::ActionPacket setHome;
    setHome.SetAction(Protocol::ActionType::SetHome);

    Protocol::ActionPacket start;
    start.SetAction(Protocol::ActionType::Start);

    sendPacket(&setHome,0);

    // The priority of this packet needs to be 100 if you want to work with simulation
    //sendPacket(&start, 100);
    sendPacket(&start,1);

    while (running){
        if (!outPackets.isEmpty()){
            sendNextPacket();
            QThread::msleep(100);
        }
        QThread::msleep(2000);
    }
    outSocket->close();
    std::cout << "Server closing..." << std::endl;
    delete outSocket;
}

void GsServer::sendPacket(Protocol::Packet* packet){
    sendPacket(packet,DEFAULT_PRIORITY);
}

void GsServer::sendPacket(Protocol::Packet* packet, unsigned int priority){
    outPackets.enqueue(packet,priority);
}

void GsServer::addPacketToMission(Protocol::TelemetryPacket packet){
    myMission->addPacket(packet);
}


void GsServer::sendNextPacket() {
    printf("sending message!\n");

    Protocol::Packet* packet = outPackets.getNextPacket();
    if(packet == NULL){
        std::cout<<"No packets left to send!" << std::endl;
        return;
    }

    //TEST retrieving data from the mission object
    /*
    QVector<double> *startValues = myMission->getValuesForID(1);
    std::cout<<"Start Values: ";
    for(double entry: *startValues){
        std::cout<<entry << ",";
    }
    std::cout<<std::endl;
    */
    //end retrieval test

    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);

    // Allocate storage for the packet in the for of u_int8_t
    unsigned char storage[NET::PACKET_LENGTH];

    // Convert the packet into bytes and store into storage
    size_t packet_size = packet->GetBytes(storage, NET::PACKET_LENGTH);

    // Send bytes inside storage to out datastream
    for(size_t i =0; i < packet_size; i++) {
        out << storage[i];
    }

    // Send datagram through UDP socket
    outSocket->writeDatagram(datagram, target, NET::TARGET_PORT);

    //TEST CODE TO SIMULATE INCOMING ACK PACKETS
    //COMMENT OUT TO USE ACTUAL ACK PACKETS

    ///@todo implement actual ack packet transfer from message box to outPackets.recievAckPacket(AckPacket)

    //Protocol::AckPacket *ack = new Protocol::AckPacket;
    //ack->set_timestamp(packet->get_timestamp());
    //outPackets.recieveAckPacket(ack);

    //END TEST CODE
}

/*
void GsServer::recivePacket(Protocol::Packet *packet) {
    emit packetRecieved(packet);
}*/

void GsServer::recieveTelemData(TelemetryData data) {
    emit telemDataRecieved(data);
}
