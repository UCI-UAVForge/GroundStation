/**
  @author Jordan Dickson
  */

#include "mapwidget.h"
#include <QWebSocket>
#include <QWebSocketServer>
#include <iostream>
#include <QTimer>
#include <QList>

#include "ackpacket.h"

MapWidget::MapWidget(QWidget *parent): QWebEngineView(parent),
    server(QStringLiteral("MapServer"), QWebSocketServer::NonSecureMode),
    clientWrapper(&server)
{
    this->connect(this, &MapWidget::loadStarted, this, &MapWidget::loadStartedSlot);
    this->connect(this, &MapWidget::loadStarted, this, &MapWidget::loadFinishedSlot);

    lists = new QList<QList<Protocol::Waypoint> >;

    // setup the QWebSocketServer
    if (!server.listen(QHostAddress::LocalHost, 20270)) {
        qFatal("Failed to open web socket server.");
    }

    // setup the channel
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel
    channel.registerObject(QStringLiteral("cbridge"), this);

    // open a browser window with the client HTML page
    load(MapURL);
}

MapWidget::~MapWidget() {
    //we might need the destructor to delete each of the inner lists...
        //but then again maybe not... that's what testing is for
    delete lists;
}

bool MapWidget::ready() {
    return !loading;
}

int MapWidget::createNewPath() {
    return 0;
}

void MapWidget::appendGPSCoordToPath(double lat, double lng, int pathID) {

}

QList<Protocol::Waypoint> *MapWidget::getPath(int pathID) {
    return new QList<Protocol::Waypoint>();
}

void MapWidget::loadFinishedSlot() {
    loading = false;
}

void MapWidget::loadStartedSlot() {
    loading= true;
}

void MapWidget::addPointToTable(double lat, double lng){
    //QTextStream(stdout)<<lat << "," << lng;
    emit pointAddedToMap(lat,lng,0);
}

void MapWidget::clearMap(){
    emit clearFlightPath(0);
}

void MapWidget::disconnectWebSocket(){
    server.close();
}

void MapWidget::addFlightPath(FlightPath* fp, int index){
    QList<Protocol::Waypoint> *list = fp->getOrderedWaypoints();

    for(int i = 0; i < list->length(); i++){
        Protocol::Waypoint wp = list->at(i);
        emit sendPointToMap(wp.lat,wp.alt,index);
    }

    delete list;
}
