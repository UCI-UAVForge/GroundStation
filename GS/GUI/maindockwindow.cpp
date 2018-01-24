#include "maindockwindow.h"
#include "ui_maindockwindow.h"
#include <QDebug>
#include <QQuickItem>
#include <QtCore>
#include <QMargins>

MainDockWindow::MainDockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDockWindow)
{
    ui->setupUi(this);
    ui->graphDock->hide();

    // UDP Link for SITL
    link = new UdpLink();

//     Serial link for RF900
  //     link = new SerialLink();

       link->startLink();

    mission = new Mission();
    uavButton = new UAVButton(this);

    Decoder * decoder = new Decoder();
    decoder->setLink(link);
    connectDecoder(decoder);

    Encoder * encoder = new Encoder();
    encoder->setLink(link);
    connectEncoder(encoder);

    Waypoint * waypoint = new Waypoint();
    connectWaypoint(waypoint, encoder, decoder);

    addToolBarButtons();

    QWidget* spacer = new QWidget();
    LoginWidget * loginWidget = new LoginWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->addWidget(spacer);
    ui->toolBar->addWidget(loginWidget);
    ui->toolBar->addWidget(uavButton);

    connect(loginWidget, &LoginWidget::connectionSuccess, ui->missionWidget, &MissionWidget::getMissions);
    connect(ui->missionWidget, &MissionWidget::drawMission, ui->mapWidget, &MapWidget::drawMission);
}

void MainDockWindow::addToolBarButtons() {
    foreach(QDockWidget * dw, this->findChildren<QDockWidget*>()) {
       ui->toolBar->addAction(dw->toggleViewAction());
    }
}

void MainDockWindow::addInteropLogin() {
    QWidget* spacer = new QWidget();
    LoginWidget * loginWidget = new LoginWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->addWidget(spacer);
    ui->toolBar->addWidget(loginWidget);
}

void MainDockWindow::connectDecoder(Decoder * decoder) {
    connect(decoder, &Decoder::vfrHudReceived, ui->qfiWidget, &QFIWidget::updateVFR);
    connect(decoder, &Decoder::attReceived, ui->qfiWidget, &QFIWidget::updateAttitude);
    connect(decoder, &Decoder::pressureReceived, ui->qfiWidget, &QFIWidget::updatePressure);
    connect(decoder, &Decoder::vfrHudReceived, ui->movementWidget, &MovementWidget::updateTelemetry);
    connect(decoder, &Decoder::attReceived, ui->movementWidget, &MovementWidget::updateAttitude);
    connect(decoder, &Decoder::localPositionReceived, ui->movementWidget, &MovementWidget::updateLocalPosition);
    connect(decoder, &Decoder::gpsReceived, ui->graphWidget, &GraphWidget::appendTelemData);
    connect(decoder, &Decoder::heartbeatReceived, ui->actionWidget, &ActionWidget::toggleArmButton);
    connect(decoder, &Decoder::heartbeatReceived, ui->actionWidget, &ActionWidget::toggleModeButtons);
    connect(decoder, &Decoder::statTextReceived, ui->messageWidget, &MessageWidget::updateMessages);
//    connect(decoder, &Decoder::mrequestReceived, mission, &Mission::loadWaypoint);

    connect(decoder, &Decoder::heartbeatReceived, uavButton, &UAVButton::updateHeartbeat);
    connect(decoder, &Decoder::statusReceived, uavButton, &UAVButton::updateBattery);

    connect(decoder, &Decoder::gpsReceived, ui->mapWidget, &MapWidget::updateUAVPosition);
    connect(decoder, &Decoder::vfrHudReceived, ui->mapWidget, &MapWidget::updateUAVHeading);
}

void MainDockWindow::connectEncoder(Encoder * encoder) {
    connect(ui->actionWidget, &ActionWidget::setArm, encoder, &Encoder::sendArm);
    connect(ui->actionWidget, &ActionWidget::setAuto, encoder, &Encoder::sendSetAuto);
    connect(ui->actionWidget, &ActionWidget::setGuided, encoder, &Encoder::sendClearAll);
    connect(ui->actionWidget, &ActionWidget::setManual, encoder, &Encoder::sendSetManual);
//    connect(mission, &Mission::lSoadToUAV, encoder, &Encoder::sendMissionItem);
}

void MainDockWindow::connectWaypoint(Waypoint * waypoint, Encoder * encoder, Decoder * decoder) {
    connect(waypoint, &Waypoint::reqClearAll, encoder, &Encoder::sendClearAll);
    connect(waypoint, &Waypoint::reqList, encoder, &Encoder::sendMissionRequestList);
    connect(waypoint, &Waypoint::reqWP, encoder, &Encoder::sendMissionRequest);
    connect(waypoint, &Waypoint::sendAck, encoder, &Encoder::sendMissionACK);
    connect(waypoint, &Waypoint::sendWP, encoder, &Encoder::sendMissionItem);
    connect(waypoint, &Waypoint::sendWPCount, encoder, &Encoder::sendMissionCount);
//    connect(waypoint, &Waypoint::sendWPSetCurrent, encoder, &Encoder::sendMissionSetCurrent);

    connect(decoder, &Decoder::mAckReceived, waypoint, &Waypoint::updateMissionAck);
    connect(decoder, &Decoder::missionCountReceived, waypoint, &Waypoint::updateMissionCount);
    connect(decoder, &Decoder::missionItemReceived, waypoint, &Waypoint::updateMissionItem);
//    connect(decoder, &Decoder::missionCurrentReceived, waypoint, &Waypoint::updateMissionCurrent);
    connect(decoder, &Decoder::mrequestReceived, waypoint, &Waypoint::updateMissionRequest);

    connect(ui->missionWidget, &MissionWidget::clearMissions, waypoint, &Waypoint::clearAllWaypoints);
    connect(ui->missionWidget, &MissionWidget::readMissionsSignal, waypoint, &Waypoint::readWaypointsList);
    connect(ui->missionWidget, &MissionWidget::writeMissionsSignal, waypoint, &Waypoint::writeWaypoints);
    connect(waypoint, &Waypoint::waypointsReceived, ui->missionWidget, &MissionWidget::readMissions);
    connect(waypoint, &Waypoint::waypointsWriteStatus, ui->missionWidget, &MissionWidget::writeMissionsStatus);
}

void MainDockWindow::test() {
    emit (what(2));
}

QDockWidget * MainDockWindow::createDockWidget(const QString &title, Qt::DockWidgetArea area, QWidget * child, QWidget * parent) {
    QDockWidget * dock = new QDockWidget(title, parent);
    dock->setWidget(child);
    addDockWidget(area, dock);
    dock->setVisible(false);
    ui->toolBar->addAction(dock->toggleViewAction());
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
