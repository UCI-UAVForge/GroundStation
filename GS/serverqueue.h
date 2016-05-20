#ifndef SERVERQUEUE_H
#define SERVERQUEUE_H

#include <QList>
#include <QLinkedList>

#include "packet.h"
#include "ackpacket.h"
#include "actionpacket.h"
#include "infopacket.h"
#include "telemetrypacket.h"

typedef struct QUEUE_ENTRY{
    Protocol::Packet *packet = NULL;
    unsigned int priority = 10000;
    bool waitingForAck = false;
}QueueEntry;

class ServerQueue {
private:
    QLinkedList<QueueEntry*> pendingPackets;
    QList<QueueEntry*> window;

    int windowLen;

    void updateWindow();

public:
    ServerQueue();
    ServerQueue(int windowLen);
    ~ServerQueue();
    bool isEmpty();

    void enqueue(Protocol::Packet *packet);
    void enqueue(Protocol::Packet *packet, unsigned int priority);

    void dequeue(Protocol::Packet *packet);

    void forceDequeue(Protocol::Packet *packet);

    bool recieveAckPacket(Protocol::AckPacket *ack_pack);
    Protocol::Packet *getNextPacket();
};

#endif // SERVERQUEUE_H
