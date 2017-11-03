#include "maindockwindow.h"
#include "ui_maindockwindow.h"
#include <QDebug>
#include <QQuickItem>

#include "link.h"
#include "decoder.h"
#include "infowidget.h"

MainDockWindow::MainDockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDockWindow)
{
    centralWidget = new QStackedWidget(this);
    QQuickWidget * mapWidget = createQmlWidget(QUrl("qrc:/res/map.qml"), this);
    centralWidget->addWidget(mapWidget);
    setCentralWidget(centralWidget);

    Link * link = new Link();
    link->startLink();
    Decoder * decoder = new Decoder();
    decoder->setLink(link);
    GraphWidget * graphWidget = new GraphWidget(this);
    QDockWidget * graphDock = createDockWidget("Graph",Qt::BottomDockWidgetArea, graphWidget, this);
    QDockWidget * tableDock = createDockWidget("Table",Qt::BottomDockWidgetArea, new TableWidget(this), this);
    QDockWidget * timerDock = createDockWidget("Timer",Qt::RightDockWidgetArea, new Timer(this), this);
    graphDock->setMinimumWidth(500);
    tableDock->setMinimumWidth(500);
    //graphWidget->appendTelemData();
 //   timerDock->setFixedSize(200, 100);
   // timerDock->setFloating(true);

    //Connect all widgets to decoder like this.
    InfoWidget * infoWidget = new InfoWidget(this);
    connect(decoder, &Decoder::gpsMsgReceived, infoWidget, &InfoWidget::updateTelemetry);
    connect(decoder, &Decoder::gpsMsgReceived, graphWidget, &GraphWidget::appendTelemData);
    QDockWidget * infoDock = createDockWidget("Info", Qt::RightDockWidgetArea, infoWidget, this);
    infoDock->setMaximumHeight(220);
    infoDock->setMinimumWidth(230);

    toolBar = new ToolBar(this);
    toolBar->addAction(graphDock->toggleViewAction());
    toolBar->addAction(tableDock->toggleViewAction());
    toolBar->addAction(timerDock->toggleViewAction());
    toolBar->addAction(infoDock->toggleViewAction());
    graphDock->setVisible(true);
    tableDock->setVisible(true);
    infoDock->setVisible(true);
    toolBar->addAction("Test find", this, &MainDockWindow::testFind);
    toolBar->addAction("Hide All Widgets", this, &MainDockWindow::hideDockWidgets);
    //toolBar->addAction("Close All Widgets", this, &MainDockWindow::closeDockWidgets);
    addToolBar(toolBar);
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
    Interop interop("testuser", "testpass");
    Mission mission = interop.getMission(1);

    if (!mission.isActive())
        return;

    //to-do: make the lines between each points!


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
                Q_ARG(QVariant, temp[i].toObject()["longitude"].toVariant()));
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
                Q_ARG(QVariant, temp[i].toObject()["longitude"].toVariant()));
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
                    Q_ARG(QVariant, temp3[j].toObject()["longitude"].toVariant()));
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
            Q_ARG(QVariant, mission.get_off_axis_odlc_pos()["longitude"].toVariant()));

    //-----------------------------------------------------Emergent Last Known Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/green_circle"),
            Q_ARG(QVariant, mission.get_emergent_last_known_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_emergent_last_known_pos()["longitude"].toVariant()));

    //-----------------------------------------------------Home Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/tent"),
            Q_ARG(QVariant, mission.get_home_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_home_pos()["longitude"].toVariant()));

    //-----------------------------------------------------Air Drop Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/crosshair"),
            Q_ARG(QVariant, mission.get_air_drop_pos()["latitude"].toVariant()),
            Q_ARG(QVariant, mission.get_air_drop_pos()["longitude"].toVariant()));


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
