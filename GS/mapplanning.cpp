#include "mapplanning.h"

MapPlanning::MapPlanning(QWidget *parent) : QDialog(parent), ui(new Ui::MapPlanning) {
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();

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

// execution button
// redirect to mission execution window
void MapPlanning::on_executeButton_clicked() {
    this->done(2);
}

// + button
void MapPlanning::on_addButton_clicked() {
    model->insertRow();
}

// - button
void MapPlanning::on_deleteButton_clicked() {
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    model->removeRows(indexes);
    updateMap();
}

// update buttun
void MapPlanning::on_updateTableButton_clicked() {
     updateMap();
}

// back button
// redirect to main window
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

void MapPlanning::closeWindow() {
    this->close();
}

/* Passer function for adding entries to the table with coordinates recived
from the JavaScript file. See tablemodel.cpp file for more information.
Added by Jordan Dickson Feb 14th 2015.*/
void MapPlanning::addPointToTable(double lat, double lng) {
    model->insertRow(lng,lat);
}
