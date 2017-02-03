#include "mapexecution.h"
#include <iostream>

MapExecution::MapExecution(QWidget *parent) :MapExecution(new FlightPath,parent){}

MapExecution::MapExecution(FlightPath* flightPath, QWidget *parent):
    QDialog(parent),
    myServer(&MyMessageBox,&myMission),
    ui(new Ui::MapExecution),
    prevTime(),
    myFlightPath(*flightPath),
    myMission(myFlightPath){

    missionStarted = false;
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();

    map = new MapWidget();
    ui->graphicsView->setViewport(map);

    //MyMessageBox.fetch_from_table(strings);

    for (TimedAction *a : myFlightPath){
        MyMessageBox.addActionPacket(*(a->first));
    }
    //initate clock timer
    ui->clock->initiate(MyMessageBox.timer);

    ui->StatusConsole->initiate(&MyMessageBox, this);
    //display widgets

    //std::vector<Protocol::ActionPacket> test_actions = MyMessageBox.get_action_packets();

    conTime = new QTimer(this);
    connect(conTime, SIGNAL(timeout()), this, SLOT(updateStatusIndicator()));
    conTime->start(1000);
    int pack_number = 1;

    //for(auto i : test_actions){
    //    Protocol::Waypoint test_wp;
    //    test_wp = i.GetWaypoint();
    //    std::cout << pack_number << " Latitude: " << test_wp.lat << " Longitude: " << test_wp.lon << std::endl;
    //    ++pack_number;
    //}

    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());

    /*
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(5, true);
    ui->tableView->setColumnWidth(2, 42);
    ui->tableView->setColumnWidth(4, 42);
    */

    //connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);
    //ui->webView->load(QUrl("qrc:/res/html/mapsPlanning.html"));
    //qDebug() << "Map Execution Constructor URL: " << ui->webView->url();

    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()), Qt::UniqueConnection);
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()), Qt::UniqueConnection);
    connect(ui->finishButton, SIGNAL(clicked()), this, SLOT(on_finishButton_clicked()), Qt::UniqueConnection);
    myServer.openServer(QHostAddress::LocalHost,20715);
}


MapExecution::~MapExecution() {
    delete ui;
    delete model;
    delete map;
    conTime->disconnect();
    conTime->deleteLater();
}

// finish button
// redirect to mission recap window
void MapExecution::on_finishButton_clicked() {
    std::cout<<"Finish button clicked!" << std::endl;

    myServer.closeServer();

    emit timeToStartMapRecap();

    /* Commented out for QtTabTest.cpp
    this->close();
    myServer.closeServer();


    MapRecap* x = new MapRecap(&myMission);
    x->showFullScreen();
    */
}

// stop button
/* Sends the point (999.99,999.99) to the UAV. Used as a code for stop.
Function added by Jordan Dickson March 9th 2015. */
void MapExecution::on_stopButton_clicked() {
    Protocol::ActionPacket stop;
    stop.SetAction(Protocol::ActionType::Stop);
    myServer.sendPacket(&stop,0);
}

// return home button
// redirect to main window
void MapExecution::on_returnHomeButton_clicked() {
    Protocol::ActionPacket rtnHome;
    rtnHome.SetAction(Protocol::ActionType::AddWaypoint);
    myServer.sendPacket(&rtnHome,0);
}

// cancel button
// redirect to mission planning
void MapExecution::on_cancelButton_clicked() {
    //ui->webView->page()->mainFrame()->evaluateJavaScript("cancelFlight()");
//    ui->webView->load(QUrl("qrc:/res/html/mapsPlanning.html"));
    this->done(1);
}

// back button
// redirect to mission planning
// REPURPOSED TO BE A MISSION START BUTTON
void MapExecution::on_backButton_clicked() {

    //-old code-
    //this->done(1);

    //-start button code-
    if (!missionStarted){
        missionStarted = true;
        sendFlightPlan();
        //ui->webView->page()->mainFrame()->evaluateJavaScript("startFlight()");
        myServer.startServer();
    }
}

