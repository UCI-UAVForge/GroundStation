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
#include <QDebug>

MapWidget::MapWidget(QWidget *parent): QWebEngineView(parent),
    server(QStringLiteral("MapServer"), QWebSocketServer::NonSecureMode),
    clientWrapper(&server)
{
    this->connect(this, &MapWidget::loadStarted, this, &MapWidget::loadStartedSlot);
    //this->connect(this, &MapWidget::loadFinished, this, &MapWidget::loadFinishedSlot);

    loading = true;

    lists = new QList<QList<Protocol::Waypoint> >;

    // setup the QWebSocketServer
    if (!server.listen(QHostAddress::LocalHost, 20270)) {
        qDebug() << "Attempted to open 2 MapWidgets!";
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

void MapWidget::appendGPSCoordToPath(double lat, double lng, int pathID) {
    emit appendPointToPath(lat,lng,pathID);
}

QList<Protocol::Waypoint> *MapWidget::getPath(int pathID) {
    return new QList<Protocol::Waypoint>();
}

void MapWidget::loadFinishedSlot() {
    //loading = false;
    //finishedLoading();
}

void MapWidget::loadStartedSlot() {
    loading= true;
}

//Public "emitters" used by C++ to communicate with JS

void MapWidget::addPointToMap(double lat, double lng, int index, int pathID){
    emit insertPointToMap(lat,lng,index,pathID);
}

void MapWidget::appendPointToMap(double lat, double lng, int pathID){
    qDebug() << "Adding point (" << lat << "," << lng << ") to path " << pathID;
    emit appendPointToPath(lat,lng,pathID);
}

void MapWidget::sendCreateNewPath(int id){
    emit createNewPath(id);
}

void MapWidget::sendSetActivePath(int id){
    emit setActivePath(id);
}

void MapWidget::sendClearFlightPath(int pathID){
    emit clearFlightPath(pathID);
}

void MapWidget::sendDisableEditing(){
    emit disableEditing();
}

void MapWidget::clearTable(){
    emit tableCleared();
}

void MapWidget::disconnectWebSocket(){
    server.close();
}

void MapWidget::addFlightPath(FlightPath* fp, int id, QString source){
    QList<Protocol::Waypoint> *list = fp->getOrderedWaypoints();
    for(int i = 0; i < list->length(); i++){
        Protocol::Waypoint wp = list->at(i);
        emit appendPointToPath(wp.lat,wp.lon,id);
    }
    emit flightPathSent(id, source);
    delete list;
}

//Public slots called by JavaScript

void MapWidget::pointAddedToMap(double lat, double lng, int index, int pathID){
    /// \todo include index in this signal
    emit pointAdded(lat,lng,pathID);
}

void MapWidget::pathCleared(int pathID){

}

void MapWidget::pointRemovedFromMap(int index, int pathID){

}

void MapWidget::finishedLoading() {
    loading = false;
    emit JSInitialized();
}

