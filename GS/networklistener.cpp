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
    udpSocket.bind(27015);

    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

NetworkListener::NetworkListener(messagebox *myMessagebox, int UAVid):NetworkListener(myMessagebox) {
    this->UAVid = UAVid;
    listening = true;
}

NetworkListener::~NetworkListener() {

}

void NetworkListener::processPendingDatagrams(){

    //Coppied dirrectly from Avionics simulation
    QByteArray datagram;
    std::cout << "running!" << std::endl;


    do {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
        std::cout<< "loop!" << std::endl;
    } while (udpSocket.hasPendingDatagrams());

    QByteArray altitude;
    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_3);
    in >> altitude;

    std::cout << "running...";


    std::cout << altitude.toStdString();

}

void NetworkListener::setId(int UAVid){
    this->UAVid = UAVid;
}

void NetworkListener::run() {
    //----test code----
    listening = false;

    while (listening){

        netWait(1);
        long numbytes = 0;
        char buffer[BUFSIZE];
        numbytes = reciveMessage(buffer);
        if (listening){
            messageRecieved(buffer);
        }
    }
}

long NetworkListener::reciveMessage(char* buf){
  long len = BUFSIZE;
  char packets[16];
  recv(UAVid, packets, 16, 0);
  std::cout << packets << std::endl;
  int numOfPackets;
  try {
    numOfPackets = std::stoi(packets);
  } catch (std::invalid_argument) {
    numOfPackets = 0;
    std::cout << "Bad message format recieved" << std::endl;
  }
  std::cout << numOfPackets << "packets incoming" << std::endl;
  long numbytes = 0;
  for (int i = 0; i < numOfPackets; i++) {
    long bytes = 0;
    if ((bytes = recv(UAVid, buf, len-1, 0)) == -1) {
      perror("recv");
      return 0;
    }
    std::cout << "Reciving " << bytes << " bytes: " << buf << std::endl;
    numbytes += bytes;
  }
  return numbytes;
}

/*long NetworkListener::reciveMessage(char* buf){
  long numbytes = 0;
  if ((numbytes = recv(UAVid, buf, BUFSIZE-1, 0)) == -1) {
    perror("recv");
    return 0;
  }
  buf[numbytes] = '\0';
  std::cout << "Reciving " << numbytes << " bytes: '" << buf << "'" << std::endl;
  return numbytes;
}*/

void NetworkListener::messageRecieved(char *msg){
    int len = strlen(msg);
    unsigned char unsigned_msg[len+1];
    for(int i = 0; i < len; i ++){
        unsigned_msg[i] = (char)(msg[i]+128);
    }
    unsigned_msg[len] = 0;



    Protocol::Packet *incPacket = Protocol::Packet::Parse(unsigned_msg,len+1);
    Protocol::PacketType type = (Protocol::PacketType)unsigned_msg[0];
    switch (type) {
    case Protocol::PacketType::Ack:{
        std::cout<< "AckPacket Recieved";
        Protocol::AckPacket *ackPacket = (Protocol::AckPacket*)incPacket;
        myMessageBox->addAckPacket(*ackPacket);
        break;}
    case Protocol::PacketType::Action:{
        std::cout<< "ActionPacket Recieved";
        Protocol::ActionPacket *actionPacket = (Protocol::ActionPacket*)incPacket;
        myMessageBox->addActionPacket(*actionPacket);
        break;}
    case Protocol::PacketType::Telem:{
        std::cout<< "TelemPacket Recieved";
        Protocol::TelemetryPacket *telemPacket = (Protocol::TelemetryPacket*)incPacket;
        myMessageBox->addTelemetryPacket(*telemPacket);
        break;}
    case Protocol::PacketType::Info:{
        std::cout<< "InfoPacket Recieved";
        Protocol::InfoPacket *infoPacket = (Protocol::InfoPacket*)incPacket;
        myMessageBox->addInfoPacket(*infoPacket);
        break;}
    default:
        std::cout<< "UNKNOWN PACKET TYPE RECIEVED!";
        break;
    }

    return;

    //old recieve code
    QString msgString = msg;
    if (msgString == "init"){
        cout<< "Sending coordinates!" << endl;
        emit sendCoordinates();
    } else if (msgString.split(',').length()==3){
        emit logTelemetry(msgString);
    } else {
        std::cout << "Recieved unknown string: " << msgString.toStdString() << std::endl;
    }
}

void NetworkListener::stop(){
    listening = false;
}
