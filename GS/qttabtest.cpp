#include "qttabtest.h"
#include "ui_qttabtest.h"

//TODO Somebody please fix all the memory leaks in this project. We want a clean program close.
//This doesn't seem to work lol

/**
 * Constructor for the main window
 */
QtTabTest::QtTabTest(QWidget *parent) : QMainWindow( parent ) , ui( new Ui::QtTabTest ) , isFirstTabEmpty( true ) {

    //this->MapPlanningUIWidget = new MapPlanning();

    ui->setupUi( this );

    //this->ui->mdiArea->addSubWindow( this->MapPlanningUIWidget );

    //this->MapPlanningUIWidget->showMaximized();

}

/**
 * Destructor for the main window
 */
QtTabTest::~QtTabTest() {

    delete ui;

}

/**
 * @brief Ready to begin map execution. Replace the MapPlanning widget with a new MapExecution widget.
 */
//Old function. No longer used.
void QtTabTest::startMapExecution() {

    /* PRIVATE SLOT */

    this->MapExecutionUIWidget = new MapExecution( this->MapPlanningUIWidget->getTableAsFlightPath() );

    this->addNewTab( this->MapExecutionUIWidget , QString( "Mission Execution" ) );

    connect( this->MapExecutionUIWidget , SIGNAL( timeToStartMapRecap() ) , this , SLOT ( startMapRecap() ) );

}

//Old function. No longer used.
void QtTabTest::startMapRecap() {

    //Instantiate MapRecapUIWidget

    this->MapRecapUIWidget = this->MapExecutionUIWidget->getMapRecap();

    MapRecapUI_MapTab = this->MapRecapUIWidget->getTab( 0 );

    MapRecapUI_TableTab = this->MapRecapUIWidget->getTab( 1 );

    MapRecapUI_GraphTab = this->MapRecapUIWidget->getTab( 2 );

    this->addNewTab( this->MapRecapUI_MapTab , QString( "Map (Recap)" ) );

    this->addNewTab( this->MapRecapUI_TableTab , QString( "Table (Recap)" ) );

    this->addNewTab( this->MapRecapUI_GraphTab , QString( "Graph (Recap)" ) );

}

MapExecution * QtTabTest::getMapExecutionUIWidget() const {

    return MapExecutionUIWidget;

}

//Old function. No longer used. - Roman Parise
void QtTabTest::setMapExecutionUIWidget(MapExecution *value) {

    MapExecutionUIWidget = value;

}


MapPlanning * QtTabTest::getMapPlanningUIWidget() const {

    return MapPlanningUIWidget;

}

void QtTabTest::setMapPlanningUIWidget( MapPlanning * MapPlanningUIWidget ) {

    if ( this->MapPlanningUIWidget == NULL ) {

        this->MapPlanningUIWidget = MapPlanningUIWidget;

        //this->addNewTab( this->MapPlanningUIWidget , QString( "Mission Planning" ) );

        //When the MapPlanning widget says to start map execution, call the startMapExecution slot.

        //connect( this->MapPlanningUIWidget , SIGNAL( timeToStartMapExecution() ) , this , SLOT( startMapExecution() ) );

    }

    else {

        qDebug() << "You already have a MapPlanningUIWidget in QtTabTest!";

    }

}

/* Roman Parise - Temporary function for adding a new tab to the window. Eventually,
 *
 * have a special QWidget with this function */

void QtTabTest::addNewTab( QWidget * myNewTabWidget , QString label ) {

    //The tab itself

    QGridLayout * newTab = new QGridLayout();

    QMdiArea * newMdiArea = new QMdiArea();

    newMdiArea->addSubWindow( myNewTabWidget );

    myNewTabWidget->showMaximized();

    newTab->addWidget( newMdiArea );

    this->ui->tabWidget->addTab( myNewTabWidget , label );

    if ( isFirstTabEmpty == true ) {

        /* If we're still stuck with the default empty first tab in tabWidget, delete it. */

        this->ui->tabWidget->removeTab( 0 );

        isFirstTabEmpty = false;

    }

    else {

        /* Do nothing */

    }

}

void QtTabTest::deleteTabIndex( int index ) {

    this->ui->tabWidget->removeTab( index );

}

