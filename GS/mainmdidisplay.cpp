#include "mainmdidisplay.h"
#include "ui_mainmdidisplay.h"

MainMDIDisplay::MainMDIDisplay(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainMDIDisplay),

    MapExecutionStatusVBoxLayout(NULL) , mapExecutionStatusUIWidget(NULL) {

    ui->setupUi(this);

    ui->mdiArea->setBackground( QBrush( QPixmap( ":/res/images/UAVLogo.png" ) ) );

    this->qttWidget = new QtTabTest();

    this->addWindow( qttWidget /* , QString( "Data" ) */ );

    this->tempMapPlanningUIWidget = new MapPlanning();

    this->missionPlanningWindowUIWidget = new MissionPlanningWindow();

    //Add the map planning table to the tab widget window

    qttWidget->setMapPlanningUIWidget( this->tempMapPlanningUIWidget );

    qttWidget->addNewTab( this->tempMapPlanningUIWidget->ui->tableView , QString( "Table (Mission Planning)" ) );

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

    this->missionPlanningWindowUIWidget->changeTitle( QString( "Mission Planning" ) );

    // Delete default buttons

    this->missionPlanningWindowUIWidget->dumpButtons();

    //Add the map in the background

    this->MapPlanningMapUIWidget = this->tempMapPlanningUIWidget->ui->webView;

    //Add the buttons from MapPlanning to the Mission Planning window

    this->tempMapPlanningUIWidget->ui->backButton->show();

    this->tempMapPlanningUIWidget->ui->clearTableButton->show();

    this->tempMapPlanningUIWidget->ui->executeButton->show();

    this->missionPlanningWindowUIWidget->uavComboBox->show();

    this->missionPlanningWindowUIWidget->missionPlanComboBox->show();

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

    /* TODO Default window style should go here by making all of the windows conform to the same
     * stylesheet - Roman Parise */

    /* Second argument - turns off the 'X' in the subwindows */

    ui->mdiArea->addSubWindow( myNewWindowWidget , Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint );

}

//TODO Right now this function doesn't work due to issues with Qt's private constructors for QMdiSubWindow. - Roman Parise
void MainMDIDisplay::addWindow( QWidget * myNewWindowWidget , QString windowTitle ) {

    /* Second argument - turns off the 'X' in the subwindows */

    QMdiSubWindow tempSubWindow ;

    tempSubWindow.setWidget( myNewWindowWidget );

    tempSubWindow.setWindowTitle( windowTitle );

    this->addWindow( &tempSubWindow );

}

void MainMDIDisplay::beginMapExecution() {

    //Make two new tabs in qttWidget. One is for the MapExecution table, and one

    //is for the current connection/network status.

    /* TODO Maybe replace all these pointers and just pass things by reference.
            Will that work? Cuz dynamic memory allocation sucks - Roman */

    if ( this->MapExecutionStatusVBoxLayout == NULL ) {

        this->MapExecutionStatusVBoxLayout = new QVBoxLayout();

    }

    else {

        /* Do nothing. */

    }

    if ( this->mapExecutionStatusUIWidget == NULL ) {

        this->mapExecutionStatusUIWidget = new QWidget();

    }

    else {

        /* Do nothing. */

    }

    FlightPath* fp = this->tempMapPlanningUIWidget->getTableAsFlightPath();
    this->tempMapExecutionUIWidget = new MapExecution(fp);
    //this->qttWidget->setMapExecutionUIWidget( this->tempMapExecutionUIWidget );

 //   qDebug() << "URL BEFORE: " << this->MapPlanningMapUIWidget->url();
 //   this->MapPlanningMapUIWidget->load(QUrl("qrc:/res/html/mapsPlanning.html"));
    this->tempMapExecutionUIWidget->ui->webView = this->MapPlanningMapUIWidget;
    this->tempMapExecutionUIWidget->addNewMap();
 //   qDebug() << "URL AFTER: " << this->MapPlanningMapUIWidget->url();

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

    this->missionPlanningWindowUIWidget->uavComboBox->hide();

    this->missionPlanningWindowUIWidget->missionPlanComboBox->hide();

    //delete tempMapPlanningUIWidget ;

    //tempMapPlanningUIWidget = NULL;

    //TODO Add addButtons function to take a list of buttons in the missionplanningwindow class

    this->missionPlanningWindowUIWidget->addButton( this->tempMapExecutionUIWidget->ui->backButton ) ;

    this->missionPlanningWindowUIWidget->addButton( this->tempMapExecutionUIWidget->ui->cancelButton );

    this->missionPlanningWindowUIWidget->addButton( this->tempMapExecutionUIWidget->ui->finishButton );

    this->missionPlanningWindowUIWidget->changeTitle( QString( "Mission Execution" ) ) ;

    connect( this->tempMapExecutionUIWidget->ui->backButton, SIGNAL(clicked()), this, SLOT(clickedBackButton_MainDisplay()) );

    connect( this->tempMapExecutionUIWidget->ui->cancelButton, SIGNAL(clicked()), this, SLOT(clickedCancelButton_MainDisplay()) );

    connect( this->tempMapExecutionUIWidget->ui->finishButton, SIGNAL(clicked()), this, SLOT(clickedFinishButton_MainDisplay()) );

}

