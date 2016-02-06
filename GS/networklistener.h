#ifndef NETWORKLISTENER_H
#define NETWORKLISTENER_H

#include <QObject>
#include <QThread>
#include <QString>

/**
 * @brief The NetworkListener class is used to continuously listen for and
 * process incoming network signals.
 * @see GsServer
 * @author Jordan Dickson
 * @date 10-3-2015
 */
class NetworkListener : public QThread{
    Q_OBJECT
signals:
    /**
     * @brief sendCoordinates is used to request that the flightplan be sent
     * to the UAV
     * @see MapExecution::sendFlightPlan()
     */
    void sendCoordinates(void);

    /**
     * @brief logTelemetry is the signal used to notify the main window that a
     * telemetry point has been recieved.
     * @param coordString
     */
    void logTelemetry(QString coordString);
private:
    bool listening = true;
    int UAVid;
    //char buffer[];
public:
    NetworkListener(int UAVid);
    NetworkListener();

    void netWait(int millis);
    //~NetworkListener();
    long reciveMessage(char* buf);
    void messageRecieved(char* msg);
    void run();
    void stop();
    void setId(int UAVid);
    ~NetworkListener();
};

#endif // NETWORKLISTENER_H