void MapExecution::sendFlightPlan(){
    std::vector<Protocol::ActionPacket> packets = MyMessageBox.get_action_packets();

    for (Protocol::ActionPacket pack : packets){
        pack.SetAction(Protocol::ActionType::AddWaypoint);
        myServer.sendPacket(&pack);
    }
}

void MapExecution::drawFlightPath(FlightPath *flightPath) {
    //ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");
    QList<Protocol::Waypoint> *points = flightPath->getOrderedWaypoints();
    for (Protocol::Waypoint wp : *points){
        sendCoordToJSMap(wp.lat,wp.lon,0);
    }
<<<<<<< HEAD
    ui->webView->page()->mainFrame()->evaluateJavaScript("plotFlightPlan()");
=======
    //ui->webView->page()->mainFrame()->evaluateJavaScript("plotPolyline()");
>>>>>>> master
    delete points;
}

/* Since c++/JS bridges are broken when the JS page refreshes this slot
 is used to rebruild the bridge each time when triggered by a
 javaScriptWindowObjectCleared signal from the page frame. Function
 added by Jordan Dickson Feb 21st 2015. */
void MapExecution::addClickListener() {
    //Creates the bridge called cbridge between the java script object and this class.
    //ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}
Mission MapExecution::getMyMission() const
{
    return myMission;
}

void MapExecution::setMyMission(const Mission &value)
{
    myMission = value;
}

/*  Function called by the JavaScript to add the map data from mission planning.
This is necessary because data cannot be added until the html file is completely
loaded. Jordan 2/21/2015 */
void MapExecution::addNewMap() {
    std::cout << "Add new map called!" << std::endl;
    drawFlightPath(&myFlightPath);
}

/*  Sends a (latitude,longitude) pair to the map to be plotted.
Used for telemetry. */
void MapExecution::plotPosition(double lat, double lng) {
    updateTable(lat,lng);
    ui->webView->page()->mainFrame()->evaluateJavaScript("plotUAVPosition(" + QString::number(lat) + "," + QString::number(lng) + ")");
}

void MapExecution::sendCoordToJSMap(double lat, double lng, int mapID){
<<<<<<< HEAD
    ui->webView->page()->mainFrame()->evaluateJavaScript("addFlightPlan("+QString::number(lat)+","+QString::number(lng)+","+QString::number(mapID)+")");
=======
    //ui->webView->page()->mainFrame()->evaluateJavaScript("plotPointOnMap("+QString::number(lat)+","+QString::number(lng)+","+QString::number(mapID)+")");
>>>>>>> master
}

void MapExecution::updateTable(double lat, double lng) {
    model->insertRow(lng, lat);
    ui->tableView->scrollToBottom();
}

/*Change status indicator using inputted x */
void MapExecution::updateStatusIndicator()
{
    int x;
    if (MyMessageBox.get_telem_packets().empty())
        x = 2;
    else
        x = 0;
    ui->StatusIndicator->clear();
    switch(x)
    {
        case 0:
            ui->StatusIndicator->setStyleSheet("background-color:green");
            ui->StatusIndicator->appendPlainText("\nConnected to UAV");
            break;
        case 1:
            ui->StatusIndicator->setStyleSheet("background-color:yellow");
            break;
        case 2:
            ui->StatusIndicator->setStyleSheet("background-color:red");
            ui->StatusIndicator->appendPlainText("\nNo Connection to UAV " + QString::number(MyMessageBox.timer.elapsed()/1000));
            break;
        default:
            ui->StatusIndicator->setStyleSheet("background-color:black;");
    }
}

//TODO Make this function a little safer. Do we really wanna make a new object every damn time?
//- Roman Parise
MapRecap * MapExecution::getMapRecap() {

    return new MapRecap(&myMission);

}
