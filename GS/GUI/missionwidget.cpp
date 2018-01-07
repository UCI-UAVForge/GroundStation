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

MissionWidget::~MissionWidget()
{
    delete ui;
}
