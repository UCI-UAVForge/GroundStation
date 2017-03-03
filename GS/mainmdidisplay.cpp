#include "mainmdidisplay.h"
#include "ui_mainmdidisplay.h"
#include "mapwidget.h"
#include "tablewidget.h"
#include "graphwidget.h"
#include "net.h"

MainMDIDisplay::MainMDIDisplay(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainMDIDisplay) {

    ui->setupUi(this);

    ui->mdiArea->setBackground(QBrush( QPixmap( ":/res/images/UAVLogo.png" ) ) );

    //startMissionPlanning();

    addWindow(&msw);
    addWindow(&gscp);

    graph = new GraphWidget();
    this->addWindow(graph);

    connect(&gscp, &GSControlPanel::createMissionButton_clicked, this, &MainMDIDisplay::startMissionPlanningSlot);
    connect(&gscp, &GSControlPanel::startMissionButton_clicked, this, &MainMDIDisplay::startMissionExecutionSlot);
    connect(&gscp, &GSControlPanel::finishMissionButton_clicked, this, &MainMDIDisplay::startMissionRecapSlot);
    connect(&gscp, &GSControlPanel::exitButton_clicked, this, &MainMDIDisplay::close);
}

MainMDIDisplay::~MainMDIDisplay() {
    delete ui;
    exit(0);
}

void MainMDIDisplay::setupMapPaths(){
    if(!map){
        //do nothing if the map does not exist
        /// \todo add an error message and handling
        qDebug() << "Called setupMapPaths with map == NULL!";
        return;
    }
    qDebug() << "Sending map settings for state: ";
    switch (myState) {
        case PLANNING:
            qDebug() << "PLANNING";
            map->sendCreateNewPath(0);
            map->sendSetActivePath(0);
            break;
        case EXECUTION:
            qDebug() << "EXECUTION";
            if(!map){
                /// \todo handling code for if map does not exist prior to starting execution
                map->sendCreateNewPath(0);
                map->addFlightPath(myLoadedFlightPath,0);
            } else {
                qDebug() << "Sending disableEditing!";
                map->sendDisableEditing();
            }
            map->sendCreateNewPath(1);
            break;
        case RECAP:
            qDebug() << "RECAP";
            /// \todo fill out MapRecap map requirements
            break;
        default:
            qDebug() << "NONE - this is clearly a bug!";
            break;
    }
}

void MainMDIDisplay::addWindow(QWidget* myNewWindowWidget) {
    /* TODO Default window style should go here by making all of the windows conform to the same
     * stylesheet - Roman Parise */
    /* Second argument - turns off the 'X' in the subwindows */
    ui->mdiArea->addSubWindow(myNewWindowWidget, Qt::CustomizeWindowHint|Qt::WindowMinMaxButtonsHint);
    myNewWindowWidget->show();
}

//TODO Right now this function doesn't work due to issues with Qt's private constructors for QMdiSubWindow. - Roman Parise
void MainMDIDisplay::addWindow(QWidget* myNewWindowWidget, QString windowTitle) {
    /* Second argument - turns off the 'X' in the subwindows */
    QMdiSubWindow tempSubWindow;
    tempSubWindow.setWidget(myNewWindowWidget);
    tempSubWindow.setWindowTitle(windowTitle);
    addWindow(&tempSubWindow);
}

void MainMDIDisplay::changeState(MDIState newState){
    switch(myState){
        case NONE:
            break;
        case PLANNING:
            endMissionPlanning();
            break;
        case EXECUTION:
            /// \todo get mission output in a Mission object from the messagebox
            // myLoadedMission = myMessagebox.toMission();
            endMissionExecution();
            break;
        case RECAP:
            endMissionRecap();
            break;
        default: break;
    }
    myState = newState;

    switch(newState){
        case NONE:
            break;
        case PLANNING:
            startMissionPlanning();
            break;
        case EXECUTION:
            startMissionExecution();
            break;
        case RECAP: startMissionRecap(); break;
        default: break;
    }
}

