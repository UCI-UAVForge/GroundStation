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
    connect(ui->missionList, SIGNAL(currentIndexChanged(int)), this, SLOT(updateInteropMission(int)));

    if (test_mission) {
        missions->append(new Mission(testReadJSON_mission()));
        ui->missionList->addItem("*TEST MISSION*");
        ui->missionList->setItemData(0, Qt::AlignCenter, Qt::TextAlignmentRole);

        QStandardItemModel * test_mission_model = createMissionModel(missions->at(ui->missionList->currentIndex()));
        setTableModel(ui->interopMission, test_mission_model);
    }

}

bool MissionWidget::hasMission() {
    return missions->size() > 0;
}

void MissionWidget::loadMission() {
    if (hasMission()) {
        PlanMission pm;

        Mission * selectedMission = missions->at(ui->missionList->currentIndex());

        for (int i = 1; i < selectedMission->mission_waypoints.waypoints->size(); i++) {
            QVector3D point = selectedMission->mission_waypoints.waypoints->at(i);
            qDebug() << "X: " << point.x() << " Y: " << point.y() << " Z: " << point.z();
            pm.add_goal_point(Point::fromGeodetic(point.x(), point.y(), point.z()));
        }
        QVector3D start_point = selectedMission->mission_waypoints.waypoints->at(0);
        qDebug() << "Start X: " << start_point.x() << " Y: " << start_point.y() << " Z: " << start_point.z();

        // Currently not working - path finding returns 0
        pm.set_obstacles(Obstacles(testReadJSON_obstacle()));
//        selectedMission->mission_waypoints.waypoints = pm.get_path(Point::fromGeodetic(start_point.x(), start_point.y(), start_point.z()),
//                                                                   selectedMission->fly_zones);

        selectedMission->setActions_std();
        // TODO Delete waypoints length print below
        qDebug() << "Waypoints Length missionWidget::loadMission" << selectedMission->waypointLength() << "//" <<
                    missions->at(ui->missionList->currentIndex())->waypointLength();
        emit(drawMission(selectedMission));
        for (QPolygonF obst_poly : pm.get_obstacles()) {
            emit(drawObstacle(obst_poly, QColor("red")));
        }
        QStandardItemModel * genmodel = createMissionModel(selectedMission);
        setTableModel(ui->generatedMission, genmodel);
        currentMission = selectedMission;
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
    emit(writeMissionsSignal(currentMission->constructWaypoints(), currentMission->waypointLength()));
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
QJsonObject MissionWidget::testReadJSON_mission() {
    qDebug() << "MissionWidget::readJSON_mission - INPUT JSON FILE";
    QFile load(":/res/test_mission.json");
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
    setTableModel(ui->interopMission, missionModel);
}

MissionWidget::~MissionWidget()
{
    delete ui;
}
