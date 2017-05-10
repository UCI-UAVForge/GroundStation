#include "mainmdidisplay.h"
#include "ui_mainmdidisplay.h"
#include "mapwidget.h"
#include "tablewidget.h"
#include "net.h"

MainMDIDisplay::MainMDIDisplay(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainMDIDisplay) {

    ui->setupUi(this);

    this->connect(this, &MainMDIDisplay::destroyed, this, &MainMDIDisplay::onWindowClose);
    this->connect(ui->actionShow_Control_Panel, &QAction::triggered, this, &MainMDIDisplay::showControlPanel);
    //ui->mdiArea->setBackground(QBrush( QPixmap( ":/res/images/UAVLogo.png" ) ) );
  
    ui->mdiArea->setBackground(QBrush(QPixmap(":/res/UAV_FORGE_LOGO_2.png").scaledToWidth(1200)));

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
            if(map->isVisible()){
                map->disconnectWebSocket();
            }
            break;
        case EXECUTION:
            myServer->closeServer();
            map->disconnectWebSocket();
            map->disconnect();
            table->disconnect();
            graph->disconnect();
            break;
        case RECAP:
            map->disconnectWebSocket();
            map->disconnect();
            table->disconnect();
            graph->disconnect();
            break;
        default: break;
    }
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

            if(myFlightPath.length() > 0) {
                qDebug() << "Pushing path of size:" << myFlightPath.length();
                map->addFlightPath(&myFlightPath,0,"preloaded");
                myFlightPath.clear();
            } else {
                qDebug() << "Flight Path object is empty or null";
            }
            break;
        case EXECUTION:
            qDebug() << "EXECUTION";
            if(!map){
                /// \todo handling code for if map does not exist prior to starting execution
                map->sendCreateNewPath(0);
                map->addFlightPath(&myFlightPath,0, "execution");
            } else {
                qDebug() << "Sending disableEditing!";
                map->sendDisableEditing();
            }
            map->sendCreateNewPath(1);
            break;
        case RECAP:
            qDebug() << "RECAP";
            if(!map){
                /// \todo handling code for if map does not exist prior to starting execution
                map->sendCreateNewPath(0);
                map->addFlightPath(&myFlightPath,0, "execution");
            } else {
                qDebug() << "Sending disableEditing!";
                map->sendDisableEditing();
            }
            map->sendCreateNewPath(1);
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

    QMdiSubWindow *targetWindow = NULL;

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

        if(map->isVisible()){
            map->disconnectWebSocket();
            qtt->deleteTabWidget(map);
            qtt->deleteTabWidget(table);
            qtt->deleteTabWidget(graph);
            removeWindow(qtt);
        }
        //qtt->deleteLater();
    }
}

void MainMDIDisplay::startMissionPlanning(){
    qtt = new QtTabTest();
    map = new MapWidget();
    table = new TableWidget();
    table->setEditable(true);
    qtt->addNewTab(map,"Map");
    qtt->addNewTab(table,"Table");
    addWindow(qtt);
    //addWindow(map);
    //addWindow(table);
    this->connect(map, &MapWidget::pointAdded, table, &TableWidget::appendRow);
    this->connect(table, &TableWidget::flightPathSent, map, &MapWidget::addFlightPath);
    this->connect(map, &MapWidget::tableCleared, table, &TableWidget::clearTable);
    this->connect(map, &MapWidget::JSInitialized, this, &MainMDIDisplay::setupMapPaths);
}

void MainMDIDisplay::endMissionPlanning(){
    myFlightPath.clear();
    if(map->isVisible()){
        FlightPath* fp = table->getTableAsFlightPath();
        myFlightPath = *fp;
        delete fp;
        qDebug() << "FlightPath contains " << myFlightPath.length() << " waypoints";
        //myLoadedMission = new Mission(myFlightPath);
        myMission = Mission(myFlightPath);


        //qDebug() << "Mission contains " << myLoadedMission->getFlightPath()->length() << " waypoints";
        qDebug() << "Mission contains " << myMission.getFlightPath()->length() << " waypoints";
    }
}

