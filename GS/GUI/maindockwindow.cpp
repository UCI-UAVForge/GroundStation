#include "maindockwindow.h"
#include "ui_maindockwindow.h"


MainDockWindow::MainDockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDockWindow)
{

    try{
        interop = new Interop("testuser","testpass");
    } catch (QNetworkReply::NetworkError err) {
        qDebug() << "! Not loading map objects: " << err;
    }
    centralWidget = new QStackedWidget(this);
    QQuickWidget * mapWidget = createQmlWidget(QUrl("qrc:/res/map.qml"), this);
    centralWidget->addWidget(mapWidget);
    setCentralWidget(centralWidget);

    Link * link = new Link();
    link->startLink();
    Decoder * decoder = new Decoder();
    decoder->setLink(link);

    toolBar = new ToolBar(this);

    GraphWidget * graphWidget = new GraphWidget(this);
    QDockWidget * graphDock = createDockWidget("Graph",Qt::BottomDockWidgetArea, graphWidget, this);
    QDockWidget * tableDock = createDockWidget("Table",Qt::BottomDockWidgetArea, new TableWidget(this), this);
    QDockWidget * missionDetailsDock = createDockWidget("Mission Details",Qt::BottomDockWidgetArea, new missionDetailsWindow(this,interop,mapWidget), this);
    QDockWidget * timerDock = createDockWidget("Timer",Qt::RightDockWidgetArea, new Timer(this), this);
    graphDock->setMinimumWidth(500);
    tableDock->setMinimumWidth(500);
    missionDetailsDock->setMinimumWidth(500);

    //Connect all widgets to decoder like this.
    MovementWidget * movementWidget = new MovementWidget(this);
    StatusWidget * statusWidget = new StatusWidget(this);
    connect(decoder, &Decoder::gpsReceived, movementWidget, &MovementWidget::updateTelemetry);
    connect(decoder, &Decoder::attReceived, movementWidget, &MovementWidget::updateAttitude);
    connect(decoder, &Decoder::gpsReceived, graphWidget, &GraphWidget::appendTelemData);

    QDockWidget * movementDock = createDockWidget("Movement", Qt::RightDockWidgetArea, movementWidget, this);
    QDockWidget * statusDock = createDockWidget("Status", Qt::RightDockWidgetArea, statusWidget, this);
    tabifyDockWidget(movementDock, statusDock);
    movementDock->setMaximumHeight(300);
    movementDock->setMinimumWidth(230);
    graphDock->setVisible(true);
    tableDock->setVisible(true);
    missionDetailsDock->setVisible(true);
    timerDock->setVisible(true);
    movementDock->setVisible(true);
    statusDock->setVisible(true);

    toolBar->addAction("Test find", this, &MainDockWindow::testFind);
    toolBar->addAction("Hide All Widgets", this, &MainDockWindow::hideDockWidgets);
    //toolBar->addAction("Close All Widgets", this, &MainDockWindow::closeDockWidgets);
    addToolBar(toolBar);

//    Mission mission = interop->getMission(1);
//    mission.loadMissionObjects(mapWidget);
    Obstacles obstacles = interop->getObstacles();
    obstacles.loadStationaryObjects(mapWidget);
    qDebug()<<mapWidget;
//    std::thread update_mov_obj(whatever,1);
}


QDockWidget * MainDockWindow::createDockWidget(const QString &title, Qt::DockWidgetArea area, QWidget * child, QWidget * parent) {
    QDockWidget * dock = new QDockWidget(title, parent);
    dock->setWidget(child);
    addDockWidget(area, dock);
    dock->setVisible(false);
    toolBar->addAction(dock->toggleViewAction());
    return dock;
}

QQuickWidget * MainDockWindow::createQmlWidget(QUrl qmlSource, QWidget * parent) {
    QQuickWidget * quickWidget = new QQuickWidget(parent);
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->setSource(qmlSource);
    return quickWidget;
}

void MainDockWindow::testFind() {
    qDebug() << this->findChild<GraphWidget*>();
}

void MainDockWindow::hideDockWidgets() {
    foreach(QDockWidget * dw, this->findChildren<QDockWidget*>()) {
        dw->setVisible(false);
    }
}
void MainDockWindow::closeDockWidgets() {
    foreach(QDockWidget * dw, this->findChildren<QDockWidget*>()) {
        delete dw;
    }
}


void MainDockWindow::updateMovingObjects(QQuickWidget * mapWidget){
    Obstacles obstacles = interop->getObstacles();
    obstacles.updateMovingObjects(mapWidget);
}

MainDockWindow::~MainDockWindow()
{
    delete ui;
}
