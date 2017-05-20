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
#include "dataobjects.h"

#define DEFAULT_PRIORITY 10


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
     * GsServer constructor that makes its own messagebox.
     */
    GsServer( Mission * myMission ) : GsServer ( new messagebox() , myMission ) { }

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

    /**
     * @brief startServer
     */
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
     * @brief sendStartSequence sends the sequence of packets necesary to start
     * the execution of a mission
     */
    void sendStartSequence();

    /**
     * @brief sendStopSequence sends the sequence of packets necesary to
     * terminate a mission.
     */
    void sendStopSequence();

    /**
     * @brief sendFlightPath sends all of the waypoints in a flightpath to
     * the UAV
     * @param fp A pointer to the FlightPath object containing the waypoints
     */
    void sendFlightPath(FlightPath *fp);

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
    void addPacketToMission(Protocol::TelemetryPacket packet);

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

     QUdpSocket *outSocket;

     QHostAddress target;

     ServerQueue outPackets;

private slots:
     //void recivePacket(Protocol::Packet* packet);
     void recieveTelemData(TelemetryData data);

signals:
     //void packetRecieved(Protocol::Packet* packet);
     void telemDataRecieved(TelemetryData data);
};
#endif // GSSERVER_H

