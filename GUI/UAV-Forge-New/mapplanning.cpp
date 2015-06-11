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


/* MapPlanning usage:

    MapPlanning planner = new MapPlanning();
    planner.showMaximized();

No parameters necessary. The window will not appear until one of the show
functions is called. */


MapPlanning::MapPlanning(QWidget *parent) : QDialog(parent), ui(new Ui::MapPlanning) {
    ui->setupUi(this);


//    //connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonWasClicked(int)));
//    //delete = new  (row)
//    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_7_clicked()));

//    //Recreates the c++/JS bridge when the JavaScript window is refreshed
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);

    ui->webView->load(QUrl("qrc:/res/html/mapsPlanning.html"));

    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(on_addButton_clicked()), Qt::UniqueConnection);
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()), Qt::UniqueConnection);
    connect(ui->clearMapButton, SIGNAL(clicked()), this, SLOT(on_clearMapButton_clicked()), Qt::UniqueConnection);
    connect(ui->clearTableButton, SIGNAL(clicked()), this, SLOT(on_clearTableButton_clicked()), Qt::UniqueConnection);
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(on_deleteButton_clicked()), Qt::UniqueConnection);
    connect(ui->executeButton, SIGNAL(clicked()), this, SLOT(on_executeButton_clicked()), Qt::UniqueConnection);
    connect(ui->updateTableButton, SIGNAL(clicked()), this, SLOT(on_updateTableButton_clicked()), Qt::UniqueConnection);
}

/* Class destructor */
MapPlanning::~MapPlanning() {
    delete ui;
}


//<<<<<<< HEAD
//void MapPlanning::buttonWasClicked(int buttonID)
//{


/* Since c++/JS bridges are broken when the JS page refreshes this slot
 is used to rebruild the bridge each time when triggered by a
 javaScriptWindowObjectCleared signal from the page frame. Function
 added by Jordan Dickson Feb 14th 2015. */
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
void MapPlanning::on_executeButton_clicked() {
    this->done(2);
}

/* Triggered by the "+" button. Causes an map update and adds a new empty row
 to the table for entering points by keyboard. The newly entered point will not
 appear on the map until the next map update.

 Function added sometime prior to April 30 2015. */
void MapPlanning::on_addButton_clicked() {
    model->insertRow();
}

/* Triggered by the "-" button. Removes the currently selected row from the
 table and causes a map update.

 Function added sometime prior to April 30 2015. */
void MapPlanning::on_deleteButton_clicked() {
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    model->removeRows(indexes);
    updateMap();
}




///* Triggered by the "Clear Path" button. Removes all the rows in the table,
// then causes a map update.

// Function added by Arash sometime prior to April 30 2015.
// Edited by Jordan Dickson April 30 2015. */
//void MapPlanning::on_clearPath_clicked() {
//    model->removeRows(0,model->getList().length());
//    updateMap();
//}

/* Sends a request for the map to clear itself, causing the JavaScript page
 to reload itself with an empty map. This function then cycles through each
 entry currently on the table and enters the coordinates on the map one by
 one in order.

 Function added by Jordan Dickson Feb 14 2015. */

/* Triggered by the "Update" button. Causes a map update.

 Function added sometime prior to April 30 2015. */
void MapPlanning::on_updateTableButton_clicked() {
     updateMap();
}

/* Triggered by the "Back" button. Closes the current window and returns the
 user to the MainWindow UI. All data stored in the table and map will be lost.

 Function added sometime prior to April 30 2015. */
void MapPlanning::on_backButton_clicked() {
    this->done(0);
}

// clear table button
/* Clears all the rows in the table, basically makes a new table
 * Arash
 */
void MapPlanning::on_clearTableButton_clicked() {
    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());
}

//clear map button
/* Clears the map
 * Arash
 */
void MapPlanning::on_clearMapButton_clicked() {
     //ui->webView->load(QUrl("qrc:/res/html/mapsPlanning.html"));
     ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");
}

/* Sends a request for the map to clear itself, causing the JavaScript page
to reload itself. This function then cycles through each entry on the table
and enters the coordinates on the map one by one in order. Function added by
Jordan Dickson Feb 14th 2015. */
//Sends clearMap request.
void MapPlanning::updateMap() {
    ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");
    //Loops through table entries
    for(int i = 0; i < model->getList().size(); i++) {
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


/*  Converts the table into a list of strings formatted with each row of the
table being its own entry in the list, and each entry on the list represented
as (Action,Longitude,LongDirection,Latitude,LatDirection,Behavior). This is
the same formatting used in Mission Execution to add waypoints to the map.
Function added by Jordan Dickson Feb 21st 2015. */
QList<QString> MapPlanning::getTableAsStrings() {
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


/* A function to get the data of the table and send it to database.
 * This function iterates through each row, gets each string, cancatinates them
 * and appends them to a new list(tableData list). Returns  [[strings],[strings]...]
 * Arash
 * Overlapped with Jordan's getTabelAsStrings function
 */
QList<QList<QString> > MapPlanning::getTableData() {
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

void MapPlanning::closeWindow() {

    this->close();
}

/* Passer function for adding entries to the table with coordinates recived
<<<<<<< HEAD
 from the JavaScript file. See tablemodel.cpp file for more information on
 how the points are added, and see mapsPlanning.html for this function's calls.

 Function added by Jordan Dickson Feb 14th 2015.*/

void MapPlanning::addPointToTable(double lat, double lng) {
    model->insertRow(lng,lat);
}
