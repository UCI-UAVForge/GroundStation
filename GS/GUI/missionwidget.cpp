#include "missionwidget.h"
#include "ui_missionwidget.h"
//#include "qtmaterialraisedbutton.h"
#include <QDebug>

MissionWidget::MissionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionWidget)
{
    ui->setupUi(this);
    loadCount=0;
    style = Style();
    ui->missionList->setEditable(true);
    ui->missionList->lineEdit()->setReadOnly(true);
    ui->missionList->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->setCurrentValue->setRange(0,0);
    connect(ui->generateButton, &QPushButton::clicked, this, &MissionWidget::generateMission);
    connect(ui->writeButton, &QPushButton::clicked, this, &MissionWidget::writeButtonClicked);
    connect(ui->readButton, &QPushButton::clicked, this, &MissionWidget::readButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MissionWidget::clearButtonClicked);
    connect(ui->setCurrentButton, &QPushButton::clicked, this, &MissionWidget::setCurrentButtonClicked);
    connect(ui->missionList, SIGNAL(currentIndexChanged(int)), this, SLOT(updateMission(int)));

    connect(ui->saveButton,&QPushButton::clicked, this, &MissionWidget::saveMission);
    connect(ui->loadButton,&QPushButton::clicked, this, &MissionWidget::loadMission);

    foreach(MissionTable * table, this->findChildren<MissionTable*>()) {
        connect(table, &MissionTable::selectWaypoint, this, &MissionWidget::selectWaypoint);
        connect(table, &MissionTable::moveWaypoint, this, &MissionWidget::moveWaypoint);
        connect(table, &MissionTable::removeWaypoint, this, &MissionWidget::removeWaypoint);
        connect(table, &MissionTable::editMode, this, &MissionWidget::editMode);
    }

    foreach(QPushButton * p, this->findChildren<QPushButton*>()) {
        if (p->objectName() == "clearButton") {
            style.setButtonOff(p);
        } else {
            style.setButtonDefault(p);
        }
    }

    //Hard coded loaded missions
    qInfo() << "LOADING TEST";
    loadJSON_mission("://res/test_mission2.json",loadCount++);
    loadJSON_mission("://res/test_mission.json",loadCount++);


    missions.append(new Mission(testReadJSON_mission(""), testReadJSON_obstacle()));
    ui->missionList->addItem("*TEST MISSION*");
    ui->missionList->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);

    mission = missions[0];
    QStandardItemModel * model = createMissionModel(mission);
    ui->generatedMission->setTableModel(model);
    ui->setCurrentValue->setRange(1, mission->completeMissionLength() - 1);
}

bool MissionWidget::hasMission() {
    return missions.size() > 0;
}

void MissionWidget::updateDraw() {
    emit(clearMap());
    for (QPolygonF obst_poly : mission->get_obstacles()) {
        emit(drawObstacle(obst_poly, QColor("red"), "Obstacle"));
    }
    drawMission(mission);
}

void MissionWidget::updateSetCurrentLen() {
    ui->setCurrentValue->setRange(1, mission->completeMissionLength() - 1);
}

void MissionWidget::generateMission() {
    if (hasMission()) {
        PlanMission pm(mission);
        /* Path Finding */
        QVector3D start_point = mission->generatedPath.waypoints.at(0).coords;
        QList<QVector3D>* path = pm.get_path();

        /* Replace with Coordinate add/remove only */
        mission->generatedPath.waypoints.clear();
        mission->generatedPath.waypoints.reserve(mission->generatedPath.waypoints.size()
                                                + std::distance(path->begin(),
                                                                path->end()) + 1);
        mission->generatedPath.addWaypoint(Waypt(start_point)); // <- we don't want to use this thingy
        foreach(QVector3D coords, *path) {
            mission->generatedPath.addWaypoint(Waypt(coords));
        }

        ui->generatedMission->setTableModel(createMissionModel(mission));
        updateDraw();
        // TODO: Create generatedPath model for mission table.
//        QStandardItemModel * genmodel = createMissionModel(generatedMission);
//        //setTableModel(ui->generatedMission, genmodel);
//        ui->generatedMission->setTableModel(genmodel);

    }
}

void MissionWidget::removeWaypoint(int wpNum) {
    QVector3D wp = mission->generatedPath.waypoints.at(wpNum).coords;
    mission->generatedPath.waypoints.removeAt(wpNum);
    QStandardItemModel * model = createMissionModel(mission);
    ui->generatedMission->setTableModel(model);
    updateDraw();
    emit(removeWaypointSignal(wpNum, wp));
}

