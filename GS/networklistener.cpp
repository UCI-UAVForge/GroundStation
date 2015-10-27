#include "networklistener.h"
#include "net.h"
#include <QtCore>
#include <QDebug>
#include <iostream>
#include <QString>

#define BUFSIZE 4096

using namespace std;

NetworkListener::NetworkListener(int UAVid) {
    this->UAVid = UAVid;
    listening = true;
}

NetworkListener::NetworkListener(){

}

NetworkListener::~NetworkListener() {

}

void NetworkListener::setId(int UAVid){
    this->UAVid = UAVid;
}


void NetworkListener::run() {
    while (listening){
        net::sleep(1);
        net::sleep(1);
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
