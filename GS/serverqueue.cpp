#include "serverqueue.h"

#include <iostream>

const unsigned int DEFAULT_PRIORITY = 10;
const unsigned int SEND_BUMP = 10;
ServerQueue::ServerQueue() {

}

ServerQueue::~ServerQueue() {
    for (int i = 0; i < pendingPackets.length(); i++){
        delete pendingPackets[i];
    }
}

void ServerQueue::bumpPriorities(int amount){
    for(QueueEntry *entry : pendingPackets){
        if(((int)entry->priority + amount) > 0){
            entry->priority += amount;
        } else {
            entry->priority += amount-((int)entry->priority + amount);
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
    newEntry->waitingForAck = false;
    bumpPriorities(-1);
    pendingPackets.append(newEntry);
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
    for (QueueEntry *entry : pendingPackets){
        if (entry->waitingForAck == true){
            if (entry->packet->get_timestamp() == ack_pack->get_timestamp()){
                pendingPackets.removeOne(entry);
                return true;
            }
        }
    }
    return false;
}

Protocol::Packet *ServerQueue::getNextPacket(){
    unsigned int highestPriority = 100000;
    QueueEntry *nextSend = NULL;

    for (QueueEntry *entry : pendingPackets){
        if (entry->priority < highestPriority){
            highestPriority = entry->priority;
            nextSend = entry;
        }
    }
    if(nextSend){
        nextSend->waitingForAck = true;
        nextSend->priority += SEND_BUMP;
        bumpPriorities(-1);
        return nextSend->packet;
    }
    return NULL;
}
