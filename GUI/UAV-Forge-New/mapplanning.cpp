/* The MapPlanning class is used to layout flightpaths prior to taking them to
 * the Mission Execution stage. The user can enter a series of GPS coordinates
 * either by adding entries to a table or by clicking on a map. The map and
 * table are kept synchronized using a click listener and an update button.
 * Once the flight path is complete the user can send the list of points to
 * Mission Execution.
 *
 * File added sometime prior to April 30 2015.
 */

#include <QString>
#include <QApplication>
#include "mapplanning.h"
#include "ui_mapplanning.h"
#include "popwindowmp.h"
#include "mainwindow.h"
#include "mapexecution.h"

/* MapPlanning usage:

    MapPlanning planner = new MapPlanning();
    planner.showMaximized();

No parameters necessary. The window will not appear until one of the show
functions is called. */
MapPlanning::MapPlanning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapPlanning) {
    ui->setupUi(this);

    //Couldn't get automatic signals/slots working... need to connect manually.
    connect(ui->AddRow,SIGNAL(clicked()),this,SLOT(on_addRow_clicked()));
    connect(ui->RemoveRow,SIGNAL(clicked()),this,SLOT(on_removeRow_clicked()));
    connect(ui->Back,SIGNAL(clicked()),this,SLOT(on_back_clicked()));
    connect(ui->Execute,SIGNAL(clicked()),this,SLOT(on_execute_clicked()));
    connect(ui->ClearPath,SIGNAL(clicked()),this,SLOT(on_clearPath_clicked()));
    connect(ui->Update,SIGNAL(clicked()),this,SLOT(on_update_clicked()));

    //Recreates the c++/JS bridge when the JavaScript window is refreshed
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()));

    ui->webView->load(QUrl("qrc:/res/html/mapsPlanning.html"));

    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());
}

/* Class destructor */
MapPlanning::~MapPlanning() {
    delete ui;
    delete model;
    delete popup;
}

/* Since c++/JS bridges are broken when the JS page refreshes this slot is used
 to rebuild the bridge each time when triggered by a javaScriptWindowObjectCleared
 signal from the page frame.

 Function added by Jordan Dickson Feb 14th 2015. */
void MapPlanning::addClickListener() {
    //Creates the bridge called cbridge between the java script object and this class.
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}


/* Triggered by the "Execute" button. This function creates a popup window
 asking for confirmation before sending corrdinates to the UAV and continuing
 to the execution process. If the user clicks 'yes', the corrdinates are sent
 to the UAV and the Mission Execution window will open with the current
 mission loaded. Clicking 'No' will return the user to the Mission Planning
 window.

 Function added sometime prior to April 30 2015. */
void MapPlanning::on_execute_clicked() {
    //popup = new PopWindowMP(getTableAsStrings());
    //connect(popup,SIGNAL(windowClosed()),this,SLOT(closeWindow()));
    mapexecution *mapExecution = new mapexecution(getTableAsStrings());
    this->close();
    mapExecution->showFullScreen();
}

/* Triggered by the "+" button. Causes an map update and adds a new empty row
 to the table for entering points by keyboard. The newly entered point will not
 appear on the map until the next map update.

 Function added sometime prior to April 30 2015. */
void MapPlanning::on_addRow_clicked() {
    updateMap();
    model->insertRow();
}

/* Triggered by the "-" button. Removes the currently selected row from the
 table and causes a map update.

 Function added sometime prior to April 30 2015. */
void MapPlanning::on_removeRow_clicked() {
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    model->removeRows(indexes);
    updateMap();
}

/* Triggered by the "Update" button. Causes a map update.

 Function added sometime prior to April 30 2015. */
void MapPlanning::on_update_clicked() {
     updateMap();
}

/* Triggered by the "Back" button. Closes the current window and returns the
 user to the MainWindow UI. All data stored in the table and map will be lost.

 Function added sometime prior to April 30 2015. */
