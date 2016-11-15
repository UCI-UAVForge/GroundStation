#include "mainwindow.h"

/**
 * Constructor for the main window
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //Resize the image for the Mission Execution button
    QPixmap pixmap(":/res/longButtons/Mission_Execution_Button_Type_2.png");
    QIcon ButtonIcon(pixmap);
    ui->pushButton_8->setIcon(ButtonIcon);
    ui->pushButton_8->setIconSize(pixmap.rect().size()/13);

    //Resize the image for the Mission Planning button
    QPixmap pixmap2(":/res/longButtons/Mission_Planning_Button_Type_2.png");
    QIcon ButtonIcon2(pixmap2);
    ui->pushButton_9->setIcon(ButtonIcon2);
    ui->pushButton_9->setIconSize(pixmap2.rect().size()/13);

    //Resize the image for the Mission Recap button
    QPixmap pixmap3(":/res/longButtons/Mission_Recap_Button_Type_2.png");
    QIcon ButtonIcon3(pixmap3);
    ui->pushButton_7->setIcon(ButtonIcon3);
    ui->pushButton_7->setIconSize(pixmap3.rect().size()/13);

    //Resize the image for the Tutorial button
    QPixmap pixmap4(":/res/longButtons/Tutorial_Button_Type_2.png");
    QIcon ButtonIcon4(pixmap4);
    ui->pushButton_6->setIcon(ButtonIcon4);
    ui->pushButton_6->setIconSize(pixmap4.rect().size()/13);
}

/**
 * Destructor for the main window
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * When the tutorial button is clicked, create a new tutorial window,
 * close the main window, and open the tutorial window in full screen
 */
void MainWindow::openTutorial() {
    this->showTutorial();
}

/**
 * When the mission planning button is clicked, create a new mission planning window
 */
void MainWindow::missionPlanningClicked() {
    this->showMissionPlanning();
}

/**
 * When the mission execution button is clicked, create a new mission execution window
 */
void MainWindow::missionExecutionClicked() {
    this->showMissionExecution();
}

/**
 * When the mission recap buttion is clicked, create a new mission recap window
 */
void MainWindow::missionRecapClicked() {
    this->showMissionRecap();
}

/**
 * Close the main window when ALT + Q is clicked
 */
void MainWindow::on_actionQuit_triggered() {
    this->close();
}
void MainWindow::on_actionSave_triggered() {
    this->close();
}
void MainWindow::on_actionMap_Planning_triggered() {
    this->showMissionPlanning();
}
void MainWindow::on_actionMission_Execution_triggered(){
    this->showMissionExecution();
}
void MainWindow::on_actionMission_Recap_triggered(){
    this->showMissionRecap();
}
/**
 * The callback function to check for return status and redirect to corresponded new window
 * 0 == main window (default)
 * 1 == mission planning
 * 2 == mission execution
 * 3 == mission recap
 * 4 == tutorial
 * Advice for improvement: can use stack data structure to handle the callbacks
 */
void MainWindow::checkFinishStatus(int status) {
    if(status == 1) {
        this->showMissionPlanning();
    } else if(status == 2) {
        this->showMissionExecution();
    } else if(status == 3) {
        this->showMissionRecap();
    } else if(status == 4) {
        this->showTutorial();
    }
}

// helper functions

void MainWindow::showMissionPlanning() {
    MapPlanning *mapPlanning = new MapPlanning();
    QObject::connect(mapPlanning, SIGNAL(finished(int)), this, SLOT(checkFinishStatus(int)), Qt::UniqueConnection);
    mapPlanning->showFullScreen();
}

void MainWindow::showMissionExecution(){
    //Temporary FlightPath code - Remove Later

    std::cout << "Attempting to create FlightPath" << std::endl;
    FlightPath *myFlightPath = new FlightPath();


    std::cout << "Filling point 1" << std::endl;
    Protocol::Waypoint wp;
    wp.alt = 10;
    wp.lat = 33;
    wp.lon = -111;
    wp.speed = 10;
    myFlightPath->addNavAction(wp,10);

    std::cout << "Filling point 2" << std::endl;
    wp.alt = 10;
    wp.lat = 34;
    wp.lon = -111;
    wp.speed = 10;
    myFlightPath->addNavAction(wp,20);

    std::cout << "Filling point 3" << std::endl;
    wp.alt = 10;
    wp.lat = 34;
    wp.lon = -110;
    wp.speed = 10;
    myFlightPath->addNavAction(wp,30);

    std::cout << "Done creating FlightPath" << std::endl;

    //End temporary FlightPath code



    MapExecution *mapExecution = new MapExecution(myFlightPath);
    QObject::connect(mapExecution, SIGNAL(finished(int)), this, SLOT(checkFinishStatus(int)), Qt::UniqueConnection);
    mapExecution->showFullScreen();

    //Open ConnectionDialog when MissionExecution is opened

    //
    //ConnectionDialog * connectionDialog = new ConnectionDialog();
    //connectionDialog -> show();
}

void MainWindow::showMissionRecap() {
    //MissionRecap *missionRecap = new MissionRecap();
    MapRecap *missionRecap = new MapRecap();
    QObject::connect(missionRecap, SIGNAL(finished(int)), this, SLOT(checkFinishStatus(int)), Qt::UniqueConnection);
    missionRecap->showFullScreen();

}

void MainWindow::showTutorial() {
    Tutorial *tutorial = new Tutorial();
    QObject::connect(tutorial, SIGNAL(finished(int)), this, SLOT(checkFinishStatus(int)), Qt::UniqueConnection);
    tutorial->showFullScreen();
}
