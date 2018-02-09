#include "missionwidget.h"
#include "ui_missionwidget.h"
//#include "qtmaterialraisedbutton.h"
#include <QDebug>
#include <QFile> // Testing purposes
#include "point.hpp"
#include "plan_mission.hpp"
MissionWidget::MissionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionWidget)
{
    ui->setupUi(this);
    missions = new QVector<Mission*>();
    ui->missionList->setEditable(true);
    ui->missionList->lineEdit()->setReadOnly(true);
    ui->missionList->lineEdit()->setAlignment(Qt::AlignCenter);
    connect(ui->loadButton, &QPushButton::clicked, this, &MissionWidget::loadMission);
    connect(ui->writeButton, &QPushButton::clicked, this, &MissionWidget::writeButtonClicked);
    connect(ui->readButton, &QPushButton::clicked, this, &MissionWidget::readButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MissionWidget::clearButtonClicked);
}

bool MissionWidget::hasMission() {
    return missions->size() > 0;
}

void MissionWidget::loadMission() {
    /* TEST MISSION LOAD */
    if (test_mission) {
        qDebug() << "test_mission == true: LOADING TEST MISSION";
        PlanMission pm;
        currentMission = new Mission(testReadJSON());
        for (int i = 1; i < currentMission->mission_waypoints.waypoints->size(); i++) {
            QVector3D point = currentMission->mission_waypoints.waypoints->at(i);
            qDebug() << "X: " << point.x() << " Y: " << point.y() << " Z: " << point.z();
            pm.add_goal_point(Point::fromGeodetic(point.x(), point.y(), point.z()));
        }
        QVector3D start_point = currentMission->mission_waypoints.waypoints->at(0);
        qDebug() << "Start X: " << start_point.x() << " Y: " << start_point.y() << " Z: " << start_point.z();
        QString sb = "{"
                     "    \"moving_obstacles\": ["
                     "        {"
                     "            \"altitude_msl\": 189.56748784643966,"
                     "            \"latitude\": 34.141826869853645,"
                     "            \"longitude\": -76.43199876559223,"
                     "            \"sphere_radius\": 150.0"
                     "        },"
                     "        {"
                     "            \"altitude_msl\": 250.0,"
                     "            \"latitude\": 34.14923628783763,"
                     "            \"longitude\": -76.43238529543882,"
                     "            \"sphere_radius\": 150.0"
                     "        }"
                     "    ],"
                     "    \"stationary_obstacles\": ["
                     "        {"
                     "            \"cylinder_height\": 750.0,"
                     "            \"cylinder_radius\": 10000.0,"
                     "            \"latitude\": 38.141826869853645,"
                     "            \"longitude\": -76.43199876559223"
                     "        },"
                     "        {"
                     "            \"cylinder_height\": 400.0,"
                     "            \"cylinder_radius\": 10000.0,"
                     "            \"latitude\": 38.149156,"
                     "            \"longitude\": -76.430622"
                     "        }"
                     "    ]"
                     "}";
//        pm.set_obstacles(QJsonDocument::fromJson(sb.toUtf8()));
//        currentMission->mission_waypoints.waypoints = pm.get_path(Point::fromGeodetic(start_point.x(), start_point.y(), start_point.z()),
//                                                                  currentMission->fly_zones);
        currentMission->setActions_std(); // Standard mission to hit all waypoints and land at last waypoint.
        emit(drawMission(currentMission));
        // Model
        QStandardItemModel * genmodel = createMissionModel(currentMission);
        setTableModel(ui->generatedMission, genmodel);
    }

    /* Load interop mission */
    if (hasMission() && !test_mission) {
        PlanMission pm;
        Mission * selectedMission = missions->at(ui->missionList->currentIndex());
        currentMission = selectedMission;
        emit (drawMission(selectedMission));
        QStandardItemModel * interopModel = createMissionModel(selectedMission);
        setTableModel(ui->interopMission, interopModel);
        for (int i = 1; i < selectedMission->mission_waypoints.waypoints->size(); i++) {
            QVector3D point = selectedMission->mission_waypoints.waypoints->at(i);
            pm.add_goal_point(Point::fromGeodetic(point.x(), point.y(), point.z()));
        }
        QVector3D start_point = selectedMission->mission_waypoints.waypoints->at(0);
        qDebug() << "Start X: " << start_point.x() << " Y: " << start_point.y() << " Z: " << start_point.z();
        QString sb = "{"
                     "    \"moving_obstacles\": ["
                     "        {"
                     "            \"altitude_msl\": 189.56748784643966,"
                     "            \"latitude\": 34.141826869853645,"
                     "            \"longitude\": -76.43199876559223,"
                     "            \"sphere_radius\": 150.0"
                     "        },"
                     "        {"
                     "            \"altitude_msl\": 250.0,"
                     "            \"latitude\": 34.14923628783763,"
                     "            \"longitude\": -76.43238529543882,"
                     "            \"sphere_radius\": 150.0"
                     "        }"
                     "    ],"
                     "    \"stationary_obstacles\": ["
                     "        {"
                     "            \"cylinder_height\": 750.0,"
                     "            \"cylinder_radius\": 10000.0,"
                     "            \"latitude\": 33.6511,"
                     "            \"longitude\": -117.852"
                     "        },"
                     "        {"
                     "            \"cylinder_height\": 400.0,"
                     "            \"cylinder_radius\": 10000.0,"
                     "            \"latitude\": 38.149156,"
                     "            \"longitude\": -76.430622"
                     "        }"
                     "    ]"
                     "}";
        pm.set_obstacles(QJsonDocument::fromJson(sb.toUtf8()));
        selectedMission->mission_waypoints.waypoints = pm.get_path(Point::fromGeodetic(start_point.x(), start_point.y(), start_point.z()),
                                                                   selectedMission->fly_zones);
        for (int i = 1; i < selectedMission->mission_waypoints.waypoints->size(); i++) {
            if (selectedMission->mission_waypoints.actions->size() != selectedMission->mission_waypoints.waypoints->size()) {
                selectedMission->mission_waypoints.actions->append(0);
            }
        }
        emit (drawMission(selectedMission));
        QStandardItemModel * genmodel = createMissionModel(selectedMission);
        setTableModel(ui->generatedMission, genmodel);
    }
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
    // Writes only the first mission in the mission vector
//    if (missions->empty()) qDebug() << "MissionWidget::writeButtonClicked -> empty mission vector";
//    else
//        emit(writeMissionsSignal(constructWaypoints(*missions->at(0)),
//                              missions->at(0)->mission_waypoints.waypoints->length()));
//    qDebug() << currentMission->mission_waypoints.waypoints->length();
    emit(writeMissionsSignal(currentMission->constructWaypoints(), currentMission->waypointLength()));
//    emit(writeMissionsSignal(testWaypoints(), currentMission->mission_waypoints.waypoints->length()+1));
}
void MissionWidget::readButtonClicked() {
    emit(readMissionsSignal());
}
void MissionWidget::clearButtonClicked() {
    emit(clearMissions());
}

