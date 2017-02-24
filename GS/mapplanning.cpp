#include "mapplanning.h"
#include <QWebEngineView>
#include <QWebSocketServer>
#include "mapwidget.h"
#include <iostream>
#include "tablewidget.h"

MapPlanning::MapPlanning(QWidget *parent) : QDialog(parent), ui(new Ui::MapPlanning) {
    ui->setupUi(this);
    this->connect(ui->mapView, &MapWidget::pointAdded, ui->tableView, &TableWidget::appendRow);
    this->connect(ui->mapView, &MapWidget::JSInitialized, this, &MapPlanning::setupMapPaths);
    this->connect(ui->clearTableButton, &QPushButton::clicked, ui->tableView, &TableWidget::clearTable);
    this->connect(ui->clearTableButton, &QPushButton::clicked, ui->mapView, &MapWidget::clearFlightPath);
}

MapPlanning::~MapPlanning() {
    delete ui;
}

// execution button
// redirect to mission execution window
void MapPlanning::on_executeButton_clicked() {
    ui->mapView->disconnectWebSocket();
    //this->done(2);
    MapExecution* mapExecution = new MapExecution(getTableAsFlightPath());
    this->close();
    mapExecution->showFullScreen();
}

// + button
void MapPlanning::on_addButton_clicked() {
    //model->insertRow();
}

// - button
void MapPlanning::on_deleteButton_clicked() {
    ui->tableView->removeSelectedRows();
}

// update button
void MapPlanning::on_updateTableButton_clicked() {
     updateMap();
}

// back button
// redirect to main window
void MapPlanning::on_backButton_clicked() {
    ui->mapView->disconnectWebSocket();
    this->done(0);
}

/* Sends a request for the map to clear itself, causing the JavaScript page
to reload itself. This function then cycles through each entry on the table
and enters the coordinates on the map one by one in order. Function added by
Jordan Dickson Feb 14th 2015. */
void MapPlanning::updateMap() {
    FlightPath *fp = ui->tableView->getTableAsFlightPath();
    ui->mapView->addFlightPath(fp);
    delete fp;
}

FlightPath *MapPlanning::getTableAsFlightPath(){
    return ui->tableView->getTableAsFlightPath();
}

void MapPlanning::closeWindow() {
    ui->mapView->disconnectWebSocket();
    this->close();
}

/* Passer function for adding entries to the table with coordinates recived
from the JavaScript file. See tablemodel.cpp file for more information.
Added by Jordan Dickson Feb 14th 2015.*/
void MapPlanning::addPointToTable(double lat, double lng) {
    ui->tableView->appendRow(lat,lng);
}

void MapPlanning::setupMapPaths(){
    ui->mapView->sendCreateNewPath(0);
    ui->mapView->sendSetActivePath(0);
}

void MapPlanning::clearTable() {
    ui->tableView->clearTable();
    /// \todo make the argument in clearFlightPath mean something (tie it to a variable)
    ui->mapView->clearFlightPath(0);
}