void MainMDIDisplay::startMissionPlanningSlot() {
    changeState(MDIState::PLANNING);
}

void MainMDIDisplay::startMissionExecutionSlot() {
    changeState(MDIState::EXECUTION);
}

void MainMDIDisplay::startMissionRecapSlot() {
    changeState(MDIState::RECAP);
}

void MainMDIDisplay::startMissionPlanning(){
    map = new MapWidget();
    table = new TableWidget();
    addWindow(map);
    addWindow(table);
    this->connect(map, &MapWidget::pointAdded, table, &TableWidget::appendRow);
    this->connect(map, &MapWidget::JSInitialized, this, &MainMDIDisplay::setupMapPaths);
}

void MainMDIDisplay::endMissionPlanning(){
    if(myLoadedFlightPath){
        delete myLoadedFlightPath;
        myLoadedFlightPath = NULL;
    }
    myLoadedFlightPath = table->getTableAsFlightPath();
    qDebug() << "FlightPath contains " << myLoadedFlightPath->length() << " waypoints";
    myLoadedMission = new Mission(*myLoadedFlightPath);
    qDebug() << "Mission contains " << myLoadedMission->getFlightPath()->length() << " waypoints";
}

void MainMDIDisplay::startMissionExecution(){
    /// \todo add handling for starting MissionExection from any other state

    /// \todo add a clearTable() method to reuse this object
    delete table;
    table = new TableWidget();
    addWindow(table);

    setupMapPaths();
    /// \todo add server startup code here

    myMessageBox = new messagebox();
    myServer = new GsServer(myMessageBox, myLoadedMission);

    /// \todo change address and port to be located in the net.h file
    myServer->openServer(QHostAddress::LocalHost, 20715);
    connect(myServer, &GsServer::packetRecieved, this, &MainMDIDisplay::receivePacket);

    for (TimedAction *a : *myLoadedFlightPath){
        myMessageBox->addActionPacket(*(a->first));
    }

    std::vector<Protocol::ActionPacket> packets = myMessageBox->get_action_packets();

    for (Protocol::ActionPacket pack : packets){
        pack.SetAction(Protocol::ActionType::AddWaypoint);
        myServer->sendPacket(&pack);
    }

    myServer->startServer();
}

void MainMDIDisplay::endMissionExecution(){

}

void MainMDIDisplay::startMissionRecap(){

}

void MainMDIDisplay::endMissionRecap(){

}

void MainMDIDisplay::receivePacket(Protocol::Packet* packet){
    Protocol::Packet* incPack = packet;
    Protocol::PacketType type = incPack->get_type();
    if (type == Protocol::PacketType::Ack){
        std::cout<< "AckPacket Recieved" << std::endl;
        Protocol::AckPacket *ackPacket = (Protocol::AckPacket*)incPack;
        //myMessageBox->addAckPacket(*ackPacket);
    } else if (type == Protocol::PacketType::Telem){
        std::cout<< "TelemPacket Recieved" << std::endl;
        Protocol::TelemetryPacket *telemPacket = (Protocol::TelemetryPacket*)incPack;
        myMessageBox->addTelemetryPacket(*telemPacket);
        double lat, lng;
        float alt;
        telemPacket->GetLocation(&lat,&lng,&alt);
        plotPosition(lat,lng);
    } else if (type == Protocol::PacketType::Info){
        std::cout<< "InfoPacket Recieved" << std::endl;
        Protocol::InfoPacket *infoPacket = (Protocol::InfoPacket*)incPack;
        //myMessageBox->addInfoPacket(*infoPacket);
    } else {
        std::cout<< "UNEXPECTED PACKET TYPE RECIEVED!" << std::endl;
    }

}

void MainMDIDisplay::plotPosition(double lat, double lng){
    table->appendRow(lat,lng);
    map->appendPointToPath(lat,lng,1);
}
