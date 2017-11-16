#include "maindockwindow.h"
#include "ui_maindockwindow.h"
#include <QDebug>
#include <QQuickItem>
#include "mapwidget.h"
#include "qfi_ASI.h"
#include <QtCore>
#include "textbox.h"

MainDockWindow::MainDockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDockWindow)
{
    ui->setupUi(this);
    centralWidget = new QStackedWidget(this);
    QQuickWidget * mapWidget = createQmlWidget(QUrl("qrc:/res/map.qml"), this);
    centralWidget->addWidget(mapWidget);
    setCentralWidget(centralWidget);

    link = new UdpLink(QHostAddress::LocalHost, 5761, QHostAddress("127.0.0.1"), 14550);
    link->startLink();
    Decoder * decoder = new Decoder();
    decoder->setLink(link);

    toolBar = new ToolBar(this);
    Timer * timer = new Timer(this);

    GraphWidget * graphWidget = new GraphWidget(this);
    ActionWidget * actionWidget = new ActionWidget(this);
    actionWidget->setLink(link);
    MovementWidget * movementWidget = new MovementWidget(this);
    StatusWidget * statusWidget = new StatusWidget(this);
    statusWidget->setLink(link);

    QDockWidget * graphDock = createDockWidget("Graph",Qt::BottomDockWidgetArea, graphWidget, this);
    QDockWidget * tableDock = createDockWidget("Table",Qt::BottomDockWidgetArea, new TableWidget(this), this);
    QDockWidget * timerDock = createDockWidget("Timer",Qt::RightDockWidgetArea, timer, this);
    QDockWidget * actionDock = createDockWidget("Actions", Qt::RightDockWidgetArea, actionWidget, this);
    QDockWidget * movementDock = createDockWidget("Movement", Qt::RightDockWidgetArea, movementWidget, this);
    QDockWidget * statusDock = createDockWidget("Status", Qt::RightDockWidgetArea, statusWidget, this);

    graphDock->setMinimumWidth(500);
    tableDock->setMinimumWidth(500);
    //Connect all widgets to decoder like this;
    connect(decoder, &Decoder::gpsReceived, movementWidget, &MovementWidget::updateTelemetry);
    connect(decoder, &Decoder::attReceived, movementWidget, &MovementWidget::updateAttitude);
    connect(decoder, &Decoder::gpsReceived, graphWidget, &GraphWidget::appendTelemData);
    connect(decoder, &Decoder::heartbeatReceived, statusWidget, &StatusWidget::updateHeartbeat);
    connect(decoder, &Decoder::armSuccess, actionWidget, &ActionWidget::toggleArmButton);
    connect(decoder, &Decoder::armFailed, actionWidget, &ActionWidget::armFailed);
    connect(decoder, &Decoder::heartbeatReceived, actionWidget, &ActionWidget::toggleModeButtons);
    connect(decoder, &Decoder::batteryReceived, statusWidget, &StatusWidget::updateBattery);


    tabifyDockWidget(movementDock, statusDock);

    movementDock->setVisible(true);
    actionDock->setVisible(true);


   // tlink = new TcpLink();
   // decoder->setLink(tlink);
    toolBar->addAction("Hide All Widgets", this, &MainDockWindow::hideDockWidgets);
    toolBar->addAction("setmode", this, &MainDockWindow::sendCommand);

    //toolBar->addAction("Close All Widgets", this, &MainDockWindow::closeDockWidgets);
    addToolBar(toolBar);
    connect(timer, &Timer::timeChanged, this, &MainDockWindow::testMav);

    try {
        loadMapObjects(mapWidget);
    } catch (QNetworkReply::NetworkError err) {
        qDebug() << "! Not loading map objects: " << err;
    }

}

void MainDockWindow::testMav() {
    mavlink_message_t heart;
    mavlink_msg_heartbeat_pack(255, 1 , &heart, 1, 3, 81, 0, 3);
    //link->sendMsg(heart);
}



void MainDockWindow::sendCommand() {
    mavlink_message_t msg;
    mavlink_message_t msg2;
    mavlink_msg_set_mode_pack(255,  1 , &msg, 1, 1, 10);
    //mavlink_msg_mission_set_current_pack(255,1, &msg, 1, 0, 3);
   // mavlink_msg_mission_item_pack(255, 1 , &msg, 1, 0, 0, MAV_FRAME_MISSION, MAV_CMD_NAV_WAYPOINT, 1, 1, 10, 5, 0, 0, 12.21,38, 1000);
    //mavlink_msg_command_long_pack(255, 1, &msg, 1, 0,400, 1, 1, 0, 0,0,0, 0, 0);
    link->sendMsg(msg);
}

