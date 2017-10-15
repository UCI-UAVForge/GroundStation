#include "mainmdidisplay.h"
#include "ui_mainmdidisplay.h"
#include "mapwidget.h"
#include "tablewidget.h"
#include "net.h"

MainMDIDisplay::MainMDIDisplay(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainMDIDisplay),
    myMap(NULL),
    telemTable(NULL),
    waypointTable(NULL),
    myGraph(NULL){

    ui->setupUi(this);

    this->connect(this, &MainMDIDisplay::destroyed, this, &MainMDIDisplay::onWindowClose);
    this->connect(ui->actionShow_Control_Panel, &QAction::triggered, this, &MainMDIDisplay::showControlPanel);
//    ui->mdiArea->setBackground(QBrush( QPixmap( ":/res/images/UAVLogo.png" )) );
//    ui->mdiArea->setBackground(QBrush(QPixmap(":/res/UAV_FORGE_LOGO_2.png").scaled(1920,1080,Qt::IgnoreAspectRatio)));
    ui->mdiArea->setBackground(QBrush(QPixmap(":/res/images/test.png").scaled(1920,1080,Qt::IgnoreAspectRatio)));

    ///\todo Just put these in the UI file and promote QWidgets
    showControlPanel();
}

MainMDIDisplay::~MainMDIDisplay() {
    delete ui;
    //exit(0);
}

void MainMDIDisplay::showControlPanel(){
    bool windowShowing = false;
    for(QMdiSubWindow *w : ui->mdiArea->subWindowList()){
        if(w->widget() == gscp){
            windowShowing = true;
            return;
        }
    }
    if(!windowShowing){
        this->removeWindow(gscp);
        gscp = new GSControlPanel();
        connect(gscp, &GSControlPanel::createMissionButton_clicked, this, &MainMDIDisplay::startMissionPlanningSlot);
        connect(gscp, &GSControlPanel::startMissionButton_clicked, this, &MainMDIDisplay::startMissionExecutionSlot);
        connect(gscp, &GSControlPanel::finishMissionButton_clicked, this, &MainMDIDisplay::startMissionRecapSlot);
        connect(gscp, &GSControlPanel::exitButton_clicked, this, &MainMDIDisplay::close);
        connect(gscp, &GSControlPanel::loadFlightpathButton_clicked, this, &MainMDIDisplay::loadFlightPath);
        connect(gscp, &GSControlPanel::saveFlightpathButton_clicked, this, &MainMDIDisplay::saveFlightPath);


        connect(gscp, &GSControlPanel::loadMissionButton_clicked, this, &MainMDIDisplay::loadMission);
        connect(gscp, &GSControlPanel::saveMissionButton_clicked, this, &MainMDIDisplay::saveMission);
        connect(gscp, &GSControlPanel::missionRecapButton_clicked, this, &MainMDIDisplay::startMissionRecapSlot);

        connect(gscp, &GSControlPanel::mainMenuButton_clicked, this, &MainMDIDisplay::rtnToMainMenu);
        addWindow(gscp);
    }
}

void MainMDIDisplay::onWindowClose(){
    switch(myState){
        case PLANNING:
            //myMap.disconnectWebSocket();
            break;
        case EXECUTION:
            myServer->closeServer();
            myMap.disconnectWebSocket();
            myMap.disconnect();
            telemTable.disconnect();
            waypointTable.disconnect();
            myGraph.disconnect();
            break;
        case RECAP:
            myMap.disconnectWebSocket();
            myMap.disconnect();
            telemTable.disconnect();
            waypointTable.disconnect();
            myGraph.disconnect();
            break;
        default: break;
    }
}

void MainMDIDisplay::setupMapPaths(){
    qDebug() << "Sending map settings for state: ";
    switch (myState) {
        case PLANNING:
            qDebug() << "PLANNING";
            myMap.sendCreateNewPath(0);
            myMap.sendSetActivePath(0);

            if(myFlightPath.length() > 0) {
                qDebug() << "Pushing path of size:" << myFlightPath.length();
                myMap.addFlightPath(&myFlightPath,0,"preloaded");
                myFlightPath.clear();
            } else {
                qDebug() << "Flight Path object is empty or null";
            }
            break;
        case EXECUTION:
            qDebug() << "EXECUTION";
            qDebug() << "Sending disableEditing!";
            myMap.sendDisableEditing();
            myMap.sendCreateNewPath(1);
            break;
        case RECAP:
            qDebug() << "RECAP";
            qDebug() << "Sending disableEditing!";
            myMap.sendDisableEditing();
            myMap.sendCreateNewPath(1);
            break;
        default:
            qDebug() << "NONE - this is clearly a bug cause by an illegal value for myState!";
            break;
    }
}

