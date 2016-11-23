#include "mainmdidisplay.h"
#include "ui_mainmdidisplay.h"

MainMDIDisplay::MainMDIDisplay(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainMDIDisplay),

    qttWidget(NULL) , MapSubWindow(NULL) , missionPlanningWindowUIWidget(NULL),

    tempMapExecutionUIWidget(NULL) , tempMapRecapUIWidget(NULL), backToPlanningButton(NULL),

    MapRecapUI_GraphTab(NULL) , MapRecapUI_TableTab(NULL) , currentMenu( Startup ) ,

    MapExecutionStatusVBoxLayout(NULL) , mapExecutionStatusUIWidget(NULL) , tempMapPlanningUIWidget(NULL) {

    ui->setupUi(this);

    ui->mdiArea->setBackground( QBrush( QPixmap( ":/res/images/UAVLogo.png" ) ) );

    this->qttWidget = new QtTabTest();

    this->addWindow( qttWidget /* , QString( "Data" ) */ );

    this->missionPlanningWindowUIWidget = new MissionPlanningWindow();

    //MapSubWindow will start off as window with an empty QWidget

    this->MapSubWindow = this->addWindow( &QWidget() );

    this->switchToPlanningWindow() ;

    //TODO Rename MissionPlanningWindow class to MissionControlWindow class

    this->MissionControlSubWindow = this->addWindow( this->missionPlanningWindowUIWidget );

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

    if ( this->currentMenu == Recap || this->currentMenu == Startup ) {

        this->tempMapPlanningUIWidget = new MapPlanning();

        //Add the map planning table to the tab widget window

        //TODO Is the line below necessary anymore?

        this->qttWidget->setMapPlanningUIWidget( this->tempMapPlanningUIWidget ) ;

        this->qttWidget->addNewTab( this->tempMapPlanningUIWidget->ui->tableView , QString( "Table (Mission Planning)" ) );

        // Remove the old Mission Planning table in favor of the new one if we just completed a mission.

        // The mission planning table tab added above would have a tab index of 1 and not 0.

        if ( ( this->currentMenu == Recap ) &&

             ( this->qttWidget->ui->tabWidget->tabText( 0 ) == QString( "Table (Mission Planning)" ) ) ) {

            qDebug() << "NEW MAP PLANNING!" ;

            this->qttWidget->ui->tabWidget->removeTab( 0 ) ;

        }

        else {

            /* Do nothing */

        }

        //Add the three buttons from MapPlanning to the Mission Planning window

        connect ( this->tempMapPlanningUIWidget->ui->backButton , SIGNAL( clicked() ) , this , SLOT( destroy() ) ) ;

        connect ( this->tempMapPlanningUIWidget->ui->executeButton , SIGNAL( clicked() ) , this , SLOT ( beginMapExecution() ) ) ;

    }

    else {

        /* Do nothing. */

    }

    this->MapSubWindow->setWidget( this->tempMapPlanningUIWidget->ui->webView );

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

    this->currentMenu = Planning ;

}

QtTabTest * MainMDIDisplay::getQttWidget() const {

    return qttWidget;

}

void MainMDIDisplay::setQttWidget( QtTabTest * value) {

    qttWidget = value;

}

