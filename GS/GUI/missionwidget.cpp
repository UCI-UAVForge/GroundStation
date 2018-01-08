#include "missionwidget.h"
#include "ui_missionwidget.h"
#include "qtmaterialraisedbutton.h"
#include <QDebug>
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
    ui->clearButton->setBackgroundColor(QColor(255, 80, 83));
    connect(ui->writeButton, &QPushButton::clicked, this, &MissionWidget::writeButtonClicked);
    connect(ui->readButton, &QPushButton::clicked, this, &MissionWidget::readButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MissionWidget::clearButtonClicked);
}

bool MissionWidget::hasMission() {
    return missions->size() > 0;
}

void MissionWidget::loadMission() {
    if (hasMission()) {
        Mission * selectedMission = missions->at(ui->missionList->currentIndex());
        emit (drawMission(selectedMission));
        model = createMissionModel(selectedMission);
        ui->missionTable->setModel(model);
        ui->missionTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        for (int c = 1; c < ui->missionTable->horizontalHeader()->count(); ++c) {
            ui->missionTable->horizontalHeader()->setSectionResizeMode(
                c, QHeaderView::ResizeToContents);
        }
    }
}

void MissionWidget::writeButtonClicked() {
    // Writes only the first mission in the mission vector
    qDebug() << "MissionWidget::writeButtonClicked" << missions->at(0)->mission_waypoints.waypoints->length();
    if (missions->empty()) qDebug() << "MissionWidget::writeButtonClicked -> empty mission vector";
    else
        emit(writeMissionsSignal(constructWaypoints(*missions->at(0)),
                              missions->at(0)->mission_waypoints.waypoints->length()));
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
        qDebug() << "Waypoint" << i << "->" << waypoints[i].x;
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

//void MissionWidget::getObstacles(Interop * i) {
//    Obstacles obstacles = interop->getObstacles();
//    obstacles.loadStationaryObjects(mapWidget);

Waypoint::WP* MissionWidget::constructWaypoints(const Mission& mission) {
    Waypoint::WP* waypoints = new Waypoint::WP[missions->length()];
    for (uint16_t i = 0; i < mission.mission_waypoints.waypoints->length(); i++) {
        Waypoint::WP wp;
        qDebug() << "MissionWidget::constructWaypoints -> Temporary placeholder values. MUST change for actual flight";
//        TEMPORARY VALUES. NEEDS TO BE MODIFIED FOR ACTUAL FLIGHT
        wp.id = i;
        wp.command = 16;
        wp.autocontinue = 1;
        wp.current = 0;
        wp.param1 = 0;
        wp.param2 = 10;
        wp.param3 = 0;
        wp.x = mission.mission_waypoints.waypoints->at(i).x();
        wp.y = mission.mission_waypoints.waypoints->at(i).y();
        wp.z = mission.mission_waypoints.waypoints->at(i).z();
        waypoints[i] = wp;
    }
    return waypoints;
}

MissionWidget::~MissionWidget()
{
    delete ui;
}
