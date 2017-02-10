#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QList>
#include <QWebEngineView>
#include <QUrl>
#include <QWebChannel>
#include <QWebSocketServer>
#include <QWebChannelAbstractTransport>
#include "actionpacket.h"
#include "websocketclientwrapper.h"
#include "websockettransport.h"
#include "flightpath.h"

/**
 * @brief The MapWidget class
 * @author Jordan Dickson
 */
class MapWidget : public QWebEngineView {
Q_OBJECT
private:
    bool loading = false;
    QList<QList<Protocol::Waypoint> >* lists;
    QWebChannel channel;
    QWebSocketServer server;
    WebSocketClientWrapper clientWrapper;

    const QUrl MapURL = QUrl("qrc:/res/html/mapsPlanningGoogle.html");


public:
    MapWidget(QWidget *parent = 0);
    ~MapWidget();

    /**
     * @brief ready
     * @return True if the MapWidget input or output Waypoints
     */
    bool ready();

    /**
     * @brief createNewPath
     * @return A new path ID for adding waypoints to and retrieving the path.
     */
    int createNewPath();

    /**
     * @brief appendGPSCoordToPath
     * @param lat
     * @param lng
     * @param pathID - The ID of the path the point is to be added to.
     */
    void appendGPSCoordToPath(double lat, double lng, int pathID);

    /**
     * @brief getPath
     * @param pathID - The of the path to be returned
     * @return An ordered list of all the waypoints in a certain path
     */
    QList<Protocol::Waypoint>* getPath(int pathID);

private slots:
    /**
     * @brief loadStartedSlot tied to the loadStarted signal
     */
    void loadStartedSlot();

    /**
     * @brief loadFinishedSlot tied to the loadFinished signal
     */
    void loadFinishedSlot();

public slots:
    /**
     * @brief addPointToTable
     * @param lat
     * @param lng
     */
    void addPointToTable(double lat, double lng);

    /**
     * @brief clearMap
     */
    void clearMap();

    /**
     * @brief disconnectWebSocket must be called before opening another MapWidget
     * Later we'll work a solution that allows for multiple MapWidgets to be "open"
     * at the same time.
     */
    void disconnectWebSocket();

    /**
     * @brief addFlightpath
     * @param fp
     * @param index
     */
    void addFlightPath(FlightPath* fp, int index = 0);

signals:
    //Qt Signals for use with C++
    /**
     * @brief pointAddedToMap is emitted each time a new point is added to
     * the map.
     * @param lat - the latitude of the new point
     * @param lng - the longitude of the new point
     * @param pathID - the ID of the path the point is a member of
     */
    void pointAddedToMap(double lat, double lng, int pathID);

    //JavaScript Signals for use with Cbridge.js
    /**
     * @brief sendPointToMap Tells the mapping script to append a new waypoint
     * with (lat,lng) to a the path with ID equal to pathID
     * @param lat - the latitude of the new waypoint
     * @param lng - the longitude of the new waypoint
     * @param pathID - the ID of the path to be appended to
     */
    void sendPointToMap(double lat, double lng, int pathID);

    /**
     * @brief clearFlightpath Tells the mapping script to delete all of the
     * points in the path with ID equal to pathID.
     * @param pathID - The ID of the flight path to be cleared.
     */
    void clearFlightPath(int pathID);
};

#endif // MAPWIDGET_H