void MainMDIDisplay::startMissionExecution(){
    /// \todo add handling for starting MissionExection from any other state
    table->setEditable(false);
    table->clearTable();
    //changeState(EXECUTION);

    setupMapPaths();
    /// \todo add server startup code here

    //myServer = new GsServer(myLoadedMission);
    myServer = new GsServer(&myMission);
    /// \todo change address and port to be located in the net.h file
    myServer->openServer(QHostAddress::LocalHost, 20715);
    connect(myServer, &GsServer::packetRecieved, this, &MainMDIDisplay::receivePacket);

    for(TimedAction *a: myFlightPath){
        a->first->SetAction(Protocol::ActionType::AddWaypoint);
        myServer->sendPacket(a->first);
    }
    myServer->startServer();

    graph = new GraphWidget();
    qtt->addNewTab(graph,"Graph");
    //this->addWindow(graph);

}

void MainMDIDisplay::endMissionExecution(){
    ///\todo
    /// -send stop command
    /// -shutdown server maybe???
    /// -stop editing maps, tables, and graphs


    Protocol::ActionPacket a1,a2;
    a1.SetAction(Protocol::ActionType::Stop);
    //a2.SetAction(Protocol::ActionType::Shutdown);
    myServer->sendPacket(&a1);
    //myServer->sendPacket(&a2);

    disconnect(myServer, &GsServer::packetRecieved, this, &MainMDIDisplay::receivePacket);
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
        map = new MapWidget();
        qtt->addNewTab(map, "Map View");
        table = new TableWidget();
        qtt->addNewTab(table, "Telemetry Log");
        graph = new GraphWidget();
        qtt->addNewTab(graph, "Graphs");
    }
    this->connect(map, &MapWidget::JSInitialized, this, &MainMDIDisplay::setupMapPaths);

    if(!qtt->isVisible()){
        addWindow(qtt);
        this->graph->drawMission(&myMission);
        this->table->insertMissionTelem(&myMission);
        this->map->drawMissionTelem(&myMission);
    }
    table->setEditable(false);
}

void MainMDIDisplay::endMissionRecap(){
    ///\todo
    /// delete dynamic objects
    //removeWindow(qtt);
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
        graph->appendTelemPacket(currentTelemetryPacket);
        this->gscp->setCurrentTelemetryPacket( currentTelemetryPacket );
    }
}

void MainMDIDisplay::plotPosition(double lat, double lng){
    table->appendRow(lat, lng);
    FlightPath *fp = table->getTableAsFlightPath();
    map->addFlightPath(fp, 0, "execution");
    delete fp;
}

void MainMDIDisplay::loadFlightPath() {
    if (this->gscp->getFlightpathNameToLoad() == "")
        return;

    qDebug() << "ENTERING LOAD FLIGHTPTH!";

    QString fullFileName = this->gscp->getFlightpathNameToLoad();

    this->changeState(MDIState::PLANNING);

    myFlightPath = FlightPath(fullFileName);
    qDebug() << "Mission Length: " << myFlightPath.length();
    QList<Protocol::Waypoint> *list = myFlightPath.getOrderedWaypoints();



    foreach (Protocol::Waypoint wp, *list) {
        this->table->appendRow(wp.lat, wp.lon);
    };
    delete list;
}

void MainMDIDisplay::saveFlightPath() {
    // This is for flightPath
    if (this->gscp->getFlightpathNameToSave() == "")
        return;

    qDebug() << "ENTERING SAVE FLIGHTPTH!";

    QString fullFileName = this->gscp->getFlightpathNameToSave();

    FlightPath *fp = table->getTableAsFlightPath();
    myFlightPath = *fp;
    myFlightPath.save(fullFileName);
    delete fp;

    //this->gscp->addMissionToLoad(fileName);
    //this->gscp->setSelectedMission(fileName);


    /* This is for mission, put it in different method after done with testing.
    QString fileName = "Try1";
    QString fullFileName = this->folder + this->kPathSeparator + fileName;

    this->myLoadedMission = new Mission(fullFileName);
    this->myLoadedMission->save(fullFileName);
    */
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
}
