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

    ///\todo Just put these in the UI file and promote QWidgets

    addWindow(&msw);
    addWindow(&gscp);

    connect( &(this->msw) , SIGNAL( updateStatusWidget() ) , this , SLOT( updateMissionStatus() ) ) ;

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
                map->addFlightPath(myLoadedFlightPath,0, "execution");
            } else {
                qDebug() << "Sending disableEditing!";
                map->sendDisableEditing();
            }
            map->sendCreateNewPath(1);
            //map->addFlightPath(myLoadedFlightPath,0, "execution");
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

    QMdiSubWindow * newWindow = NULL ;

    if ( myNewWindowWidget != NULL ) {
        /* Second argument - turns off the 'X' in the subwindows */
        newWindow = ui->mdiArea->addSubWindow( myNewWindowWidget , Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint );
        myNewWindowWidget->show();
        ///\todo Better error checking?
        if ( newWindow != NULL ) {
            newWindow->setMinimumSize( myNewWindowWidget->geometry().width() , myNewWindowWidget->geometry().height());
            newWindow->adjustSize() ;
        } else {
            qDebug() << "Subwindow could not be created to hold widget." ;
        }
    } else {
        qDebug() << "Cannot add window with NULL widget." ;
    }

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
        case RECAP:
            startMissionRecap();
            break;
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
    this->connect(table, &TableWidget::flightPathSent, map, &MapWidget::addFlightPath);
    this->connect(map, &MapWidget::tableCleared, table, &TableWidget::clearTable);
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
    table->clearTable();
    //changeState(EXECUTION);
    setupMapPaths();
    /// \todo add server startup code here

    myServer = new GsServer(myLoadedMission);
    /// \todo change address and port to be located in the net.h file
    myServer->openServer(QHostAddress::LocalHost, 20715);
    connect(myServer, &GsServer::packetRecieved, this, &MainMDIDisplay::receivePacket);

    for (TimedAction *a : *myLoadedFlightPath) {
        a->first->SetAction(Protocol::ActionType::AddWaypoint);
        myServer->sendPacket(a->first);
    }

    myServer->startServer();
    this->msw.initiateWidgets();
}

void MainMDIDisplay::endMissionExecution(){

    this->msw.stopWidgets() ;

    ///\todo

}

void MainMDIDisplay::startMissionRecap(){
    ///\todo
}

void MainMDIDisplay::endMissionRecap(){
    ///\todo
}

void MainMDIDisplay::receivePacket(Protocol::Packet* packet){

    Protocol::Packet* incPack = packet;
    Protocol::PacketType type = incPack->get_type();
    if (type == Protocol::PacketType::Telem){
        double lat, lng;
        float alt;
        Protocol::TelemetryPacket * currentTelemetryPacket = (Protocol::TelemetryPacket*)incPack;
        qDebug() << "TelemPacket Recieved" ;
        currentTelemetryPacket->GetLocation(&lat,&lng,&alt);
        plotPosition(lat,lng);
        this->msw.setCurrentTelemetryPacket( currentTelemetryPacket );
    }
}

void MainMDIDisplay::plotPosition(double lat, double lng){
    table->appendRow(lat, lng);
    FlightPath *fp = table->getTableAsFlightPath();
    map->addFlightPath(fp, 0, "execution");
    delete fp;
}
