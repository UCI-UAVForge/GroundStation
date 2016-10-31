#include "mapplanning.h"

MapPlanning::MapPlanning(QWidget *parent) : QDialog(parent), ui(new Ui::MapPlanning) {
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();

/*
 * Recreates the C++/JS bridge when the JavaScript window is refreshed
 */
    //connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);
    ui->webView->load(QUrl("qrc:/res/html/mapsPlanning.html"));

    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());
    //ui->tableView->setColumnHidden(0, true);
    //ui->tableView->setColumnHidden(5, true);
    //ui->tableView->setColumnWidth(2, 42);
    //ui->tableView->setColumnWidth(4, 42);

    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()), Qt::UniqueConnection);
    connect(ui->clearTableButton, SIGNAL(clicked()), this, SLOT(on_clearTableButton_clicked()), Qt::UniqueConnection);
    connect(ui->executeButton, SIGNAL(clicked()), this, SLOT(on_executeButton_clicked()), Qt::UniqueConnection);
}

MapPlanning::~MapPlanning() {
    delete ui;
}

/*
 * Since C++/JS bridges are broken when the JS page refreshes this slot
 * is used to rebruild the bridge each time when triggered by a
 * javaScriptWindowObjectCleared signal from the page frame. Function
 * added by Jordan Dickson Feb 14th 2015.
 */
void MapPlanning::addClickListener() {
    //Creates the bridge called cbridge between the java script object and this class.
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}

// execution button
// redirect to mission execution window
void MapPlanning::on_executeButton_clicked() {

    //emit timeToStartMapExecution();

    /* Commented out for QtTabTest.cpp
     */
    MapExecution* mapExecution = new MapExecution(getTableAsFlightPath());
    this->close();
    mapExecution->showFullScreen();



//    ConnectionDialog * connectionDialog = new ConnectionDialog();
//    connectionDialog -> show();


    //this->done(2);
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

// update button
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
    delete model;
    model = new TableModel();
    ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");
    ui->tableView->setModel(model);
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

FlightPath *MapPlanning::getTableAsFlightPath(){
    FlightPath *newFP = new FlightPath();

    QList<QList<QString> > table = model->getList();
    for(int i = 0; i < table.length(); i++) {
        QList<QString> row = table[i];
        Protocol::Waypoint wp;
        wp.lon = row[1].toDouble();
        wp.lon *= (row[2].at(0)=='E')?1:-1;

        wp.lat = row[3].toDouble();
        wp.lat *= (row[4].at(0)=='N')?1:-1;

        wp.alt = row[5].toDouble();

        wp.speed = row[6].toDouble();

        newFP->addNavAction(wp,i*10);
    }

    return newFP;
}

void MapPlanning::closeWindow() {
    this->close();
}

/* Passer function for adding entries to the table with coordinates recived
from the JavaScript file. See tablemodel.cpp file for more information.
Added by Jordan Dickson Feb 14th 2015.*/
void MapPlanning::addPointToTable(double lat, double lng) {

    model->insertRow(lng,lat);

    //David Moe

    ui->tableView->scrollToBottom();

}