void MainMDIDisplay::destroy() {

    /* PRIVATE SLOT */

    delete this;

}

void MainMDIDisplay::switchToRecapWindow() {

    this->tempMapRecapUIWidget = this->tempMapExecutionUIWidget->getMapRecap();

    //TODO May not be necessary since the URL appears to be the same before and after

    qDebug() << "URL BEFORE: " << this->MapPlanningMapUIWidget->url() ;
    this->tempMapRecapUIWidget->ui->webView = this->MapPlanningMapUIWidget;
    this->tempMapRecapUIWidget->updateMap();

//    this->MapPlanningMapUIWidget = this->tempMapRecapUIWidget->ui->webView ;
//    this->tempMapRecapUIWidget->updateMap();

    qDebug() << "URL AFTER: " << this->MapPlanningMapUIWidget->url() ;

    this->MapRecapUI_TableTab = this->tempMapRecapUIWidget->getTab( 1 );

    this->MapRecapUI_GraphTab = this->tempMapRecapUIWidget->getTab( 2 );

    this->qttWidget->addNewTab( this->MapRecapUI_TableTab , QString( "Table (Recap)" ) );

    this->qttWidget->addNewTab( this->MapRecapUI_GraphTab , QString( "Graph (Recap)" ) );

    this->backToPlanningButton = this->tempMapRecapUIWidget->ui->backButton /* this->tempMapRecapUIWidget->getBackToPlanningButton() */ ;

    this->missionPlanningWindowUIWidget->addButton( this->backToPlanningButton );

    connect( this->backToPlanningButton , SIGNAL( clicked() ) , this , SLOT ( clickedBackToPlanningButton_MainDisplay() ) ) ;

    this->missionPlanningWindowUIWidget->changeTitle( QString( "Mission Recap" ) ) ;

}

void MainMDIDisplay::clickedBackToPlanningButton_MainDisplay() {

    this->clearMapRecap();
    this->switchToPlanningWindow();

    /* this->clearMapRecap(); */

}

void MainMDIDisplay::clickedFinishButton_MainDisplay() {

    this->switchToRecapWindow();

    this->clearMapExecution();

}

//TODO Add error messages that pop up under else
void MainMDIDisplay::clearMapRecap() {

    if ( this->qttWidget->ui->tabWidget->tabText( 1 ) == QString( "Table (Recap)" ) ) {

        this->qttWidget->ui->tabWidget->removeTab( 1 ) ;

    }

    else {

        /* Do nothing */

    }

    if ( this->qttWidget->ui->tabWidget->tabText( 1 ) == QString( "Graph (Recap)" ) ) {

        this->qttWidget->ui->tabWidget->removeTab( 1 ) ;

    }

    else {

        /* Do nothing */

    }

    if ( this->backToPlanningButton != NULL ) {

        this->backToPlanningButton->hide();

    }

    else {

        /* Do nothing */

    }

}

//TODO Add error messages that pop up under else
void MainMDIDisplay::clearMapExecution() {

    if ( this->tempMapExecutionUIWidget->ui->cancelButton != NULL ) {

        this->tempMapExecutionUIWidget->ui->cancelButton->hide() ;

    }

    else {

        /* Do nothing */

    }

    if ( this->tempMapExecutionUIWidget->ui->finishButton != NULL ) {

        this->tempMapExecutionUIWidget->ui->finishButton->hide() ;

    }

    else {

        /* Do nothing */

    }

    if ( this->tempMapExecutionUIWidget->ui->backButton != NULL ) {

        this->tempMapExecutionUIWidget->ui->backButton->hide() ;

    }

    else {

        /* Do nothing */

    }

    if ( this->tempMapExecutionUIWidget->conTime != NULL ) {

        this->tempMapExecutionUIWidget->conTime->deleteLater() ;

        this->tempMapExecutionUIWidget->conTime = NULL ;

    }

    else {

        /* Do nothing. */

    }

    if ( this->tempMapExecutionUIWidget->ui != NULL ) {

        delete this->tempMapExecutionUIWidget->ui ;

        this->tempMapExecutionUIWidget = NULL ;

    }

    else {

        /* Do nothing. */

    }

    if ( this->qttWidget->ui->tabWidget->tabText( 1 ) == QString( "Network Status (Execution)" ) ) {

        this->qttWidget->ui->tabWidget->removeTab( 1 );

    }

    else {

        /* Do nothing */

    }

    if ( this->qttWidget->ui->tabWidget->tabText( 1 ) == QString( "Table (Execution)" ) ) {

        this->qttWidget->ui->tabWidget->removeTab( 1 );

    }

    else {

        /* Do nothing */

    }
    this->tempMapExecutionUIWidget->deleteLater();
}

void MainMDIDisplay::clickedCancelButton_MainDisplay() {

    this->switchToPlanningWindow();
    this->clearMapExecution();

    /* TODO DELETE MAP EXECUTION */

}

void MainMDIDisplay::clickedBackButton_MainDisplay() {

    //this->destroy() ;

}
