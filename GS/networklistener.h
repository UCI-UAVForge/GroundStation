#ifndef NETWORKLISTENER_H
#define NETWORKLISTENER_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QUdpSocket>
#include "messagebox.h"

class GsServer;

#include "packet.h"

/**
 * @brief The NetworkListener class is used to continuously listen for and
 * process incoming network signals.
 * @see GsServer
 * @author Jordan Dickson
 * @date 10-3-2015
 */
class NetworkListener : public QUdpSocket{
    Q_OBJECT
signals:
    /**
     * @brief sendCoordinates is used to request that the flightplan be sent
     * to the UAV
     * @see MapExecution::sendFlightPlan()
     */
    void sendCoordinates(void);

    void packetRecieved(Protocol::Packet *packet);
private:
    bool listening = true;
    int UAVid;
    messagebox *myMessageBox;
    //char buffer[];

private slots:
    void processPendingDatagrams();
public:
    void start();
    NetworkListener(messagebox *myMessageBox, int UAVid, GsServer* server);
    NetworkListener(messagebox *myMessageBox, GsServer* server);
    //QUdpSocket udpSocket;
    void netWait(int millis);
    //~NetworkListener();
    long reciveMessage(char* buf);
    void messageRecieved(char* msg);
    void setId(int UAVid);
    void stop();
    ~NetworkListener();
    GsServer *server;
};

#endif // NETWORKLISTENER_H
