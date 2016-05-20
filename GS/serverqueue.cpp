#include "serverqueue.h"

#include <iostream>

const unsigned int DEFAULT_PRIORITY = 10;
const unsigned int DEFAULT_WINDOW_LEN = 5;
const unsigned int SEND_BUMP = 10;


ServerQueue::ServerQueue(int windowLen) {
    this->windowLen = windowLen;
}

ServerQueue::ServerQueue():ServerQueue(DEFAULT_WINDOW_LEN){

}

ServerQueue::~ServerQueue() {
    while (!pendingPackets.isEmpty()){
        delete pendingPackets.first();
        pendingPackets.removeFirst();
    }
}

void ServerQueue::updateWindow(){
    window.clear();
    int winCt = 0;
    for(QueueEntry *e:pendingPackets){
        if(window.size() == windowLen){
            break;
        }
        if(e->waitingForAck){
            window.append(e);
            winCt++;
        }
    }
}

bool ServerQueue::isEmpty(){
    return pendingPackets.isEmpty();
}

void ServerQueue::enqueue(Protocol::Packet *packet, unsigned int priority){
    QueueEntry *newEntry = (QueueEntry*)malloc(sizeof(QueueEntry));

    unsigned char str[1024];
    size_t length = packet->GetBytes(str,1024);

    Protocol::Packet *readPacket = Protocol::Packet::Parse(str,length);
    Protocol::Packet *newPacket;

    switch(readPacket->get_type()){
    case Protocol::PacketType::Ack:
        newPacket = new Protocol::AckPacket(str,length);
        break;
    case Protocol::PacketType::Action:
        newPacket = new Protocol::ActionPacket(str,length);
        break;
    case Protocol::PacketType::Info:
        newPacket = new Protocol::InfoPacket(str,length);
        break;
    case Protocol::PacketType::Telem:
        newPacket = new Protocol::TelemetryPacket(str,length);
        break;
    default:
        return;
    }

    newEntry->packet = newPacket;
    newEntry->priority = priority;
    newEntry->waitingForAck = true;

    QLinkedList<QueueEntry*>::iterator i;
    for(i = pendingPackets.begin();i!=pendingPackets.end(); ++i){
        if((*i)->priority >= newEntry->priority){
            break;
        }
    }
    pendingPackets.insert(i,newEntry);
}

void ServerQueue::enqueue(Protocol::Packet *packet){
    enqueue(packet,DEFAULT_PRIORITY);
}

void ServerQueue::dequeue(Protocol::Packet *packet){
    for (QueueEntry *entry : pendingPackets){
        if (entry->waitingForAck == false){
            if (packet == entry->packet){
                pendingPackets.removeOne(entry);
                break;
            }
        }
    }
}

void ServerQueue::forceDequeue(Protocol::Packet *packet){
    for (QueueEntry *entry : pendingPackets){
        if (packet == entry->packet){
            pendingPackets.removeOne(entry);
            break;
        }
    }
}

bool ServerQueue::recieveAckPacket(Protocol::AckPacket *ack_pack){
    std::cout << "Ack Packet Recieved!" << std::endl;
    for (QueueEntry *entry : window){
        if (entry->waitingForAck == true){
            int entryTS = entry->packet->get_timestamp();
            int ackTS = ack_pack->get_timestamp();
            std::cout << entryTS << "==" << ackTS << std::endl;
            if (entry->packet->get_timestamp() == ack_pack->get_timestamp()){
                entry->waitingForAck = false;
                return true;
            }
        }
    }
    return false;
}

Protocol::Packet *ServerQueue::getNextPacket(){
    static int sentCt = 0;
    if(sentCt == 0){
        updateWindow();
        std::cout << "refreshing output packet window!" << std::endl;
    }

    Protocol::Packet *rtnPacket = NULL;
    if(window.size() > sentCt) {
        rtnPacket = window.at(sentCt++)->packet;
        sentCt = sentCt%window.size();
    }

   return rtnPacket;
}
