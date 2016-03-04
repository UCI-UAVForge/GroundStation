#include "mapexecution.h"

MapExecution::MapExecution(QList<QString> strings, QWidget *parent) :
        QDialog(parent),
        myServer(&MyMessageBox),
        ui(new Ui::MapExecution),
        prevTime() {
    missionStarted = false;
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();
    MyMessageBox.fetch_from_table(strings);

    //initate clock timer
    ui->clock->initiate(MyMessageBox.timer);

    ui->StatusConsole->initiate(&MyMessageBox, this);
    //display widgets

    std::vector<Protocol::ActionPacket> test_actions = MyMessageBox.get_action_packets();
    QTimer *conTime = new QTimer(this);
    connect(conTime, SIGNAL(timeout()), this, SLOT(updateStatusIndicator()));
    conTime->start(1000);
    int pack_number = 1;

    for(auto i : test_actions){
        Protocol::Waypoint test_wp;
        test_wp = i.GetWaypoint();
        std::cout << pack_number << " Latitude: " << test_wp.lat << " Longitude: " << test_wp.lon << std::endl;
        ++pack_number;
    }

    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());

    mapStrings = strings;
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);
    ui->webView->load(QUrl("qrc:/res/html/mapsExecution.html"));

    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()), Qt::UniqueConnection);
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()), Qt::UniqueConnection);
    connect(ui->finishButton, SIGNAL(clicked()), this, SLOT(on_finishButton_clicked()), Qt::UniqueConnection);
    connect(ui->returnHomeButton, SIGNAL(clicked()), this, SLOT(on_returnHomeButton_clicked()), Qt::UniqueConnection);
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(on_stopButton_clicked()), Qt::UniqueConnection);

    myServer.openServer(QHostAddress::LocalHost,20715);
    //connect(&myServer.networkListener,SIGNAL(sendCoordinates()),this,SLOT(sendFlightPlan()));
    //connect(&myServer.networkListener,SIGNAL(logTelemetry(QString)),this,SLOT(newTelemCoord(QString)));
}

MapExecution::MapExecution(QWidget *parent) :MapExecution(QList<QString>(),parent){
}


MapExecution::~MapExecution() {
    delete ui;
    delete model;
}

// finish button
// redirect to mission recap window
void MapExecution::on_finishButton_clicked() {
    this->done(3);
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
        myServer.startServer();
    }
}

void MapExecution::newTelemCoord(QString msgString){
    double lat = msgString.split(',').at(0).toDouble();
    double lng = msgString.split(',').at(1).toDouble();
    long time = msgString.split(',').at(2).toLong();
    std::cout << time << std::endl;

    plotPosition(lat,lng);
}


void MapExecution::sendFlightPlan(){
    std::vector<Protocol::ActionPacket> packets = MyMessageBox.get_action_packets();

    for (Protocol::ActionPacket pack : packets){
        pack.SetAction(Protocol::ActionType::AddWaypoint);
        myServer.sendPacket(&pack);
    }
}

/* Sends a request for the map to clear itself, causing the JavaScript page
to reload itself. This function then cycles through each entry in the string
list and sends it to the addPoint(QString) function to be added to the map.
Function added by Jordan Dickson Feb 21st 2015. */
void MapExecution::setMap(QList<QString> list) {
    //Sends clearMap request.
    ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");

    //Loops through list entries
    for(int i = 0; i < list.length(); i++){
        addPoint(list[i]);
    }
}

QList<QPair<double,double> > MapExecution::getDoublePairs(QList<QString> strings) {
    QList<QPair<double,double> > returnList;
    for(QString string: strings){
        QList<QString> comps = string.split(",");

        //Converts West and South coordinates to negative numbers.
        double lat = comps[3].toDouble();
        double lng = comps[1].toDouble();
        if(comps[2] == "W") {
            lng *= -1.0;
        }
        if(comps[4] == "S") {
            lat *= -1.0;
        }
        returnList.append(QPair<double,double>(lat,lng));
    }

    return returnList;

}

/*  Takes a QString formated (Action,Longitude,LongDirection,Latitude,
LatDirection,Behavior) and extracts the (lat,lng) pair needed to add
a new point to the map. Function added by Jordan Dickson Feb 21st 2015. */
void MapExecution::addPoint(QString string) {
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

void MapExecution::push_new_point(QString string) {
   QList<QString> points = string.split(",");
}

/* Since c++/JS bridges are broken when the JS page refreshes this slot
 is used to rebruild the bridge each time when triggered by a
 javaScriptWindowObjectCleared signal from the page frame. Function
 added by Jordan Dickson Feb 21st 2015. */
void MapExecution::addClickListener() {
    //Creates the bridge called cbridge between the java script object and this class.
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}

/*  Function called by the JavaScript to add the map data from mission planning.
This is necessary because data cannot be added until the html file is completely
loaded. Jordan 2/21/2015 */
void MapExecution::addNewMap() {
    setMap(mapStrings);
    //ui->webView->page()->mainFrame()->evaluateJavaScript("simulateInput()");
}

/*  Sends a (latitude,longitude) pair to the map to be plotted.
Used for telemetry. */
void MapExecution::plotPosition(double lat, double lng) {
    updateTable(lat,lng);
    ui->webView->page()->mainFrame()->evaluateJavaScript("addActualPath("+QString::number(lat)+","+QString::number(lng)+")");
}

void MapExecution::updateTable(double lat, double lng) {
    model->insertRow(lng, lat);
    ui->tableView->scrollToBottom();
}

//void MapExecution::updatePosition(double lat, double lng, double alt, double spd)
//{

//    if(prevTime.isNull())
//    {
//        prevTime = QTime::currentTime();
//        prevLat = lat;
//        prevLng = lng;
//        prevAlt = alt;
//    }
//    else
//    {
//        LatLabel->setText(QString::number(lat));
//        LngLabel->setText(QString::number(lng));
//        AltLabel->setText(QString::number(alt));
//        SpdLabel->setText(QString::number(spd));
//    }
//}
//void MapExecution::initCurrentData()
//{

//    LatLabel = new QTableWidgetItem("LatLabel");
//    LngLabel = new QTableWidgetItem("LngLabel");
//    AltLabel = new QTableWidgetItem("AltLabel");
//    SpdLabel = new QTableWidgetItem("SpdLabel");

//    CurrentData->setItem(0,0,new QTableWidgetItem("Latitude"));
//    CurrentData->setItem(1,0,new QTableWidgetItem("Longitude"));
//    CurrentData->setItem(2,0,new QTableWidgetItem("Altitude"));
//    CurrentData->setItem(3,0,new QTableWidgetItem("Speed"));

//    CurrentData->setItem(0,1,LatLabel);
//    CurrentData->setItem(1,1,LngLabel);
//    CurrentData->setItem(2,1,AltLabel);
//    CurrentData->setItem(3,1,SpdLabel);

//}

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

//void MapExecution::on_colorTester_clicked()
//{
//    ui->StatusConsole->appendPlainText("Update");
//    MapExecution::updateStatusIndicator(rand() % 3);
//}
