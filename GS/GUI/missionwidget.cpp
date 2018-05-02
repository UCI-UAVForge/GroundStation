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
    connect(ui->dropButton, &QPushButton::clicked, this, &MissionWidget::dropIt);
    connect(ui->missionList, SIGNAL(currentIndexChanged(int)), this, SLOT(updateMission(int)));

    connect(ui->saveButton,&QPushButton::clicked, this, &MissionWidget::saveMission);
    connect(ui->loadButton,&QPushButton::clicked, this, &MissionWidget::loadMission);

    foreach(MissionTable * table, this->findChildren<MissionTable*>()) {
        connect(table, &MissionTable::selectWaypoint, this, &MissionWidget::selectWaypoint);
        connect(table, &MissionTable::moveWaypoint, this, &MissionWidget::moveWaypoint);
        connect(table, &MissionTable::removeWaypoint, this, &MissionWidget::removeWaypoint);
        connect(table, &MissionTable::addWaypoint, this, &MissionWidget::addWaypoint);
        connect(table, &MissionTable::editMode, this, &MissionWidget::editMode);
        connect(table, &MissionTable::changeParams, this, &MissionWidget::changeParams);
    }

    foreach(QPushButton * p, this->findChildren<QPushButton*>()) {
        if (p->objectName() == "clearButton") {
            style.setButtonOff(p);
        } else {
            style.setButtonDefault(p);
        }
    }
    style.setButtonOff(ui->dropButton);
    dropArmed = true;

    //Hard coded loaded missions
    qInfo() << "LOADING TEST";
    loadInteropMission("://res/test_mission2.json",":/res/test_obstacles.json",loadCount++);
    loadInteropMission("://res/test_mission.json",":/res/test_obstacles.json",loadCount++);

    mission = missions[0];
    QStandardItemModel * model = createMissionModel(mission);
    ui->generatedMission->setTableModel(model);
    ui->setCurrentValue->setRange(1, mission->generatedPath.waypoints.length());
    //updateDraw();
}

void MissionWidget::dropIt() {
    if (dropArmed) {
        emit(dropSignal(1700));
        style.setButtonOn(ui->dropButton);
        dropArmed = false;
    }
    else if (!dropArmed) {
        emit(dropSignal(1100));
        style.setButtonOff(ui->dropButton);
        dropArmed = true;
    }
}

void MissionWidget::changeParams(QStandardItem * item) {
    Waypt wp = mission->generatedPath.waypoints.at(item->row());
    switch(item->column()) {
       case 0:
          wp.action = item->data(Qt::DisplayRole).toInt();
       break;
       case 1:
          wp.coords.setZ(item->data(Qt::DisplayRole).toFloat());
       break;
       case 2:
          wp.param1 = item->data(Qt::DisplayRole).toFloat();
       break;
       case 3:
           wp.param2 = item->data(Qt::DisplayRole).toFloat();
       break;
       case 4:
            wp.param3 = item->data(Qt::DisplayRole).toFloat();
       break;
       case 5:
            wp.param4 = item->data(Qt::DisplayRole).toFloat();
       break;
       case 6:
            wp.speed = item->data(Qt::DisplayRole).toFloat();
            wp.changeSpeed = true;
       break;
    }
    mission->generatedPath.waypoints.replace(item->row(), wp);
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
    ui->setCurrentValue->setRange(1, mission->generatedPath.waypoints.length());
}

void MissionWidget::generateMission() {
    if (hasMission()) {
        PlanMission pm(mission);
        /* Path Finding */
        QVector3D start_point = mission->interopPath.waypoints.at(0).coords;
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
        mission->generatedPath.waypoints.append(mission->landing.waypoints);
        mission->generatedPath.waypoints.prepend(mission->takeoff);
        updateDraw();
        ui->generatedMission->setTableModel(createMissionModel(mission));
    }
}

void MissionWidget::removeWaypoint(int wpNum) {
    if (wpNum == 0) return;
    mission->generatedPath.waypoints.removeAt(wpNum);
    QStandardItemModel * model = createMissionModel(mission);
    ui->generatedMission->setTableModel(model);
    updateDraw();
}