///**
// * When the mission planning button is clicked, create a new mission planning window
// */
//void MainWindow::missionPlanningClicked() {
//    this->showMissionPlanning();
//}

///**
// * When the mission execution button is clicked, create a new mission execution window
// */
//void MainWindow::missionExecutionClicked() {
//    this->showMissionExecution();
//}

///**
// * When the mission recap buttion is clicked, create a new mission recap window
// */
//void MainWindow::missionRecapClicked() {
//    this->showMissionRecap();
//}

///**
// * Close the main window when ALT + Q is clicked
// */
//void MainWindow::on_actionQuit_triggered() {
//    this->close();
//}
//void MainWindow::on_actionSave_triggered() {
//    this->close();
//}
//void MainWindow::on_actionMap_Planning_triggered() {
//    this->showMissionPlanning();
//}
//void MainWindow::on_actionMission_Execution_triggered(){
//    this->showMissionExecution();
//}
//void MainWindow::on_actionMission_Recap_triggered(){
//    this->showMissionRecap();
//}
///**
// * The callback function to check for return status and redirect to corresponded new window
// * 0 == main window (default)
// * 1 == mission planning
// * 2 == mission execution
// * 3 == mission recap
// * 4 == tutorial
// * Advice for improvement: can use stack data structure to handle the callbacks
// */
//void MainWindow::checkFinishStatus(int status) {
//    if(status == 1) {
//        this->showMissionPlanning();
//    } else if(status == 2) {
//        this->showMissionExecution();
//    } else if(status == 3) {
//        this->showMissionRecap();
//    } else if(status == 4) {
//        this->showTutorial();
//    }
//}

//// helper functions

//void MainWindow::showMissionPlanning() {
//    MapPlanning *mapPlanning = new MapPlanning();
//    QObject::connect(mapPlanning, SIGNAL(finished(int)), this, SLOT(checkFinishStatus(int)), Qt::UniqueConnection);
//    mapPlanning->showFullScreen();
//}

//void MainWindow::showMissionExecution(){
//    //Temporary FlightPath code - Remove Later

//    std::cout << "Attempting to create FlightPath" << std::endl;
//    FlightPath *myFlightPath = new FlightPath();


//    std::cout << "Filling point 1" << std::endl;
//    Protocol::Waypoint wp;
//    wp.alt = 10;
//    wp.lat = 33;
//    wp.lon = -111;
//    wp.speed = 10;
//    myFlightPath->addNavAction(wp,10);

//    std::cout << "Filling point 2" << std::endl;
//    wp.alt = 10;
//    wp.lat = 34;
//    wp.lon = -111;
//    wp.speed = 10;
//    myFlightPath->addNavAction(wp,20);

//    std::cout << "Filling point 3" << std::endl;
//    wp.alt = 10;
//    wp.lat = 34;
//    wp.lon = -110;
//    wp.speed = 10;
//    myFlightPath->addNavAction(wp,30);

//    std::cout << "Done creating FlightPath" << std::endl;

//    //End temporary FlightPath code



//    MapExecution *mapExecution = new MapExecution(myFlightPath);
//    QObject::connect(mapExecution, SIGNAL(finished(int)), this, SLOT(checkFinishStatus(int)), Qt::UniqueConnection);
//    mapExecution->showFullScreen();

//    //Open ConnectionDialog when MissionExecution is opened

//    //
//    //ConnectionDialog * connectionDialog = new ConnectionDialog();
//    //connectionDialog -> show();
//}

//void MainWindow::showMissionRecap() {


//    //MissionRecap *missionRecap = new MissionRecap();
//    MapRecap *missionRecap = new MapRecap();
//    QObject::connect(missionRecap, SIGNAL(finished(int)), this, SLOT(checkFinishStatus(int)), Qt::UniqueConnection);
//    missionRecap->showFullScreen();

//}

//void MainWindow::showTutorial() {
//    Tutorial *tutorial = new Tutorial();
//    QObject::connect(tutorial, SIGNAL(finished(int)), this, SLOT(checkFinishStatus(int)), Qt::UniqueConnection);
//    tutorial->showFullScreen();
//}
