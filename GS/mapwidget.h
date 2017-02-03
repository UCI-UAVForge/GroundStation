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
    MapWidget();
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
     * @param pathID
     */
    void appendGPSCoordToPath(double lat, double lng, int pathID);

    /**
     * @brief getPath
     * @param pathID
     * @return An ordered list of all the waypoints in a certain path
     */
    QList<Protocol::Waypoint>* getPath(int pathID);

    /**
     * @brief MapURL
     */
    //const QUrl MapURL = QUrl("qrc:/res/html/mapsPlanningGoogle.html");

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

signals:
    /**
     * @brief sendPointToMap
     * @param lat
     * @param lng
     * @param pathID
     */
    void sendPointToMap(double lat, double lng, int pathID);

    /**
     * @brief pointAddedToMap
     * @param lat
     * @param lng
     */
    void pointAddedToMap(double lat, double lng, int pathID);
};

#endif // MAPWIDGET_H
