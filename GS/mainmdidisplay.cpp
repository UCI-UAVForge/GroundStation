#include "mainmdidisplay.h"
#include "ui_mainmdidisplay.h"
#include "mapwidget.h"
#include "tablewidget.h"

MainMDIDisplay::MainMDIDisplay(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainMDIDisplay) {

    ui->setupUi(this);

    ui->mdiArea->setBackground(QBrush( QPixmap( ":/res/images/UAVLogo.png" ) ) );

    startMissionPlanning();

    addWindow(&msw);
    addWindow(&gscp);

    connect(&gscp, &GSControlPanel::createMissionButton_clicked, this, &MainMDIDisplay::startMissionPlanning);

}

MainMDIDisplay::~MainMDIDisplay() {
    delete ui;
    exit(0);
}

void MainMDIDisplay::setupMapPaths(){
    switch (myState) {
        case PLANNING:
            map->sendCreateNewPath(0);
            map->sendSetActivePath(0);
            break;
        case EXECUTION:
            if(!map){
                map->sendCreateNewPath(0);
                map->addFlightPath(myLoadedFlightPath,0);
            } else {
                map->sendDisableEditing();
            }
            map->sendCreateNewPath(1);
            break;
        case RECAP:
            /// \todo fill out MapRecap map requirements
            break;
        default:
            break;
    }
}

void MainMDIDisplay::addWindow(QWidget* myNewWindowWidget) {
    /* TODO Default window style should go here by making all of the windows conform to the same
     * stylesheet - Roman Parise */
    /* Second argument - turns off the 'X' in the subwindows */
    ui->mdiArea->addSubWindow(myNewWindowWidget, Qt::CustomizeWindowHint|Qt::WindowMinMaxButtonsHint);
}

//TODO Right now this function doesn't work due to issues with Qt's private constructors for QMdiSubWindow. - Roman Parise
void MainMDIDisplay::addWindow(QWidget* myNewWindowWidget, QString windowTitle) {
    /* Second argument - turns off the 'X' in the subwindows */
    QMdiSubWindow tempSubWindow ;
    tempSubWindow.setWidget(myNewWindowWidget);
    tempSubWindow.setWindowTitle(windowTitle);
    this->addWindow(&tempSubWindow);
}

void MainMDIDisplay::changeState(MDIState newState){
    switch(myState){
        case NONE:
            break;
        case PLANNING:
            myLoadedFlightPath = table->getTableAsFlightPath();
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
        case NONE: break;
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

void MainMDIDisplay::startMissionPlanning(){
    map = new MapWidget();
    table = new TableWidget();
    this->connect(map, &MapWidget::pointAdded, table, &TableWidget::appendRow);
    this->connect(map, &MapWidget::JSInitialized, this, &MainMDIDisplay::setupMapPaths);
    this->addWindow(map);
    this->addWindow(table);
}

void MainMDIDisplay::endMissionPlanning(){

}

void MainMDIDisplay::startMissionExecution(){

}

void MainMDIDisplay::endMissionExecution(){

}

void MainMDIDisplay::startMissionRecap(){

}

void MainMDIDisplay::endMissionRecap(){

}


