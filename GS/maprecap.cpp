#include "maprecap.h"

MapRecap::MapRecap(QWidget *parent):QDialog(parent), ui(new Ui::MapRecap) {
    ui->setupUi(this);
    //buttonGroup = new QButtonGroup();

    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);
    ui->webView->load(QUrl("qrc:/res/html/mapsExecution.html"));
    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(5, true);
    ui->tableView->setColumnWidth(2, 42);
    ui->tableView->setColumnWidth(4, 42);
}

MapRecap::~MapRecap(){
    delete ui;
}

/* Since c++/JS bridges are broken when the JS page refreshes this slot
 is used to rebruild the bridge each time when triggered by a
 javaScriptWindowObjectCleared signal from the page frame. Function
 added by Jordan Dickson Feb 21st 2015. */
void MapRecap::addClickListener() {
    std::cout << "listenerAdded!" << std::endl;
    //Creates the bridge called cbridge between the java script object and this class.
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}


void MapRecap::plotPosition(double lat, double lng) {
    ui->webView->page()->mainFrame()->evaluateJavaScript("addActualPath("+QString::number(lat)+","+QString::number(lng)+")");
}

/*  Takes a QString formated (Action,Longitude,LongDirection,Latitude,
LatDirection,Behavior) and extracts the (lat,lng) pair needed to add
a new point to the map. Function added by Jordan Dickson Feb 21st 2015. */
void MapRecap::addPoint(QString string) {
    //Split the string into a list of components separated by ','
    QList<QString> comps = string.split(",");

    //Converts West and South coordinates to negative numbers.
    double lat = comps[3].toDouble();
    double lng = comps[1].toDouble();
    if(comps[2] == "W"){
        lng *= -1.0;
    }
    if(comps[4] == "S"){
        lat *= -1.0;
    }

    //Sends the add point request with its parameters.
    ui->webView->page()->mainFrame()->evaluateJavaScript("addLatLngCoords("+QString::number(lat)+","+QString::number(lng)+")");
}

void MapRecap::on_backButton_clicked() {
    this->done(0);
}


/* Sends a request for the map to clear itself, causing the JavaScript page
to reload itself. This function then cycles through each entry on the table
and enters the coordinates on the map one by one in order. Function added by
Jordan Dickson Feb 14th 2015. */
//Sends clearMap request.
void MapRecap::updateMap() {
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


void MapRecap::closeWindow() {
    this->close();
}


/*  Function called by the JavaScript to add the map data from mission planning.
This is necessary because data cannot be added until the html file is completely
loaded. Jordan 2/21/2015 */
void MapRecap::addNewMap() {

    std::cout << "adding new map" << std::endl;
    updateMap();

    plotPosition(33.6283,-117.8637);
    plotPosition(33.6554,-117.8683);
    plotPosition(33.6760,-117.8320);
    plotPosition(33.6522,-117.8085);
    plotPosition(33.6283,-117.8637);

    addPoint("NONE,117.8637,W,33.6283,N,NONE");
    addPoint("NONE,117.8685,W,33.6554,N,NONE");
    addPoint("NONE,117.8318,W,33.6763,N,NONE");
    addPoint("NONE,117.8094,W,33.6519,N,NONE");
}

/* Passer function for adding entries to the table with coordinates recived
from the JavaScript file. See tablemodel.cpp file for more information.
Added by Jordan Dickson Feb 14th 2015.*/
void MapRecap::addPointToTable(double lat, double lng) {
    model->insertRow(lng,lat);
}