void MissionWidget::addWaypoint(int wpNum) {
    if (wpNum == mission->generatedPath.waypoints.length()-1) return;
    QVector3D curr_wp = mission->generatedPath.waypoints.at(wpNum).coords;
    QVector3D next_wp = mission->generatedPath.waypoints.at(wpNum+1).coords;
    Waypt wp(findMidPoint(curr_wp, next_wp));
    mission->generatedPath.waypoints.insert(wpNum+1, wp);
    ui->generatedMission->setTableModel(createMissionModel(mission));
    updateDraw();
    ui->generatedMission->selectRow(wpNum+1);

}

QVector2D MissionWidget::findMidPoint(QVector3D a, QVector3D b) {
    float lat_a = qDegreesToRadians(a.x());
    float lat_b = qDegreesToRadians(b.x());
    float lon_a = qDegreesToRadians(a.y());
    float lon_b = qDegreesToRadians(b.y());
    float bx = cos(lat_b) * cos(lon_b - lon_a);
    float by = cos(lat_b) * sin(lon_b - lon_a);
    float latMid = atan2(sin(lat_a) + sin(lat_b),
                         sqrt((cos(lat_a)+bx)*
                              (cos(lat_a)+bx) + by*by));
    float lonMid = lon_a + atan2(by, cos(lat_a) + bx);
    return QVector2D(qRadiansToDegrees(latMid),
                     qRadiansToDegrees(lonMid));
}

void MissionWidget::moveWaypoint(int wpNum, QKeyEvent * k) {
    emit(moveWaypointSignal(wpNum, mission->moveWaypoint(wpNum, k)));
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
        emit(writeMissionsSignal(mission->constructWaypoints()));
        updateSetCurrentLen();
    }
}
void MissionWidget::readButtonClicked() {
    emit(readMissionsSignal());
}
void MissionWidget::clearButtonClicked() {
    emit(clearMissions());
}
void MissionWidget::setCurrentButtonClicked() {
    emit(setCurrentMision(mission->generatedPath.getSeq(ui->setCurrentValue->value())));
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
    QList<Waypt> wp = mission->generatedPath.waypoints;
    model->setHorizontalHeaderLabels(QList<QString>({"CMD#", " ALT ", " 1 ", " 2 ", " 3 ", " 4 ", " SPD "}));
    for (int i = 0; i < wp.length(); i++) {
        QStandardItem * action = new QStandardItem(QString("%0").arg(wp.at(i).action));
        QStandardItem * alt = new QStandardItem(QString("%0").arg(wp.at(i).coords.z()));
        QStandardItem * param1 = new QStandardItem(QString("%0").arg(wp.at(i).param1));
        QStandardItem * param2 = new QStandardItem(QString("%0").arg(wp.at(i).param2));
        QStandardItem * param3 = new QStandardItem(QString("%0").arg(wp.at(i).param3));
        QStandardItem * param4 = new QStandardItem(QString("%0").arg(wp.at(i).param4));
        QStandardItem * spd = wp.at(i).changeSpeed ? new QStandardItem(QString("%0").arg(wp.at(i).speed)) :
                                                         new QStandardItem(QString("0"));
        QList<QStandardItem*> row({action, alt, param1, param2,
                                  param3, param4, spd});
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
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open mission file");
        QJsonObject null;
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    Mission* temp = new Mission(false);
    temp->loadJson(doc.object());

    missions.append(temp);
    ui->missionList->addItem("Loaded Mission " + QString::number(loadCount++));
    ui->missionList->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);
}

void MissionWidget::loadInteropMission(QString m, QString o, int num) {
    QFile file(m);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open mission file");
        QJsonObject null;
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));

    QFile file2(o);
    if (!file2.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open obstacles file");
        QJsonDocument null;
        return;
    }
    data = file2.readAll();
    file.close();
    QJsonDocument doc2(QJsonDocument::fromJson(data));

    missions.append(new Mission(doc.object(), doc2));
    ui->missionList->addItem("Loaded Mission " + QString::number(num));
    ui->missionList->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);
}

MissionWidget::~MissionWidget() {
    delete ui;
}