QMdiSubWindow * MainMDIDisplay::addWindow( QWidget * myNewWindowWidget ) {

    /* TODO Default window style should go here by making all of the windows conform to the same
     * stylesheet - Roman Parise */

    /* Second argument - turns off the 'X' in the subwindows */

    QMdiSubWindow * mdiSubWindowToReturn = NULL ;

    mdiSubWindowToReturn = ui->mdiArea->addSubWindow( myNewWindowWidget , Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint );

    return mdiSubWindowToReturn ;

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

    /* 15 second timer. If the page is not loaded after 15 seconds, then just give up. */

    QTime timeToStopWaiting = QTime::currentTime().addSecs( 15 ) ;

    bool urlLoadSuccessStatus = false ;

    qDebug() << "Map execution trying to load at: " << QTime::currentTime() ;

    while ( QTime::currentTime() < timeToStopWaiting ) {

        if ( this->tempMapExecutionUIWidget->ui->webView->page()->mainFrame()->toHtml().contains( "</html>" ) ) {

            qDebug() << "Map execution load succeeded at time: " << QTime::currentTime() ;

            urlLoadSuccessStatus = true ;

            break ;

        }

        else {

            /* Do nothing. */

        }

    }

    if ( urlLoadSuccessStatus == true ) {

        //TODO Add error checking for if it isn't a webView object and therefore will have no url

        //qDebug() << "URL BEFORE: " << this->MapSubWindow->widget()->url();

        //this->MapPlanningMapUIWidget->setUrl(QUrl("qrc:/res/html/mapsExecution.html"));

        this->MapSubWindow->setWidget( this->tempMapExecutionUIWidget->ui->webView ) ;

        this->tempMapExecutionUIWidget->addNewMap();

        //qDebug() << "URL AFTER: " << this->MapSubWindow->widget()->url();

        this->MapExecutionStatusVBoxLayout->addWidget( this->tempMapExecutionUIWidget->ui->StatusIndicator );

        this->MapExecutionStatusVBoxLayout->addWidget( this->tempMapExecutionUIWidget->ui->StatusConsole );

        this->MapExecutionStatusVBoxLayout->addWidget( this->tempMapExecutionUIWidget->ui->clock );

        this->mapExecutionStatusUIWidget->setLayout( MapExecutionStatusVBoxLayout );

        this->qttWidget->addNewTab( this->mapExecutionStatusUIWidget , QString( "Network Status (Execution)" ) );

        this->qttWidget->addNewTab( this->tempMapExecutionUIWidget->ui->tableView , QString( "Table (Execution)" ) );

        this->changePlanningToExecutionWindow();

    }

    else {

        /* TODO LOL PLEASE FIX THIS */

        qDebug() << "Map execution load failed." ;

    }

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

    this->currentMenu = Execution ;

}

void MainMDIDisplay::destroy() {

    /* PRIVATE SLOT */

    delete this;

}

void MainMDIDisplay::switchToRecapWindow() {

    this->tempMapRecapUIWidget = this->tempMapExecutionUIWidget->getMapRecap();

    this->MapSubWindow->setWidget( this->tempMapRecapUIWidget->ui->webView );

    //TODO Change to for loop and search. Make a function to search the tabs.

    this->MapRecapUI_TableTab = this->tempMapRecapUIWidget->getTab( 1 );

    this->MapRecapUI_GraphTab = this->tempMapRecapUIWidget->getTab( 2 );

    this->qttWidget->addNewTab( this->MapRecapUI_TableTab , QString( "Table (Recap)" ) );

    this->qttWidget->addNewTab( this->MapRecapUI_GraphTab , QString( "Graph (Recap)" ) );

    this->backToPlanningButton = this->tempMapRecapUIWidget->ui->backButton /* this->tempMapRecapUIWidget->getBackToPlanningButton() */ ;

    this->missionPlanningWindowUIWidget->addButton( this->backToPlanningButton );

    connect( this->backToPlanningButton , SIGNAL( clicked() ) , this , SLOT ( clickedBackToPlanningButton_MainDisplay() ) ) ;

    this->missionPlanningWindowUIWidget->changeTitle( QString( "Mission Recap" ) ) ;

    this->currentMenu = Recap ;

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

        // Do nothing.

    }

    if ( this->tempMapExecutionUIWidget->ui->StatusConsole != NULL ) {

        this->tempMapExecutionUIWidget->ui->StatusConsole->deleteLater();

        this->tempMapExecutionUIWidget->ui->StatusConsole = NULL ;

    }

    else {

        //Do nothing.

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

    //TODO If tempMapExecutionUIWidget is NULL, then wouldn't you get errors above. Maybe assert or check this at the beginning?

    if ( this->tempMapExecutionUIWidget != NULL ) {

        this->tempMapExecutionUIWidget->deleteLater();

        this->tempMapExecutionUIWidget = NULL ;

    }

    else {

        /* Do nothing. */

    }

}

void MainMDIDisplay::clickedCancelButton_MainDisplay() {

    this->switchToPlanningWindow();

    this->clearMapExecution();

    /* TODO DELETE MAP EXECUTION */

}

void MainMDIDisplay::clickedBackButton_MainDisplay() {

    //this->destroy() ;

}
