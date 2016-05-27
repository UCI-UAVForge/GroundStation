#ifndef GSSERVER_H
#define GSSERVER_H

#include <QQueue>
#include <QPair>
#include <QThread>
#include <QUdpSocket>
#include "serverqueue.h"
#include <QObject>
//#include "net.h"
#include "networklistener.h"
#include "messagebox.h"
#include "mission.h"

#define DEFAULT_PRIORITY 10

const static QString UAV_IP_ADDRESS = "localhost";


/**
  GsServer is the server object for the ground station. The current
  implementation will be changing, but this is the first working version.

  I will be cleaning the code and making frequent implementation changes in
  the near future. The functions and variables however will probably remain
  stable.

  @author Jordan Dickson
  @date 1-29-1016
  @version 2.0
*/
class GsServer : public QThread{
    Q_OBJECT
public:
    /**
     Creates a new server hosted on the localhost (127.0.0.1) on port 3495.

     @param myMessageBox the messagebox used for outgoing packets
     */
    GsServer(messagebox *myMessageBox, Mission *myMission);

    /**
      Destructor for GsServer
     */
    ~GsServer();

    /**
      Override run to implement thread as a server.
     */
    void run();

    /**
     * @brief recieveAckPacket
     * @param ack
     */
    void recieveAckPacket(Protocol::AckPacket* ack);


    void startServer();

    /**
      Opens ther server by hosting it on the default port and listening for
      connections.
     */
    void openServer();

    /**
      Opens ther server by hosting it on a socket and listening for
      connections.
     */
    void openServer(QHostAddress target, unsigned int port);

    /**
      Closes the server by dropping all current connections and ending the
      listener thread.
     */
    void closeServer();

    /**
      waits for a specified number of milliseconds

      @param millis the number of milliseconds to wait
    */
    void waitNet(unsigned millis);

    /**
     * @brief sendPacket adds a packet to the send queue for this server. The
     * default priority is 10. The packet will be sent as soon as the socket
     * is free for sending. Lowest prioirty is sent first.
     * @param packet the packet to be added into the send queue
     * @author Jordan Dickson
     * @date Feb 5 2016
     */
    void sendPacket(Protocol::Packet* packet);

    /**
     * @brief sendPacket adds a packet to the send queue for this server. The
     * packet will be sent as soon as the socket is free for sending. Lowest
     * priority is sent first.
     * @param packet the packet to be added into the send queue
     * @param priority the priority of the packet (lowest number sent first)
     * @date Feb 5 2016
     */
    void sendPacket(Protocol::Packet* packet, unsigned int priority);

    /**
     * @brief packetRecieved adds a TelemetryPacket to this server's Mission
     * object.
     * @param packet The telemetryPacket being added.
     */
    void packetRecieved(Protocol::TelemetryPacket packet);

    /**
     file descriptor for the UAV. Used to send information over the network.
     */
    int uav_fd;

    /**
     the maximum size of a packet that will be sent by this server.
     */
    unsigned char maxPackSize = 255;

    /**
      The NetworkListener used by this server to process incoming signals.
    */
    NetworkListener networkListener;


    bool running;
private:



    /* Alvin Truong added on 16-1-27*/
    const static int PACKET_LENGTH = 1000;
    const static int SEND_PORT = 20715;
    const static int LISTEN_PORT = 20715;
    static int NUM_RECV_PACKETS;


     /**
       Stores the port number of this server.
     */
     unsigned short port;

     /**
       Sends the most significant datagram.
     */
     void sendNextPacket();

     /**
      * @brief myMessageBox is the messagebox from mapexecution that will be used for
      * outgoing packets.
      */
     messagebox *myMessageBox;

     Mission *myMission;

     QUdpSocket outSocket;

     QHostAddress target;

     ServerQueue outPackets;
};
#endif // GSSERVER_H

