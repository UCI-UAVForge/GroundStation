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

#define BACKLOG 10   // how many pending connections queue will hold

#define BUFSIZE 256

char listenPort[10];  // the port users will be connecting to
char sendPort[10];
char buf[BUFSIZE];

//--------

GsServer::GsServer(messagebox *myMessageBox): networkListener(myMessageBox){
    this->myMessageBox = myMessageBox;
    port = 27015;
}

GsServer::~GsServer(){

}

void GsServer::openServer(){
    running = true;
    this->start();
    networkListener.start();
}

void GsServer::closeServer(){

}

void GsServer::run(){
    running = true;
    while (running){
        if (!outPackets.isEmpty()){
            //std::cout << "Sending message..." << std::endl;
            sendNextPacket();
        }
        //QThread::msleep(1);
    }
}

void GsServer::sendPacket(Protocol::Packet* packet){
    sendPacket(packet,DEFAULT_PRIORITY);
}

void GsServer::sendPacket(Protocol::Packet* packet, unsigned int priority){
    priority = 0; //to suppress unused param warning
    outPackets.enqueue(packet);
    //outPackets.append(QPair<Protocol::Packet*,int>(packet,priority));
}

Protocol::Packet* GsServer::getNextPacket(){
    return outPackets.dequeue();

    /// \todo implement priority system
    /*unsigned int callID = 0;
    unsigned int prevHigh = 0;
    for (int i = 0; i < outPackets.length(); i++){
        if (outPackets.at(i).second>prevHigh){
            callID = i;
            prevHigh = outPackets.at(i).second;
        }
    }
    return outPackets.at(callID).first;*/
}

void GsServer::sendNextPacket() {
    Protocol::Packet* packet = getNextPacket();
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
    //sendUdpSocket.writeDatagram(datagram, QHostAddress::LocalHost, GroundStation::UAV_PORT_NUM);
    outSocket.writeDatagram(datagram, QHostAddress::LocalHost, SEND_PORT);
    //delete packet;
}