void MissionWidget::moveWaypoint(int wpNum, int key) {
    emit(moveWaypointSignal(wpNum, mission->moveWaypoint(wpNum, key)));
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
        emit(writeMissionsSignal(mission->constructWaypoints(),
                                 mission->completeMissionLength()));
    }
}
void MissionWidget::readButtonClicked() {
    emit(readMissionsSignal());
}
void MissionWidget::clearButtonClicked() {
    emit(clearMissions());
}
void MissionWidget::setCurrentButtonClicked() {
    emit(setCurrentMision(ui->setCurrentValue->value()));
}

//void MissionWidget::saveButtonClicked() {
//    emit(saveMission());
//}

//void MissionWidget::loadButtonClicked() {
//    emit(loadMission());
//}

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

QStandardItemModel *MissionWidget::createMissionModel(const Mission *mission) {
    QStandardItemModel *model = new QStandardItemModel;
    QList<Waypt> wp({mission->takeoff});
    wp.append(mission->generatedPath.waypoints);
    wp.append(mission->landing.waypoints);
    model->setHorizontalHeaderLabels(QList<QString>({"CMD#", " ALT ", " 1 ", " 2 ", " 3 ", " 4 "}));
    for (int i = 0; i < wp.length(); i++) {
        QStandardItem * action = new QStandardItem(QString("%0").arg(wp.at(i).action));
        QStandardItem * alt = new QStandardItem(QString("%0").arg(wp.at(i).coords.z()));
        QStandardItem * param1 = new QStandardItem(QString("%0").arg(wp.at(i).param1));
        QStandardItem * param2 = new QStandardItem(QString("%0").arg(wp.at(i).param2));
        QStandardItem * param3 = new QStandardItem(QString("%0").arg(wp.at(i).param3));
        QStandardItem * param4 = new QStandardItem(QString("%0").arg(wp.at(i).param4));
        QList<QStandardItem*> row({action, alt, param1, param2,
                                  param3, param4});
        for (int j = 0; j < row.size(); j++) {
            row.at(j)->setTextAlignment(Qt::AlignCenter);
        }
        model->appendRow(row);
    }
    return model;
}

void MissionWidget::updateMission(int index) {
    QStandardItemModel * model = createMissionModel(missions.at(index));
    ui->generatedMission->setTableModel(model);
    mission = missions.at(index);
    updateDraw();
}

void MissionWidget::getMissions(Interop *i) {
    QJsonArray interopMissions = i->getMissions().array();
    for (int j = 0; j < interopMissions.size(); j++) {
        missions.append(new Mission(interopMissions.at(j).toObject()));
        ui->missionList->addItem("Mission " + QString::number(j+1));
        ui->missionList->setItemData(j, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}

void MissionWidget::saveMission() {
    QString filename = QFileDialog::getSaveFileName(this,
            tr("Load Mission"), QDir::currentPath() + "/../../GroundStation/GS/res",
            tr("Json Files (*.json)"));
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)){
        qWarning("Couldn't open write file");
        return;
    }
    file.write(mission->toJson().toJson());
    file.close();
}

void MissionWidget::loadMission() {
    QString filename = QFileDialog::getOpenFileName(this,
            tr("Load Mission"), QDir::currentPath() + "/../../GroundStation/GS/res",
            tr("Json Files (*.json)"));
    loadJSON_mission(filename,loadCount++);
}

void MissionWidget::loadJSON_mission(QString n, int num) {
    QFile file(n);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open mission file");
        QJsonObject null;
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    missions.append(new Mission(doc.object(), testReadJSON_obstacle()));
    ui->missionList->addItem("Loaded Mission " + QString::number(num));
    ui->missionList->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);
}


// // *********************************  // //
// // *** Test JSON Files Retrieval ***  // //
// // *********************************  // //
void MissionWidget::testOutputJSON(QJsonObject o, int i) {
    QFile file(QDir::currentPath() + "/../../GroundStation/GS/res/missionout_" + QString::number(i) + ".json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Couldn't open write file");
        return;
    }
    file.write(QJsonDocument(o).toJson());
}
QJsonObject MissionWidget::testReadJSON_mission(QString n) {
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

MissionWidget::~MissionWidget() {
    delete ui;
}


