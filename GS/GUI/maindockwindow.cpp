#include "maindockwindow.h"
#include "ui_maindockwindow.h"
#include <QDebug>
#include <QQuickItem>
#include "qfi_ASI.h"
#include <QtCore>
#include <QMargins>

MainDockWindow::MainDockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDockWindow)
{
    ui->setupUi(this);
    centralWidget = new QStackedWidget(this);
    QQuickWidget * mapWidget = createQmlWidget(QUrl("qrc:/res/map.qml"), this);
    centralWidget->addWidget(mapWidget);
    setCentralWidget(centralWidget);

    link = new UdpLink();
    link->startLink();
    mission = new Mission();

//    link = new SerialLink();
//    link->startLink();

    Decoder * decoder = new Decoder();
    decoder->setLink(link);
    connectDecoder(decoder);

    Encoder * encoder = new Encoder();
    encoder->setLink(link);
    connectEncoder(encoder);

    addToolBarButtons();

    QPushButton * p;
    p = new QPushButton("send test mission");
    connect(p, &QPushButton::clicked, this, &MainDockWindow::test);
    QDockWidget * bdock = createDockWidget("send mission",Qt::BottomDockWidgetArea, p, this);
    QLabel * n = new QLabel();
    bdock->setTitleBarWidget(n);

    ui->movementWidget->setUAVMap(mapWidget);
    try{
        interop = new Interop("testuser","testpass");
        ui->flightPathWidget->updateStuff(interop,mapWidget);
        Obstacles obstacles = interop->getObstacles();
        obstacles.loadStationaryObjects(mapWidget);
    } catch (QNetworkReply::NetworkError err) {
        qDebug() << "! Not loading map objects: " << err;
    }
    ui->actionWidget->setAttribute(Qt::WA_TranslucentBackground);
    ui->actionDock->setAttribute(Qt::WA_TranslucentBackground);
}

void MainDockWindow::addToolBarButtons() {
    foreach(QDockWidget * dw, this->findChildren<QDockWidget*>()) {
       ui->toolBar->addAction(dw->toggleViewAction());
    }
}

void MainDockWindow::connectDecoder(Decoder * decoder) {
    connect(decoder, &Decoder::vfrHudReceived, ui->qfiWidget, &QFIWidget::updateVFR);
    connect(decoder, &Decoder::attReceived, ui->qfiWidget, &QFIWidget::updateAttitude);
    connect(decoder, &Decoder::pressureReceived, ui->qfiWidget, &QFIWidget::updatePressure);
    connect(decoder, &Decoder::gpsReceived, ui->movementWidget, &MovementWidget::updateTelemetry);
    //connect (decoder, &Decoder::gpsReceived, uav, &UAV::updatepos);
    connect(decoder, &Decoder::attReceived, ui->movementWidget, &MovementWidget::updateAttitude);
    connect(decoder, &Decoder::localPositionReceived, ui->movementWidget, &MovementWidget::updateLocalPosition);
    connect(decoder, &Decoder::gpsReceived, ui->graphWidget, &GraphWidget::appendTelemData);
    connect(decoder, &Decoder::heartbeatReceived, ui->statusWidget, &StatusWidget::updateHeartbeat);
    connect(decoder, &Decoder::heartbeatReceived, ui->actionWidget, &ActionWidget::toggleArmButton);
    connect(decoder, &Decoder::heartbeatReceived, ui->actionWidget, &ActionWidget::toggleModeButtons);
    connect(decoder, &Decoder::batteryReceived, ui->statusWidget, &StatusWidget::updateBattery);
    connect(decoder, &Decoder::statTextReceived, ui->messageWidget, &MessageWidget::updateMessages);
    connect(decoder, &Decoder::mrequestReceived, mission, &Mission::loadWaypoint);
}

void MainDockWindow::connectEncoder(Encoder * encoder) {
    connect(ui->actionWidget, &ActionWidget::setArm, encoder, &Encoder::sendArm);
    connect(ui->actionWidget, &ActionWidget::setAuto, encoder, &Encoder::sendSetAuto);
    connect(ui->actionWidget, &ActionWidget::setGuided, encoder, &Encoder::sendSetGuided);
    connect(ui->actionWidget, &ActionWidget::setManual, encoder, &Encoder::sendSetManual);
    connect(mission, &Mission::loadToUAV, encoder, &Encoder::sendMissionItem);
    connect(this, &MainDockWindow::what, encoder, &Encoder::sendMissionCount);

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