void MainMDIDisplay::addWindow(QWidget* myNewWindowWidget) {
    /* TODO Default window style should go here by making all of the windows conform to the same
     * stylesheet - Roman Parise */

    QMdiSubWindow * newWindow = NULL ;

    if ( myNewWindowWidget != NULL ) {
        /* Second argument - turns off the 'X' in the subwindows */
        newWindow = ui->mdiArea->addSubWindow(myNewWindowWidget, Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint );
        myNewWindowWidget->show();
        ///\todo Better error checking?
        if ( newWindow != NULL ) {
            newWindow->setMinimumSize( myNewWindowWidget->width() , myNewWindowWidget->height() );
            newWindow->adjustSize();
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


void MainMDIDisplay::removeWindow(QWidget *targetWidget){
    QList<QMdiSubWindow*> windowList = ui->mdiArea->subWindowList();

    //QMdiSubWindow *targetWindow = NULL;

    for(QMdiSubWindow *w : windowList){
        if(w->widget() == targetWidget){
            w->setVisible(false);
            break;
        }
    }
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

void MainMDIDisplay::rtnToMainMenu(){
    if(myState != NONE){
        changeState(MDIState::NONE);
        myFlightPath.clear();

        //if(map->isVisible()){
            //map->disconnectWebSocket();
            myMap.disconnectWebSocket();
            //qtt->deleteTabWidget(map);
            qtt->deleteTabWidget(&myMap);
            //qtt->deleteTabWidget(table);
            qtt->deleteTabWidget(&telemTable);
            qtt->deleteTabWidget(&waypointTable);
            //qtt->deleteTabWidget(graph);
            qtt->deleteTabWidget(&myGraph);
            removeWindow(qtt);
        //}
        //qtt->deleteLater();
    }
}

void MainMDIDisplay::startMissionPlanning(){
    qtt = new QtTabTest();
    //map = new MapWidget();
    ///\todo somehow clear the map
    telemTable.clearTable();
    waypointTable.clearTable();

    waypointTable.setEditable(true);
    telemTable.setEditable(false);

    qtt->addNewTab(&myMap,"Map");

    qtt->addNewTab(&waypointTable,"Waypoint Table");
    addWindow(qtt);

    connect(&myMap, &MapWidget::pointAdded, &waypointTable, &TableWidget::appendRow);
    connect(&waypointTable, &TableWidget::flightPathSent, &myMap, &MapWidget::addFlightPath);
    connect(&myMap, &MapWidget::tableCleared, &waypointTable, &TableWidget::clearTable);

    connect(&myMap, &MapWidget::JSInitialized, this, &MainMDIDisplay::setupMapPaths);
}

void MainMDIDisplay::endMissionPlanning(){
    myFlightPath.clear();
    //if(map->isVisible()){
        FlightPath* fp = waypointTable.getTableAsFlightPath();
        myFlightPath = FlightPath(*fp);
        delete fp;
        qDebug() << "FlightPath contains " << myFlightPath.length() << " waypoints";
        myMission = Mission(myFlightPath);


        qDebug() << "Mission contains " << myMission.getFlightPath()->length() << " waypoints";
    //}
}

void MainMDIDisplay::startMissionExecution(){
    /// \todo add handling for starting MissionExection from any other state
    //table->setEditable(false);
    //table->clearTable();

    waypointTable.setEditable(false);
    telemTable.setEditable(false);

    qtt->addNewTab(&telemTable,"Telemetry Table");

    //changeState(EXECUTION);

    setupMapPaths();
    /// \todo add server startup code here
    myServer = new GsServer(&myMission);
    /// \todo change address and port to be located in the net.h file
    myServer->openServer(QHostAddress::LocalHost, 20715);
    //connect(myServer, &GsServer::packetRecieved, this, &MainMDIDisplay::receivePacket);

    connect(myServer, &GsServer::telemDataRecieved, this, &MainMDIDisplay::receiveTelemetryData);
    myServer->sendFlightPath(&myFlightPath);
    myServer->startServer();

    /// \todo clear the
    //graph = new GraphWidget();
    qtt->addNewTab(&myGraph, "Graph");
    //qtt->addNewTab(graph,"Graph");
    //this->addWindow(graph);

}

void MainMDIDisplay::endMissionExecution(){
    ///\todo
    /// -send stop command
    /// -shutdown server maybe???
    /// -stop editing maps, tables, and graphs

    myServer->sendStopSequence();
    disconnect(myServer, &GsServer::telemDataRecieved, this, &MainMDIDisplay::receiveTelemetryData);
}

void MainMDIDisplay::startMissionRecap(){
    ///\todo
    /// -configure/create maps, tables, and graphs

    //if(!myLoadedMission){
    //    qDebug() << "Attempted to start MissionRecap without loading a Mission first!";
    //    return;
    //}

    if(!qtt){
        qtt = new QtTabTest();
        qtt->setVisible(false);
        //map = new MapWidget();
        //qtt->addNewTab(map, "Map View");
        qtt->addNewTab(&myMap, "Map View");
        //table = new TableWidget();
        //qtt->addNewTab(table, "Telemetry Log");
        telemTable.clearTable();
        waypointTable.clearTable();
        qtt->addNewTab(&telemTable, "Telemetry Log");
        qtt->addNewTab(&waypointTable, "Waypoint Log");
        //graph = new GraphWidget();
        //qtt->addNewTab(graph, "Graph");
        qtt->addNewTab(&myGraph, "Graph");
    }
    //this->connect(map, &MapWidget::JSInitialized, this, &MainMDIDisplay::setupMapPaths);

    if(!qtt->isVisible()){
        addWindow(qtt);
        //this->graph->drawMission(&myMission);
        myGraph.drawMission(&myMission);
        //this->table->insertMissionTelem(&myMission);
        telemTable.insertMissionTelem(&myMission);
        //this->map->drawMissionTelem(&myMission);
        myMap.drawMissionTelem(&myMission);
    }
    //table->setEditable(false);
    telemTable.setEditable(false);
    waypointTable.setEditable(false);
}

void MainMDIDisplay::endMissionRecap(){
    ///\todo
    /// delete dynamic objects
    //removeWindow(qtt);
}

void MainMDIDisplay::receiveTelemetryData(TelemetryData data) {
    plotPosition(data.lat, data.lng);
    myGraph.appendTelemData(&data);
    gscp->setCurrentTelemetryData(&data);
}

void MainMDIDisplay::plotPosition(double lat, double lng){
    telemTable.appendRow(lat,lng);
    FlightPath *fp = telemTable.getTableAsFlightPath();
    myMap.addFlightPath(fp, 0, "execution");
    delete fp;
}

void MainMDIDisplay::loadFlightPath() {
    if (this->gscp->getFlightpathNameToLoad() == "")
        return;

    waypointTable.clearTable();
    qDebug() << "ENTERING LOAD FLIGHTPTH!";

    QString fullFileName = this->gscp->getFlightpathNameToLoad();

    this->changeState(MDIState::PLANNING);

    myFlightPath = FlightPath(fullFileName);
    qDebug() << "Mission Length: " << myFlightPath.length();
    waypointTable.insertFlightPath(&myFlightPath);
}

void MainMDIDisplay::saveFlightPath() {
    // This is for flightPath
    if (this->gscp->getFlightpathNameToSave() == "")
        return;

    qDebug() << "ENTERING SAVE FLIGHTPTH!";

    QString fullFileName = this->gscp->getFlightpathNameToSave();

    FlightPath *fp = waypointTable.getTableAsFlightPath();
    myFlightPath = *fp;
    myFlightPath.save(fullFileName);
    delete fp;
}

void MainMDIDisplay::saveMission(){
    if (this->gscp->getMissionNameToSave() == "")
        return;
    qDebug() << "ENTERING SAVE MISSION!";
    QString fullFileName = this->gscp->getMissionNameToSave();
    myMission.save(fullFileName);
}

void MainMDIDisplay::loadMission(){
    if (this->gscp->getMissionNameToLoad() == "") return;
    qDebug() << "ENTERING LOAD MISSION!";
    QString fullFileName = this->gscp->getMissionNameToLoad();
    //this->changeState(MDIState::RECAP);
    myMission = Mission(fullFileName);
    myFlightPath = *(myMission.getFlightPath());
    qDebug() << "Mission Length: " << myMission.numOfEntries();
    //this->graph->drawMission(&myMission);

    telemTable.insertMissionTelem(&myMission);
}
