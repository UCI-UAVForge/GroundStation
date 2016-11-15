#include "mainmdidisplay.h"
#include "ui_mainmdidisplay.h"

MainMDIDisplay::MainMDIDisplay(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainMDIDisplay) {

    ui->setupUi(this);

    this->tempMapPlanningUIWidget = new MapPlanning();

    this->qttWidget = new QtTabTest();

    //Add the map in the background

    this->MapPlanningMapUIWidget = this->tempMapPlanningUIWidget->ui->webView;

    this->addWindow( this->MapPlanningMapUIWidget );

    //Maximize the map so it fills up the background

    //( ui->mdiArea->subWindowList().at( 0 ) )->showMaximized();

    this->addWindow( qttWidget );

    //Add the map planning table to the tab widget window

    qttWidget->setMapPlanningUIWidget( this->tempMapPlanningUIWidget );

    qttWidget->addNewTab( this->tempMapPlanningUIWidget->ui->tableView , QString( "Table (Mission Planning) " ) );

    //Add the three buttons from MapPlanning to the Mission Planning window

    connect ( this->tempMapPlanningUIWidget->ui->backButton , SIGNAL( clicked() ) , this , SLOT( destroy() ) ) ;

    connect ( this->tempMapPlanningUIWidget->ui->executeButton , SIGNAL( clicked() ) , this , SLOT ( beginMapExecution() ) );

    this->missionPlanningWindowUIWidget = new MissionPlanningWindow();

    this->missionPlanningWindowUIWidget->deleteExecuteButton();

    this->missionPlanningWindowUIWidget->addButton( this->tempMapPlanningUIWidget->ui->backButton );

    this->missionPlanningWindowUIWidget->addButton( this->tempMapPlanningUIWidget->ui->clearTableButton );

    this->missionPlanningWindowUIWidget->addButton( this->tempMapPlanningUIWidget->ui->executeButton );

    this->addWindow( this->missionPlanningWindowUIWidget );

}

MainMDIDisplay::~MainMDIDisplay() {

    delete qttWidget;

    //delete tempMapPlanningUIWidget;

    delete ui;

    exit( 0 );

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

    /* TODO Maybe replace all these motherfucking pointers and just pass things by reference.
            Will that work? Cuz dynamic memory allocation sucks - Roman */

    QVBoxLayout * MapExecutionStatusVBoxLayout = new QVBoxLayout();

    this->mapExecutionStatusUIWidget = new QWidget();

    this->tempMapExecutionUIWidget = new MapExecution( this->tempMapPlanningUIWidget->getTableAsFlightPath());

    this->qttWidget->setMapExecutionUIWidget( this->tempMapExecutionUIWidget );

    qDebug() << "URL BEFORE: " << this->MapPlanningMapUIWidget->url();

    this->MapPlanningMapUIWidget = this->tempMapExecutionUIWidget->ui->webView ;

    qDebug() << "URL AFTER: " << this->MapPlanningMapUIWidget->url();

    MapExecutionStatusVBoxLayout->addWidget( this->tempMapExecutionUIWidget->ui->StatusIndicator );

    MapExecutionStatusVBoxLayout->addWidget( this->tempMapExecutionUIWidget->ui->StatusConsole );

    MapExecutionStatusVBoxLayout->addWidget( this->tempMapExecutionUIWidget->ui->clock );

    this->mapExecutionStatusUIWidget->setLayout( MapExecutionStatusVBoxLayout );

    this->qttWidget->addNewTab( this->mapExecutionStatusUIWidget , QString( "Network Status (Execution)" ) );

    this->qttWidget->addNewTab( this->tempMapExecutionUIWidget->ui->tableView , QString( "Table (Execution)" ) );

}

void MainMDIDisplay::destroy() {

    /* PRIVATE SLOT */

    delete this;

}
