#include "gsserver.h"
#include <errno.h>
#include <signal.h>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <winsock.h>
#include <windows.h>

#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#include<Ws2tcpip.h>
#include<signal.h>

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46
#endif

void GsServer::waitNet(unsigned millis){
  Sleep(millis);
}
#else
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
void GsServer::waitNet(unsigned millis){
    usleep(millis * 1000);
}
#endif


GsServer::GsServer(messagebox *myMessageBox): networkListener(myMessageBox,this){
    this->myMessageBox = myMessageBox;
    port = 27015;
    target = QHostAddress::LocalHost;
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
    std::cout << "Server starting..." << std::endl;
    if (running == false){
        std::cout << "Need to open server before it can start" << std::endl;
        return;
    }
    this->start();
    networkListener.start();
}

void GsServer::closeServer(){
    networkListener.stop();
    running = false;
}

void GsServer::run(){
    running = true;

    Protocol::ActionPacket setHome;
    setHome.SetAction(Protocol::ActionType::SetHome);

    Protocol::ActionPacket start;
    start.SetAction(Protocol::ActionType::Start);

    sendPacket(&setHome,0);

    // The priority of this packet needs to be 100 if you want to work with simulation
    // sendPacket(&start, 100);
    sendPacket(&start,1);

    while (running){
        if (!outPackets.isEmpty()){
            sendNextPacket();
        }
        QThread::msleep(2000);
    }

}

void GsServer::sendPacket(Protocol::Packet* packet){
    sendPacket(packet,DEFAULT_PRIORITY);
}

void GsServer::sendPacket(Protocol::Packet* packet, unsigned int priority){
    outPackets.enqueue(packet,priority);
}

void GsServer::sendNextPacket() {
    printf("sending message!\n");

    Protocol::Packet* packet = outPackets.getNextPacket();
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);

    // Allocate storage for the packet in the for of u_int8_t
    unsigned char storage[PACKET_LENGTH];

    // Convert the packet into bytes and store into storage
    size_t packet_size = packet->GetBytes(storage, PACKET_LENGTH);

    // Send bytes inside storage to out datastream
    for(size_t i =0; i < packet_size; i++) {
        out << storage[i];
    }

    // Send datagram through UDP socket
    outSocket.writeDatagram(datagram, target, port);


    //TEST CODE TO SIMULATE INCOMING ACK PACKETS
    //COMMENT OUT TO USE ACTUAL ACK PACKETS

    ///@todo implement actual ack packet transfer from message box to outPackets.recievAckPacket(AckPacket)

    Protocol::AckPacket *ack = new Protocol::AckPacket;
    ack->set_timestamp(packet->get_timestamp());
    outPackets.recieveAckPacket(ack);

    //END TEST CODE
}
