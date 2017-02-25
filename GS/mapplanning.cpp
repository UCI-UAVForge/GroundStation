#include "mapplanning.h"
#include <QWebEngineView>
#include <QWebSocketServer>
#include "mapwidget.h"
#include <iostream>
#include "tablewidget.h"

MapPlanning::MapPlanning(QWidget *parent) : QDialog(parent), ui(new Ui::MapPlanning) {
    ui->setupUi(this);
    this->connect(ui->mapView, &MapWidget::pointAddedToMap, ui->tableView, &TableWidget::appendRow);
    this->connect(ui->mapView, &MapWidget::tableCleared, ui->tableView, &TableWidget::clearTable);
    this->connect(ui->clearTableButton, &QPushButton::clicked, ui->tableView, &TableWidget::clearTable);
    this->connect(ui->clearTableButton, &QPushButton::clicked, ui->mapView, &MapWidget::clearMap);
    this->connect(ui->tableView, &TableWidget::selectedData, ui->mapView, &MapWidget::addFlightPath);
}

MapPlanning::~MapPlanning() {
    delete ui;
}

/*
 * Since C++/JS bridges are broken when the JS page refreshes this slot
 * is used to rebruild the bridge each time when triggered by a
 * javaScriptWindowObjectCleared signal from the page frame. Function
 * added by Jordan Dickson Feb 14th 2015.
 * Unused after 5.7 update -Jordan Dickson Feb 3 2017
 */
void MapPlanning::addClickListener() {
    //Creates the bridge called cbridge between the java script object and this class.
    //ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}

// execution button
// redirect to mission execution window
void MapPlanning::on_executeButton_clicked() {
    ui->mapView->disconnectWebSocket();
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
    this->close();
}

/* Passer function for adding entries to the table with coordinates recived
from the JavaScript file. See tablemodel.cpp file for more information.
Added by Jordan Dickson Feb 14th 2015.*/
void MapPlanning::addPointToTable(double lat, double lng) {
    ui->tableView->appendRow(lat,lng);
}

void MapPlanning::clearTable() {
    ui->tableView->clearTable();
    ui->mapView->clearMap();
}