QDockWidget * MainDockWindow::createDockWidget(const QString &title, Qt::DockWidgetArea area, QWidget * child, QWidget * parent) {
    QDockWidget * dock = new QDockWidget(title, parent);
    dock->setWidget(child);
    addDockWidget(area, dock);
    dock->setVisible(false);
   // dock->setStyleSheet("QDockWidget {background-color:rgb(0,0,0)}");
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

void MainDockWindow::loadMapObjects(QQuickWidget * mapWidget){
    Interop interop("testuser", "testpass");
    Mission mission = interop.getMission(1);

    if (!mission.isActive())
        return;




    //-----------------------------------------------------Search Grid Points------------------------------------------------
    QJsonArray temp = mission.get_search_grid_points();
    QJsonArray pathlat;
    QJsonArray pathlon;
    for(int i=0; i<temp.size();++i){
        pathlat.append(temp[i].toObject()["latitude"]);
        pathlon.append(temp[i].toObject()["longitude"]);

        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                Q_ARG(QVariant, ""),
                Q_ARG(QVariant, "images/blue_pin"),
                Q_ARG(QVariant, temp[i].toObject()["latitude"].toVariant()),
                Q_ARG(QVariant, temp[i].toObject()["longitude"].toVariant()),
                Q_ARG(QVariant, "/2"),
                Q_ARG(QVariant, ""));
    }
    if (temp.size() > 1){
        pathlat.append(temp[0].toObject()["latitude"]);
        pathlon.append(temp[0].toObject()["longitude"]);

        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addLine",
                                  Q_ARG(QVariant, ""),
                                  Q_ARG(QVariant, 3),
                                  Q_ARG(QVariant, "blue"),
                                  Q_ARG(QVariant, pathlat),
                                  Q_ARG(QVariant, pathlon),
                                  Q_ARG(QVariant, temp.size()));
    }
    Clear(pathlat);
    Clear(pathlon);


    //-----------------------------------------------------Mission Waypoints------------------------------------------------
    temp = mission.get_mission_waypoints();
    for(int i=0; i<temp.size();++i){
        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                Q_ARG(QVariant, ""),
                Q_ARG(QVariant, "images/green_pin"),
                Q_ARG(QVariant, temp[i].toObject()["latitude"].toVariant()),
                Q_ARG(QVariant, temp[i].toObject()["longitude"].toVariant()),
                Q_ARG(QVariant, "/2"),
                Q_ARG(QVariant, ""));
    }
    if (temp.size() > 1){
        pathlat.append(temp[0].toObject()["latitude"]);
        pathlon.append(temp[0].toObject()["longitude"]);

        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addLine",
                                  Q_ARG(QVariant, ""),
                                  Q_ARG(QVariant, 3),
                                  Q_ARG(QVariant, "blue"),
                                  Q_ARG(QVariant, pathlat),
                                  Q_ARG(QVariant, pathlon),
                                  Q_ARG(QVariant, temp.size()));
    }
    Clear(pathlat);
    Clear(pathlon);

    //-----------------------------------------------------No-Fly Zone Boundary Points (also contains max/min altitude)------------------------------------------------
    temp = mission.get_fly_zones();
    for(int i=0; i<temp.size();++i){
        QJsonObject temp2 = temp[i].toObject();
        QJsonArray temp3 = temp2["boundary_pts"].toArray();
        for (int j=0;j<temp3.size();++j){
            pathlat.append(temp3[j].toObject()["latitude"]);
            pathlon.append(temp3[j].toObject()["longitude"]);
            QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                    Q_ARG(QVariant, ""),
                    Q_ARG(QVariant, "images/yellow_pin"),
                    Q_ARG(QVariant, temp3[j].toObject()["latitude"].toVariant()),
                    Q_ARG(QVariant, temp3[j].toObject()["longitude"].toVariant()),
                    Q_ARG(QVariant, "/2"),
                    Q_ARG(QVariant, ""));
        }


        if (temp3.size() > 1){
            pathlat.append(temp3[0].toObject()["latitude"]);
            pathlon.append(temp3[0].toObject()["longitude"]);

            QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addLine",
                                      Q_ARG(QVariant, ""),
                                      Q_ARG(QVariant, 3),
                                      Q_ARG(QVariant, "yellow"),
                                      Q_ARG(QVariant, pathlat),
                                      Q_ARG(QVariant, pathlon),
                                      Q_ARG(QVariant, temp3.size()+1));
        }

    }

    //-----------------------------------------------------Off Axis Odlc Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/blue_circle"),
            Q_ARG(QVariant, mission.get_off_axis_odlc_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_off_axis_odlc_pos()["longitude"].toVariant()),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"));

    //-----------------------------------------------------Emergent Last Known Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/green_circle"),
            Q_ARG(QVariant, mission.get_emergent_last_known_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_emergent_last_known_pos()["longitude"].toVariant()),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"));

    //-----------------------------------------------------Home Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/tent"),
            Q_ARG(QVariant, mission.get_home_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_home_pos()["longitude"].toVariant()),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"));

    //-----------------------------------------------------Air Drop Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/crosshair"),
            Q_ARG(QVariant, mission.get_air_drop_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_air_drop_pos()["longitude"].toVariant()),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"));


}


void MainDockWindow::Clear(QJsonArray &arr){
    for (int i=0; i<arr.size(); ++i){
        arr.removeFirst();
    }
}

MainDockWindow::~MainDockWindow()
{
    delete ui;
}
