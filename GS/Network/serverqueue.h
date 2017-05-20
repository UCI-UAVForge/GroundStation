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

/**
 * @brief The ServerQueue class is a specialized priority queue-like data
 * structure for holding Packets before they are sent over the network.
 *
 * The enqueue(Packet, int) and getNextPacket() methods are the main way
 * to interact with this class. enqueue-ing packets will insert them into
 * the list at a location corresponding with their priority. getNextPacket
 * will grab the next Packet to send - determined internally by this class.
 *
 * Packets come out of the queue lowest priority value first. A priority of
 * 5 will be sent before a priority of 10. If two packets have the same
 * priority, they will be sent in the order that they were added.
 */
class ServerQueue {
private:
    /**
     * @brief pendingPackets The list of all packets waiting to be sent
     * out over the network. The list should be in order of priority with
     * the lowest values (highest priority) first and larger values
     * (lower priorities) last.
     */
    QLinkedList<QueueEntry*> pendingPackets;

    /**
     * @brief window The (small) List of Packets that this queue will
     * allow to be sent over the network. It will hold the Packets here
     * until higher priority Packets are added, or the Packets held in
     * the list are acknowledged.
     */
    QList<QueueEntry*> window;

    /**
     * @brief windowLen The maximum length of window. The number of packets
     * this Queue will send before any are acknowledged.
     */
    int windowLen;

    /**
     * @brief updateWindow Updates the contents of the window List by
     * grabbing the highest priority Packets out of pendingPackets until
     * the window if full.
     */
    void updateWindow();

public:
    /**
     * @brief ServerQueue Creates a ServerQueue object with the default
     * window length.
     */
    ServerQueue();

    /**
     * @brief ServerQueue Creates a ServerQueue object with the given window
     * length.
     * @param windowLen The maximum number of pending packets this queue
     * will allow before it begins to cycle though pending packets.
     */
    ServerQueue(int windowLen);

    /**
     * ServerQueue destructor
     */
    ~ServerQueue();

    /**
     * @brief isEmpty
     * @return True if the ServerQueue has no packets in it, False otherwise
     */
    bool isEmpty();

    /**
     * @brief enqueue Adds a packet to this ServerQueue with the default
     * priority. The default priority is 10.
     * @param packet The packet being added to the ServerQueue
     */
    void enqueue(Protocol::Packet *packet);

    /**
     * @brief enqueue Adds a packet to this ServerQueue with the given
     * priority.
     * @param packet The packet being added to the ServerQueue
     * @param priority The prioitity with which this packet will be sent.
     * Low numbers are sent first. When priorities tie, the packet that
     * was added to the queue first will be sent first. The default
     * priority is 10.
     */
    void enqueue(Protocol::Packet *packet, unsigned int priority);

    /**
     * @todo Implement and test this
     * @brief dequeue Removes a packet from the ServerQueue if it has
     * already been acknoledged.
     * @param packet The packet that will be removed
     */
    void dequeue(Protocol::Packet *packet);

    /**
     * @todo Implement and test this
     * @brief forceDequeue Removes a packet from the ServerQueue
     * regardless of if it has been acknolodged.
     * @param packet The packet that will be removed
     */
    void forceDequeue(Protocol::Packet *packet);

    /**
     * @brief recieveAckPacket Reads the timestamp in ack_pack and
     * compares it to the current pending packets. If there is a match
     * the corresponding Packet is removed from the pending list. If
     * there are no matches, the AckPacket is ignored.
     * @param ack_pack The incoming AckPacket
     * @return true if the AckPacket matches one of the pending packets,
     * false otherwise
     */
    bool recieveAckPacket(Protocol::AckPacket *ack_pack);

    /**
     * @brief getNextPacket Internally determines and gets the Packet
     * thst should be sent out next.
     * @return The next Packet to send
     */
    Protocol::Packet *getNextPacket();
};

#endif // SERVERQUEUE_H
