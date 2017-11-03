#include "maindockwindow.h"
#include "ui_maindockwindow.h"
#include <QDebug>


MainDockWindow::MainDockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDockWindow)
{
    centralWidget = new QStackedWidget(this);
    toolBar = new ToolBar(this);
    QQuickWidget * mapWidget = createQmlWidget(QUrl("qrc:/res/map.qml"), this);
    centralWidget->addWidget(mapWidget);
    QDockWidget * graphDock = createDockWidget("Graph",Qt::BottomDockWidgetArea, new GraphWidget(this), this);
    QDockWidget * tableDock = createDockWidget("Table",Qt::BottomDockWidgetArea, new TableWidget(this), this);
    QDockWidget * timerDock = createDockWidget("Timer",Qt::RightDockWidgetArea, new TimerWidget(this), this);
    graphDock->setMinimumWidth(500);
    tableDock->setMinimumWidth(500);
    toolBar->addAction(graphDock->toggleViewAction());
    toolBar->addAction(tableDock->toggleViewAction());
    toolBar->addAction(timerDock->toggleViewAction());
    toolBar->addAction("Test find", this, &MainDockWindow::testFind);
    toolBar->addAction("Hide All Widgets", this, &MainDockWindow::hideDockWidgets);
    //toolBar->addAction("Close All Widgets", this, &MainDockWindow::closeDockWidgets);
    addToolBar(toolBar);
    setCentralWidget(centralWidget);


    loadMapObjects(mapWidget);
}

QDockWidget * MainDockWindow::createDockWidget(const QString &title, Qt::DockWidgetArea area, QWidget * child, QWidget * parent) {
    QDockWidget * dock = new QDockWidget(title, parent);
    dock->setWidget(child);
    addDockWidget(area, dock);
    dock->setVisible(false);
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
//    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "showMarker",
//            Q_ARG(QVariant, 33.6405),
//            Q_ARG(QVariant, -117.8943));

    link link;
    Interop interop("testuser", "testpass");
    Mission mission = interop.getMission(1);

    if (!mission.isActive())
        return;


//    QJsonValue loc = mission.get_fly_zones();
//    QJsonArray = loc.toArray();
//    qDebug() << loc[0];

    qDebug() << "search grid points "<< mission.get_search_grid_points();
    qDebug() << "mission waypoints" << mission.get_mission_waypoints();
    qDebug() << "fly zones" << mission.get_fly_zones();
    qDebug() << "emergent" << mission.get_emergent_last_known_pos();
    qDebug() << "home" << mission.get_home_pos();
    qDebug() << "air drop" << mission.get_air_drop_pos();

    QJsonArray temp = mission.get_search_grid_points();
    for(int i=0; i<temp.size();++i){
        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                Q_ARG(QVariant, "images/blue_pin"),
                Q_ARG(QVariant, temp[i].toObject()["latitude"].toVariant()),
                Q_ARG(QVariant, temp[i].toObject()["longitude"].toVariant()));
    }

    temp = mission.get_mission_waypoints();
    for(int i=0; i<temp.size();++i){
        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                Q_ARG(QVariant, "images/green_pin"),
                Q_ARG(QVariant, temp[i].toObject()["latitude"].toVariant()),
                Q_ARG(QVariant, temp[i].toObject()["longitude"].toVariant()));
    }

    temp = mission.get_fly_zones();
    for(int i=0; i<temp.size();++i){
        QJsonObject temp2 = temp[i].toObject();
        //temp2 form: {"altitude_msl_max":Qvariable,
        //             "altitude_msl_min":QVariable,
        //             "boundary_pts":QJsonArray<QJsonObject> { "latitude":QVariable,
        //                                                      "longitude":QVariable,
        //                                                      "order":int
        //                                                    }
        //             }
        QJsonArray temp3 = temp2["boundary_pts"].toArray();
        for (int j=0;j<temp3.size();++j){
            QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                    Q_ARG(QVariant, "images/yellow_pin"),
                    Q_ARG(QVariant, temp3[j].toObject()["latitude"].toVariant()),
                    Q_ARG(QVariant, temp3[j].toObject()["longitude"].toVariant()));
        }

    }

    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, "images/blue_circle"),
            Q_ARG(QVariant, mission.get_off_axis_odlc_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_off_axis_odlc_pos()["longitude"].toVariant()));

    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, "images/green_circle"),
            Q_ARG(QVariant, mission.get_emergent_last_known_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_emergent_last_known_pos()["longitude"].toVariant()));

    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, "images/tent"),
            Q_ARG(QVariant, mission.get_home_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_home_pos()["longitude"].toVariant()));

    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, "images/crosshair"),
            Q_ARG(QVariant, mission.get_air_drop_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_air_drop_pos()["longitude"].toVariant()));


}



MainDockWindow::~MainDockWindow()
{
    delete ui;
}
