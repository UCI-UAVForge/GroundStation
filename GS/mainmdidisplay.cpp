#include "mainmdidisplay.h"
#include "ui_mainmdidisplay.h"

MainMDIDisplay::MainMDIDisplay(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainMDIDisplay) {

    ui->setupUi(this);

    ui->mdiArea->setBackground( QBrush( QPixmap( ":/res/images/UAVLogo.png" ) ) );

    this->qttWidget = new QtTabTest();

    this->addWindow( qttWidget );

    this->tempMapPlanningUIWidget = new MapPlanning();

    this->missionPlanningWindowUIWidget = new MissionPlanningWindow();

    //Add the map planning table to the tab widget window

    qttWidget->setMapPlanningUIWidget( this->tempMapPlanningUIWidget );

    qttWidget->addNewTab( this->tempMapPlanningUIWidget->ui->tableView , QString( "Table (Mission Planning) " ) );

    //Add the three buttons from MapPlanning to the Mission Planning window

    connect ( this->tempMapPlanningUIWidget->ui->backButton , SIGNAL( clicked() ) , this , SLOT( destroy() ) ) ;

    connect ( this->tempMapPlanningUIWidget->ui->executeButton , SIGNAL( clicked() ) , this , SLOT ( beginMapExecution() ) );

    this->switchToPlanningWindow();

    this->addWindow( this->MapPlanningMapUIWidget );

    this->addWindow( this->missionPlanningWindowUIWidget );

}

MainMDIDisplay::~MainMDIDisplay() {

    delete qttWidget;

    delete tempMapPlanningUIWidget;

    delete ui;

    exit( 0 );

}

void MainMDIDisplay::switchToPlanningWindow() {

    // Delete default buttons

    this->missionPlanningWindowUIWidget->dumpButtons();

    //Add the map in the background

    this->MapPlanningMapUIWidget = this->tempMapPlanningUIWidget->ui->webView;

    //Add the buttons from MapPlanning to the Mission Planning window

    this->tempMapPlanningUIWidget->ui->backButton->show();

    this->tempMapPlanningUIWidget->ui->clearTableButton->show();

    this->tempMapPlanningUIWidget->ui->executeButton->show();

    this->missionPlanningWindowUIWidget->addButton( this->tempMapPlanningUIWidget->ui->backButton );

    this->missionPlanningWindowUIWidget->addButton( this->tempMapPlanningUIWidget->ui->clearTableButton );

    this->missionPlanningWindowUIWidget->addButton( this->tempMapPlanningUIWidget->ui->executeButton );

    this->missionPlanningWindowUIWidget->addButton( this->tempMapPlanningUIWidget->getLoadMissionButton() );

    this->missionPlanningWindowUIWidget->addButton( this->tempMapPlanningUIWidget->getSaveMissionButton() );

}

QtTabTest * MainMDIDisplay::getQttWidget() const {

    return qttWidget;

}

void MainMDIDisplay::setQttWidget( QtTabTest * value) {

    qttWidget = value;

}

void MainMDIDisplay::addWindow( QWidget * myNewWindowWidget ) {

    /* Second argument - turns off the 'X' in the subwindows */

    ui->mdiArea->addSubWindow( myNewWindowWidget , Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint );

}

void MainMDIDisplay::beginMapExecution() {

    //Make two new tabs in qttWidget. One is for the MapExecution table, and one

    //is for the current connection/network status.

    /* TODO Maybe replace all these pointers and just pass things by reference.
            Will that work? Cuz dynamic memory allocation sucks - Roman */

    this->MapExecutionStatusVBoxLayout = new QVBoxLayout();

    this->mapExecutionStatusUIWidget = new QWidget();

    this->tempMapExecutionUIWidget = new MapExecution( this->tempMapPlanningUIWidget->getTableAsFlightPath() );

    //this->qttWidget->setMapExecutionUIWidget( this->tempMapExecutionUIWidget );

    qDebug() << "URL BEFORE: " << this->MapPlanningMapUIWidget->url();

    this->MapPlanningMapUIWidget = this->tempMapExecutionUIWidget->ui->webView ;

    qDebug() << "URL AFTER: " << this->MapPlanningMapUIWidget->url();

    this->MapExecutionStatusVBoxLayout->addWidget( this->tempMapExecutionUIWidget->ui->StatusIndicator );

    this->MapExecutionStatusVBoxLayout->addWidget( this->tempMapExecutionUIWidget->ui->StatusConsole );

    this->MapExecutionStatusVBoxLayout->addWidget( this->tempMapExecutionUIWidget->ui->clock );

    this->mapExecutionStatusUIWidget->setLayout( MapExecutionStatusVBoxLayout );

    this->qttWidget->addNewTab( this->mapExecutionStatusUIWidget , QString( "Network Status (Execution)" ) );

    this->qttWidget->addNewTab( this->tempMapExecutionUIWidget->ui->tableView , QString( "Table (Execution)" ) );

    this->changePlanningToExecutionWindow();

}

