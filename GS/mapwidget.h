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

    const QUrl MapURL = QUrl("qrc:/res/html/mapsPlanningLeaflet.html");


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
     * @param pathID - The ID of the path to be returned
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

    //Qt public slots for general use in C++

    /**
     * @brief sendCreateNewPath
     * @param id
     */
    void sendCreateNewPath(int id);

    /**
     * @brief sendSetActivePath
     * @param id
     */
    void sendSetActivePath(int id);

    /**
     * @brief addPointToMap
     * @param lat
     * @param lng
     * @param index
     * @param pathID
     */
    void addPointToMap(double lat, double lng, int index, int pathID);

    /**
     * @brief appendPointToMap
     * @param lat
     * @param lng
     * @param pathID
     */
    void appendPointToMap(double lat, double lng, int pathID);

    /**
     * @brief clearMap
     * @param pathID
     */
    void sendClearFlightPath(int pathID);

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
    void addFlightPath(FlightPath* fp, int id = 0, QString source = "");

    //JavaScript public slots for use with Cbridge.js
    /**
     * @brief pointAddedToMap Tells MapWidget that the user has added a new
     * waypoint with (lat, lng) at the specified index to the path with
     * identifier ID.
     * @param lat - the latitude of the point that was added
     * @param lng - the longitude of the point that was added
     * @param index - the index the point was added at
     * @param pathID - the ID for the path the point was added to
     */
    void pointAddedToMap(double lat, double lng, int index, int pathID);

    /**
     * @brief pathCleared Tells MapWidget that the user has cleared a
     * path from the map.
     * @param pathID - the ID for the path that was cleared
     */
    void pathCleared(int pathID);

    /**
     * @brief pointRemovedFromMap Tells MapWidget that a point with a certain
     * index has been removed from the path with identifier ID.
     * @param index - the index of the point that was removed
     * @param pathID - the ID for the path the point was removed from
     */
    void pointRemovedFromMap(int index, int pathID);

    /**
     * @brief finishedLoading
     */
    void finishedLoading();

    /**
     * @brief clearTable
    */
    void clearTable();

    /**
     * @brief sendDisableEditing
     */
    void sendDisableEditing();

signals:
    //Qt Signals for general use in C++
    /**
     * @brief pointAdded is emitted each time a new point is added to
     * the map.
     * @param lat - the latitude of the new point
     * @param lng - the longitude of the new point
     * @param pathID - the ID of the path the point is a member of
     */
    void pointAdded(double lat, double lng, int pathID);

    /**
     * @brief JSInitialized
     */
    void JSInitialized();

    //JavaScript Signals for use with Cbridge.js
    /**
     * @brief createNewPath Tells the mapping script to create a new path
     * with identifier ID. It is the responsibility of the C++ side (MapWidget)
     * to ensure IDs are kept unique. JavaScript should do nothing (except
     * possibly display an error message) if the ID is already in use.
     * @param pathID - the ID that will be used to identify the new path.
     */
    void createNewPath(int pathID);

    /**
     * @brief setActivePath Tells the mapping script to allow editing to
     * be made to the path with identifier ID. Only one path can be "Active"
     * at a time. By default no paths should be editable.
     * @param pathID - some identifier for which path will be made editable.
     */
    void setActivePath(int pathID);

    /**
     * @brief disableEditing Tells the mapping script to disable editing
     * for all graphs. This only affects edits made through whatever GUI
     * tools the mapping script allows for. By default not paths should
     * be editable.
     */
    void disableEditing();

    /**
     * @brief appendPointToPath Tells the mapping script to append a new
     * waypoint with (lat, lng) to the path with identifier ID.
     * @param lat - the latitude of the new waypoint
     * @param lng - the longitude of the new waypoint
     * @param pathID - the ID of the path to be appended to
     */
    void appendPointToPath(double lat, double lng, int pathID);

    /**
     * @brief insertPointToMap Tells the mapping script to add a new waypoint
     * with (lat, lng) at the specified index to the path with identifier ID.
     * @param lat - the latitude of the new waypoint
     * @param lng - the longitude of the new waypoint
     * @param index - the index the new point is to be inserted
     * @param pathID - the ID of the path this point will be inserted into
     */
    void insertPointToMap(double lat, double lng, int index, int pathID);

    /**
     * @brief removePointFromPath Tells the mapping script to remove a
     * waypoint with the specified index from the list with identifier ID.
     * @param index - the index of the point to be removed.
     * @param pathID - the ID of the path that will have a point removed.
     */
    void removePointFromMap(int index, int pathID);

    /**
     * @brief clearFlightpath Tells the mapping script to delete all of the
     * points in the path with ID equal to pathID.
     * @param pathID - The ID of the flight path to be cleared.
     */
    void clearFlightPath(int pathID);

    /**
     * @brief tableCleared
     */
    void tableCleared();

    /**
     * @brief flightPathSent
     */
    void flightPathSent(int id, QString source);

};

#endif // MAPWIDGET_H