void MapPlanning::on_back_clicked() {
    MainWindow *mainwindow = new MainWindow();
    mainwindow->showFullScreen();
    this -> close();
// <<<<<<< HEAD
    mainwindow->showFullScreen();
// =======
// >>>>>>> 4657e7a59454d03e9c48944178e4cdad163200a6
}

/* Triggered by the "Clear Path" button. Removes all the rows in the table,
 then causes a map update.

 Function added by Arash sometime prior to April 30 2015.
 Edited by Jordan Dickson April 30 2015. */
void MapPlanning::on_clearPath_clicked() {
    model->removeRows(0,model->getList().length());
    updateMap();
}

/* Sends a request for the map to clear itself, causing the JavaScript page
 to reload itself with an empty map. This function then cycles through each
 entry currently on the table and enters the coordinates on the map one by
 one in order.

 Function added by Jordan Dickson Feb 14 2015. */
void MapPlanning::updateMap() {

    //Sends clearMap request.
    ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");
    //Loops through table entries
    for(int i = 0; i < model->getList().size(); i++){
        QList<QString> list = model->getList()[i];
        //Converts West and South coordinates to negative numbers.
        double lat = list[3].toDouble();
        double lng = list[1].toDouble();
        if(list[2] == "W"){
            lng *= -1.0;
        }
        if(list[4] == "S"){
            lat *= -1.0;
        }
        //Sends the add point request with its parameters.
        ui->webView->page()->mainFrame()->evaluateJavaScript("addLatLngCoords("+QString::number(lat)+","+QString::number(lng)+")");
    }
}

/* Converts the table into a list of strings formatted with each row of the
 table being its own entry in the list, and each entry on the list represented
 as (Action,Longitude,E/W,Latitude,N/S,Behavior). This is the same formatting
 used in Mission Execution to add waypoints to the map. Very similar to
 getTableData().

 Returns a QList of QStrings.

 Function added by Jordan Dickson Feb 21 2015. */
QList<QString> MapPlanning::getTableAsStrings(){
    QList<QString> output;
    QList<QList<QString> > table = model->getList();
    for(int i = 0;i < table.length();i++) {
        QList<QString> row = table[i];
        QString formattedRow;
        for(int i = 0; i < row.length(); i++){
            if (i == 0){
                formattedRow += row[i];
            } else {
                formattedRow += "," + row[i];
            }
        }
        output<<formattedRow;
    }
    return output;
}

/* Gets the data of the table and formats it for the database. This function
 iterates through each row, gets each string, cancatinates them and appends
 them to a new list(tableData list). Very similar to getTableAsStrings().

 Returns [[string,string...],[string,string...]...]

 Function added by Arash sometime prior to April 30 2015*/
QList<QList<QString> > MapPlanning::getTableData(){
    QList<QList<QString> > tableData;

    for (int i = 0; i < model->getList().size(); i++){

        QList<QString> tableRow = model->getList()[i];

        QString action = tableRow[0];
        QString lng = tableRow[1];
        QString eastWest = tableRow[2];
        QString lat = tableRow[3];
        QString northSouth = tableRow[4];
        QString behavior = tableRow[5];

        QList<QString> rowString;
        rowString<<action<<lng<<eastWest<<lat<<northSouth<<behavior;

        tableData.append(rowString);

    }
    return tableData;
}

/* This function is used to close this window if the user decides to execute
 the panned mission.

 Function added by Jordan Dickson sometime prior to April 30 2015. */
void MapPlanning::closeWindow(){
    this->close();
}

/* Passer function for adding entries to the table with coordinates recived
 from the JavaScript file. See tablemodel.cpp file for more information on
 how the points are added, and see mapsPlanning.html for this function's calls.

 Function added by Jordan Dickson Feb 14th 2015.*/
void MapPlanning::addPointToTable(double lat, double lng) {
    model->insertRow(lng,lat);
}
