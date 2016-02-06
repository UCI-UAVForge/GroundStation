#ifndef GSSERVER_H
#define GSSERVER_H

#include <QList>
#include <QPair>
#include <QThread>
#include <QUdpSocket>
#include "net.h"
#include "networklistener.h"
#include "messagebox.h"

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
    //Q_OBJECT
public:
    /**
     Creates a new server hosted on the localhost (127.0.0.1) on port 3495.

     @param myMessageBox the messagebox used for outgoing packets
     */
    GsServer(messagebox *myMessageBox);

    /**
     Creates a new server and immediately attatches it to
     the IP address and port stored in myAddress.

     @param myAddress the object containing the address and port to host
     the server on.
     @param myMessageBox the messagebox used for outgoing packets
     */
    GsServer(net::GS_Address myAddress,messagebox *myMessageBox);

    /**
      Destructor for GsServer
     */
    ~GsServer();

    /**
      Override run to implement thread as a server.
     */
    void run();

    /**
      Opens ther server by hosting it on a socket and listening for
      connections.
     */
    int openServer();

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
     packs charArr with the a formatted version of the coordinates stored in
     coords up to the length specified by len. Use this to format
     coordinates before sending to UAV via network.

     @param charArr pointer to the start of the character array to be packed
     @param len the maximum number of characters to pack into charArr. This
     function will never split coordinates, so the coodinate that would have
     exceeded len will be omitted entirely.
     @param coords the QList of QPairs containing <latitude,longitude> for
     each coordinate.

     @see formatCoord(char*, QPair<double,double>)
     */
    void formatCoordinatesToSend(char* charArr, int len, QList<QPair<double, double> > coords);

    /**
     sends the first len characters in charArr to the target specified by
     target. Will break up long messages into packets of packSize size.

     @param charArr pointer to the start of the character array to be sent.
     @param len number of characters to send from charArr.
     @param packSize the maximum packet size to be sent.
     @param target the ID number cooresponding with the intended recipient.

     @returns 0 if the process was successful.
     */
    int sendMessage(char* charArr, int len, int packSize, int target);

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
     file descriptor for the UAV. Used to send information over the network.
     */
    int uav_fd;

    /**
     the maximum size of a packet that will be sent by this server.
     */
    u_int maxPackSize = 255;

    /**
      The NetworkListener used by this server to process incoming signals.
    */
    NetworkListener networkListener;

private:
    /**
     Function used to format a single coordinate for sendingover the network.

     @param charArr the character array to write the formatted coorinate to.
     @param coord the QPair of doubles represnting the latitude and longitude
     of the coordinate.

     @returns The length (in characters/bytes) of the formatted coordinate.
    */
     int formatCoord(char* charArr, QPair<double,double> coord);

     /**
       Stores the IP address of this server.
     */
     unsigned long myAddressInt;

     /**
       Stores the port number of this server.
     */
     unsigned short port;

     /**
       Sends the most significant datagram.
     */
     void sendDatagram();

     /**
      * @brief myMessageBox is the messagebox from mapexecution that will be used for
      * outgoing packets.
      */
     messagebox *myMessageBox;

     /**
      * @brief outPackets is the list of packets waiting to be sent by the server.
      * each packet is paired with a priority. (low numbers sent first)
      */
     QList<QPair<Protocol::Packet*,unsigned int> > outPackets;
};
#endif // GSSERVER_H

