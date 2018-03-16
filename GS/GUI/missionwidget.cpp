#include "missionwidget.h"
#include "ui_missionwidget.h"
//#include "qtmaterialraisedbutton.h"
#include <QDebug>

MissionWidget::MissionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionWidget)
{
    ui->setupUi(this);
    style = Style();
    missions = new QVector<Mission*>();
    ui->missionList->setEditable(true);
    ui->missionList->lineEdit()->setReadOnly(true);
    ui->missionList->lineEdit()->setAlignment(Qt::AlignCenter);
    connect(ui->loadButton, &QPushButton::clicked, this, &MissionWidget::loadMission);
    connect(ui->drawButton, &QPushButton::clicked, this, &MissionWidget::drawCurrentMission);
    connect(ui->writeButton, &QPushButton::clicked, this, &MissionWidget::writeButtonClicked);
    connect(ui->readButton, &QPushButton::clicked, this, &MissionWidget::readButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MissionWidget::clearButtonClicked);
    connect(ui->missionList, SIGNAL(currentIndexChanged(int)), this, SLOT(updateInteropMission(int)));

    connect(ui->interopMission, &MissionTable::selectWaypoint, this, &MissionWidget::selectWaypoint);
    connect(ui->interopMission, &MissionTable::moveWaypoint, this, &MissionWidget::moveWaypoint);
    connect(ui->interopMission, &MissionTable::editMode, this, &MissionWidget::editMode);

    foreach(QPushButton * p, this->findChildren<QPushButton*>()) {
        if (p->objectName() == "clearButton") {
            style.setButtonOff(p);
        } else {
            style.setButtonDefault(p);
        }
    }

    if (test_mission) {
        missions->append(new Mission(testReadJSON_mission("2"), testReadJSON_obstacle()));
        ui->missionList->addItem("*TEST MISSION_FT*");
        ui->missionList->setItemData(0, Qt::AlignCenter, Qt::TextAlignmentRole);

        missions->append(new Mission(testReadJSON_mission(""), testReadJSON_obstacle()));
        ui->missionList->addItem("*TEST MISSION*");
        ui->missionList->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);


        QStandardItemModel * test_mission_model = createMissionModel(missions->at(ui->missionList->currentIndex()));
        ui->interopMission->setTableModel(test_mission_model);
    }
}

bool MissionWidget::hasMission() {
    return missions->size() > 0;
}

void MissionWidget::drawCurrentMission() {
    emit(clearMap());
    if (hasMission()) {
        if (ui->tabWidget->currentIndex() == 1 && generatedMission) {
            drawMission(generatedMission);
            for (QPolygonF obst_poly : generatedMission->get_obstacles()) {
                emit(drawObstacle(obst_poly, QColor("red"), "Obstacle"));
            }
        }
        else {
            for (QPolygonF obst_poly : interopMission->get_obstacles()) {
                emit(drawObstacle(obst_poly, QColor("red"), "Obstacle"));
            }
            drawMission(interopMission);
        }
    }
}

void MissionWidget::loadMission() {
    if (hasMission()) {
        PlanMission pm;
        if (!generatedMission)
            generatedMission = new Mission(*interopMission);
        else {
            delete generatedMission;
            generatedMission = new Mission(*interopMission);
        }
        for (int i = 1; i < generatedMission->mission_waypoints.waypoints->size(); i++) {
            QVector3D point = generatedMission->mission_waypoints.waypoints->at(i);
            qDebug() << "X: " << point.x() << " Y: " << point.y() << " Z: " << point.z();
            pm.add_goal_point(Point::fromGeodetic(point.x(), point.y(), point.z()));
        }
        QVector3D start_point = generatedMission->mission_waypoints.waypoints->at(0);
        qDebug() << "Start X: " << start_point.x() << " Y: " << start_point.y() << " Z: " << start_point.z();

//         Currently not working - path finding returns 0
        pm.set_obstacles(generatedMission->obstacles);
        QList<QVector3D>* waypoints = generatedMission->mission_waypoints.waypoints;
        waypoints->clear();
        QList<QVector3D>* path = pm.get_path(Point::fromGeodetic(start_point.x(), start_point.y(), start_point.z()),
                                 generatedMission->fly_zones);
        waypoints->reserve(waypoints->size() + std::distance(path->begin(), path->end()) + 1);
        waypoints->append(start_point);
        waypoints->append(*path);
        generatedMission->setActions_wp();

        QStandardItemModel * genmodel = createMissionModel(generatedMission);
        //setTableModel(ui->generatedMission, genmodel);
        ui->generatedMission->setTableModel(genmodel);

        // Test
        QStandardItemModel * intmodel = createMissionModel(interopMission);
        ui->interopMission->setTableModel(intmodel);
    }
}

void MissionWidget::moveWaypoint(int wpNum, int key) {
    QVector3D wp = interopMission->mission_waypoints.waypoints->at(wpNum);
    switch (key) {
        case Qt::Key_Up:
            wp.setX(wp.x()+0.0001);
        break;
        case Qt::Key_Down:
            wp.setX(wp.x()-0.0001);
        break;
        case Qt::Key_Left:
            wp.setY(wp.y()-0.0001);
        break;
        case Qt::Key_Right:
            wp.setY(wp.y()+0.0001);
        break;
    }
    interopMission->mission_waypoints.waypoints->replace(wpNum, wp);
    emit(moveWaypointSignal(wpNum, wp));
}