void MissionWidget::readMissions(Waypoint::WP * waypoints, uint16_t size) {
    qDebug() << "!-----------------------!";
    qDebug() << "MissionWidget::readMissions test";
    qDebug() << "Mission waypoints length:" << size;
    for (uint16_t i = 0; i < size; i++) {
        qDebug() << "Waypoint" << waypoints[i].id << "->" << waypoints[i].x << waypoints[i].y << waypoints[i].z;
    }
    qDebug() << "!-----------------------!";
}

void MissionWidget::writeMissionsStatus(bool success) {
    if (success) qDebug() << "Write Missions Successful";
    else qDebug() << "Write Missions failed";
}

QStandardItemModel * MissionWidget::createMissionModel(Mission * mission) {
    QList<QVector3D> * waypoints = mission->mission_waypoints.waypoints;
    QStandardItemModel *model = new QStandardItemModel;
    model->setHorizontalHeaderLabels(QList<QString>({"LAT,LON", " ALT ", " CMD "}));
    for (int i = 0; i < waypoints->size(); i++) {
        QString coords = QGeoCoordinate(waypoints->at(i).x(), waypoints->at(i).y()).toString(QGeoCoordinate::DegreesWithHemisphere);
        QStandardItem * latlng = new QStandardItem(coords);
        QStandardItem * alt = new QStandardItem(QString("%0 m.").arg(waypoints->at(i).z()));
        QStandardItem * action = new QStandardItem(QString("%0").arg(mission->mission_waypoints.actions->at(i)));
        QList<QStandardItem*> row({latlng, alt, action});
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
        // testOutputJSON(interopMissions.at(j).toObject(), j);
        missions->append(new Mission(interopMissions.at(j).toObject()));
        ui->missionList->addItem("Mission " + QString::number(j+1));
        ui->missionList->setItemData(j, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}

void MissionWidget::testOutputJSON(QJsonObject o, int i) {
    qDebug() << "MissionWidget::testOutput - OUTPUT JSON FILE";
    QFile file(QDir::currentPath() + "/../../GroundStation/GS/res/missionout_" + QString::number(i) + ".json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Couldn't open write file");
        return;
    }
    file.write(QJsonDocument(o).toJson());
}

QJsonObject MissionWidget::testReadJSON() {
    qDebug() << "MissionWidget::readJSON - INPUT JSON FILE";
    QFile load(QDir::currentPath() + "/../../GroundStation/GS/res/test_mission.json");

    if (!load.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file");
        QJsonObject null;
        return null;
    }
    QByteArray data = load.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    return doc.object();
}

//void MissionWidget::getObstacles(Interop * i) {
//    Obstacles obstacles = interop->getObstacles();
//    obstacles.loadStationaryObjects(mapWidget);

MissionWidget::~MissionWidget()
{
    delete ui;
}


// TEST WAYPOINTS TODO: delete
Waypoint::WP* MissionWidget::testWaypoints() {
    // TEST WAYPOINTS TODO: delete
        int num_waypoints = 6;
        Waypoint::WP* waypoints = new Waypoint::WP[currentMission->mission_waypoints.waypoints->length()+1];
        // Home
        for (int i = 1; i < currentMission->mission_waypoints.waypoints->length()+1 ; i++) {
            waypoints[i].autocontinue = 1;
            waypoints[i].command = currentMission->mission_waypoints.actions->at(i-1);
            waypoints[i].current = 0;
            waypoints[i].param1 = 0;
            waypoints[i].param2 = 0;
            waypoints[i].param3 = 0;
            waypoints[i].param4 = 0;
            waypoints[i].x = currentMission->mission_waypoints.waypoints->at(i-1).x();
            waypoints[i].y = currentMission->mission_waypoints.waypoints->at(i-1).y();
            waypoints[i].z = currentMission->mission_waypoints.waypoints->at(i-1).z();
            waypoints[i].id = i;
            waypoints[i].frame = 3;
        }
        waypoints[0].autocontinue = 1;
        waypoints[0].command = 16;
        waypoints[0].current = 0;
        waypoints[0].param1 = 0;
        waypoints[0].param2 = 0;
        waypoints[0].param3 = 0;
        waypoints[0].param4 = 0;
        waypoints[0].x = -35.36326;
        waypoints[0].y = 149.16524;
        waypoints[0].z = 584.1;
        waypoints[0].id = 0;
        waypoints[0].frame = 0;
    return waypoints;
}
