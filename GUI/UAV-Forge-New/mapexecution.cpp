#include "mapexecution.h"
#include "ui_mapexecution.h"
#include "missionrecap.h"
#include "options.h"
#include "mainwindow.h"
#include <QWebFrame>

mapexecution::mapexecution(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mapexecution)
{
    ui->setupUi(this);
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()));
    ui->webView->load(QUrl("qrc:/res/html/mapsExecution.html"));

}

mapexecution::~mapexecution()
{
    delete ui;
}

void mapexecution::finishClicked()
{
    this->close();
    MissionRecap *missionRecap = new MissionRecap();
    missionRecap->show();
}

void mapexecution::returnHomeClicked()
{
    this->close();
}

void mapexecution::cancelClicked()
{
    this->close();
}

void mapexecution::on_pushButton_clicked()
{
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->show();
}

void mapexecution::setMap(QList<QString> list) {
    /* Sends a request for the map to clear itself, causing the JavaScript page
    to reload itself. This function then cycles through each entry in the string
    list and sends it to the addPoint(QString) function to be added to the map.
    Function added by Jordan Dickson Feb 21st 2015. */

    //Sends clearMap request.
    ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");

    //Loops through list entries
    for(int i = 0; i < list.length(); i++){
        addPoint(list[i]);
    }
}

void mapexecution::addPoint(QString string){
    /*  Takes a QString formated (Action,Longitude,LongDirection,Latitude,
    LatDirection,Behavior) and extracts the (lat,lng) pair needed to add
    a new point to the map. Function added by Jordan Dickson Feb 21st 2015. */

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

void mapexecution::addClickListener() {
    /* Since c++/JS bridges are broken when the JS page refreshes this slot
     is used to rebruild the bridge each time when triggered by a
     javaScriptWindowObjectCleared signal from the page frame. Function
     added by Jordan Dickson Feb 21st 2015. */

    //Creates the bridge called cbridge between the java script object and this class.
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);

}

void mapexecution::addNewMap(){
    /*  Test function used to add points to the mission execution map.
    Delete later.
    */
    QList<QString> newMap;
    newMap<<"Action 1,50,W,40,N,Behavior 1"<<"Action 1,55,W,42,N,Behavior 1";
    setMap(newMap);
}