void MissionWidget::setTableModel(QTableView * tableView, QStandardItemModel * model) {
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    for (int c = 1; c < tableView->horizontalHeader()->count(); ++c) {
        tableView->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::ResizeToContents);
    }
}

void MissionWidget::writeButtonClicked() {
    if (hasMission()) {
        if (ui->tabWidget->currentIndex() == 1 && generatedMission != nullptr)
            emit(writeMissionsSignal(generatedMission->constructWaypoints(), generatedMission->waypointLength()));
        else
            emit(writeMissionsSignal(interopMission->constructWaypoints(), interopMission->waypointLength()));
    }
}
void MissionWidget::readButtonClicked() {
    emit(readMissionsSignal());
}
void MissionWidget::clearButtonClicked() {
    emit(clearMissions());
}

void MissionWidget::readMissions(Waypoint::WP * waypoints, uint16_t size) {
    qInfo() << "!-----------------------!";
    qInfo() << "MissionWidget::readMissions test";
    qInfo() << "Mission waypoints length:" << size;
    QList<QVector2D> * wps = new QList<QVector2D>();
    for (uint16_t i = 0; i < size; i++) {
        wps->append(QVector2D(waypoints[i].x, waypoints[i].y));
        qInfo() << "Waypoint" << waypoints[i].id << "->" << waypoints[i].x << waypoints[i].y << waypoints[i].z;
        qInfo() << "Waypoint action ->" << waypoints[i].command;
    }
    emit(drawWaypoints(wps));
    qInfo() << "!-----------------------!";
}

void MissionWidget::writeMissionsStatus(bool success) {
    if (success) qDebug() << "Write Missions Successful";
    else qDebug() << "Write Missions failed";
}

QStandardItemModel * MissionWidget::createMissionModel(Mission * mission) {
    QList<QVector3D> * waypoints = mission->mission_waypoints.waypoints;
    QStandardItemModel *model = new QStandardItemModel;
    model->setHorizontalHeaderLabels(QList<QString>({"CMD", " ALT ", " CMD# "}));
    for (int i = 0; i < waypoints->size(); i++) {
       // QString coords = QGeoCoordinate(waypoints->at(i).x(), waypoints->at(i).y()).toString(QGeoCoordinate::DegreesWithHemisphere);
        QString act;
        switch (mission->mission_waypoints.actions->at(i)) {
            case 16:
                act = "Waypoint";
            break;
        case 22:
                act = "Takeoff";
        }
        QStandardItem * action = new QStandardItem(act);
        QStandardItem * alt = new QStandardItem(QString("%0 m.").arg(waypoints->at(i).z()));
        QStandardItem * actionNum = new QStandardItem(QString("%0").arg(mission->mission_waypoints.actions->at(i)));
        QList<QStandardItem*> row({action, alt, actionNum});
        for (int j = 0; j < row.size(); j++) {
            row.at(j)->setTextAlignment(Qt::AlignCenter);
        }
        model->appendRow(row);
    }
    return model;
}

void MissionWidget::getMissions(Interop * i) {
    QJsonArray interopMissions = i->getMissions().array();
    for (int j = 0; j < interopMissions.size(); j++) {
        missions->append(new Mission(interopMissions.at(j).toObject()));
        ui->missionList->addItem("Mission " + QString::number(j+1));
        ui->missionList->setItemData(j, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}


// // *********************************  // //
// // *** Test JSON Files Retrieval ***  // //
// // *********************************  // //
void MissionWidget::testOutputJSON(QJsonObject o, int i) {
    qDebug() << "MissionWidget::testOutput - OUTPUT JSON FILE";
    QFile file(QDir::currentPath() + "/../../GroundStation/GS/res/missionout_" + QString::number(i) + ".json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Couldn't open write file");
        return;
    }
    file.write(QJsonDocument(o).toJson());
}
QJsonObject MissionWidget::testReadJSON_mission(QString n) {
    qDebug() << "MissionWidget::readJSON_mission - INPUT JSON FILE";
    QFile load(":/res/test_mission"+n+".json");
    if (!load.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open mission file");
        QJsonObject null;
        return null;
    }
    QByteArray data = load.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    return doc.object();
}
QJsonDocument MissionWidget::testReadJSON_obstacle() {
    qDebug() << "MissionWidget::readJSON_obstacle - INPUT JSON FILE";
    QFile load(":/res/test_obstacles.json");
    if (!load.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open obstacles file");
        QJsonDocument null;
        return null;
    }
    QByteArray data = load.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    return doc;
}

//void MissionWidget::getObstacles(Interop * i) {
//    Obstacles obstacles = interop->getObstacles();
//    obstacles.loadStationaryObjects(mapWidget);

void MissionWidget::updateInteropMission(int index) {
    QStandardItemModel * missionModel= createMissionModel(missions->at(index));
    ui->interopMission->setTableModel(missionModel);
    interopMission = missions->at(index);
}

MissionWidget::~MissionWidget()
{
    delete ui;
}