//TODO Should this be something that happens in MissionPlanningWindow?
void MainMDIDisplay::changePlanningToExecutionWindow() {

    //TODO Add error checking for if MapExecution is not yet initialized

    this->missionPlanningWindowUIWidget->dumpButtons() ;

    this->missionPlanningWindowUIWidget->dumpComboBoxes() ;

    //TODO CLEAN UP THESE GODDAMN MEMORY LEAKS

    tempMapPlanningUIWidget->ui->executeButton->hide();

    tempMapPlanningUIWidget->ui->backButton->hide();

    tempMapPlanningUIWidget->ui->clearTableButton->hide();

    tempMapPlanningUIWidget->loadMissionButton->hide();

    tempMapPlanningUIWidget->saveMissionButton->hide();

    //delete tempMapPlanningUIWidget ;

    //tempMapPlanningUIWidget = NULL;

    //TODO Add addButtons function to take a list of buttons in the missionplanningwindow class

    this->missionPlanningWindowUIWidget->addButton( this->tempMapExecutionUIWidget->ui->backButton ) ;

    this->missionPlanningWindowUIWidget->addButton( this->tempMapExecutionUIWidget->ui->cancelButton );

    this->missionPlanningWindowUIWidget->addButton( this->tempMapExecutionUIWidget->ui->finishButton );

    this->missionPlanningWindowUIWidget->changeTitle( QString( "Mission Execution" ) ) ;

    //connect( this->tempMapExecutionUIWidget->ui->backButton, SIGNAL(clicked()), this, SLOT(clickedBackButton_MainDisplay()) );

    connect( this->tempMapExecutionUIWidget->ui->cancelButton, SIGNAL(clicked()), this, SLOT(clickedCancelButton_MainDisplay()) );

    connect( this->tempMapExecutionUIWidget->ui->finishButton, SIGNAL(clicked()), this, SLOT(clickedFinishButton_MainDisplay()) );

}

void MainMDIDisplay::destroy() {

    /* PRIVATE SLOT */

    delete this;

}

void MainMDIDisplay::switchToRecapWindow() {

    QWidget * MapRecapUI_TableTab , * MapRecapUI_GraphTab ;

    this->tempMapRecapUIWidget = this->tempMapExecutionUIWidget->getMapRecap();

    //TODO May not be necessary since the URL appears to be the same before and after

    qDebug() << "URL BEFORE: " << this->MapPlanningMapUIWidget->url() ;

    this->MapPlanningMapUIWidget = this->tempMapRecapUIWidget->ui->webView ;

    qDebug() << "URL AFTER: " << this->MapPlanningMapUIWidget->url() ;

    MapRecapUI_TableTab = this->tempMapRecapUIWidget->getTab( 1 );

    MapRecapUI_GraphTab = this->tempMapRecapUIWidget->getTab( 2 );

    this->qttWidget->addNewTab( MapRecapUI_TableTab , QString( "Table (Recap)" ) );

    this->qttWidget->addNewTab( MapRecapUI_GraphTab , QString( "Graph (Recap)" ) );

    this->missionPlanningWindowUIWidget->addButton( this->tempMapRecapUIWidget->ui->backButton );

}

void MainMDIDisplay::clickedFinishButton_MainDisplay() {

    this->switchToRecapWindow();

    this->clearMapExecution();

}

void MainMDIDisplay::clearMapExecution() {

    delete this->tempMapExecutionUIWidget->ui->cancelButton ;

    this->tempMapExecutionUIWidget->ui->cancelButton = NULL ;

    delete this->tempMapExecutionUIWidget->ui->finishButton ;

    this->tempMapExecutionUIWidget->ui->finishButton = NULL ;

    delete this->tempMapExecutionUIWidget->ui->backButton ;

    this->tempMapExecutionUIWidget->ui->backButton = NULL ;

    /*

    delete this->tempMapExecutionUIWidget->ui->clock ;

    this->tempMapExecutionUIWidget->ui->clock = NULL ;

    delete this->tempMapExecutionUIWidget->ui->StatusIndicator ;

    this->tempMapExecutionUIWidget->ui->StatusIndicator = NULL ;

    delete this->tempMapExecutionUIWidget->ui->StatusConsole ;

    this->tempMapExecutionUIWidget->ui->StatusConsole = NULL ;

    delete this->tempMapExecutionUIWidget->ui->clock ;

    this->tempMapExecutionUIWidget->ui->clock = NULL ;

    delete this->mapExecutionStatusUIWidget ;

    this->mapExecutionStatusUIWidget = NULL ;

    delete this->MapExecutionStatusVBoxLayout ;

    this->MapExecutionStatusVBoxLayout = NULL ;

    delete this->tempMapExecutionUIWidget ;

    this->tempMapExecutionUIWidget = NULL ;

    */

}

void MainMDIDisplay::clickedCancelButton_MainDisplay() {

    this->switchToPlanningWindow();

    this->clearMapExecution();

}
