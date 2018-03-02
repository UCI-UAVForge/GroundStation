#ifndef MISSIONWIDGET_H
#define MISSIONWIDGET_H

#include <QWidget>
#include "interop.h"
#include "mission.h"
#include "interop.h"
#include "obstacles.h"
#include "mapwidget.h"
#include "wyp.h"
#include <QLineEdit>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QGeoCoordinate>
#include <QTableView>
#include "point.hpp"
#include "plan_mission.hpp"
#include <QFile>

namespace Ui {
class MissionWidget;
}

class MissionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MissionWidget(QWidget *parent = 0);

    void writeButtonClicked();
    void readButtonClicked();
    void clearButtonClicked();
    bool hasMission();
    void drawCurrentMission();
    void loadMission();
    void getMissions(Interop * i);
    QStandardItemModel * createMissionModel(Mission * mission);
    void setTableModel(QTableView * tableView, QStandardItemModel * model);

    QVector<Mission*> * missions;
    Mission * generatedMission = nullptr;
    Mission * interopMission = nullptr;
    QStandardItemModel * model;
    Obstacles obstacles;
    MapWidget * mapWidget;

    bool test_mission = true;

    ~MissionWidget();

signals:
    void drawMission(Mission * selectedMission);
    void drawObstacle(QPolygonF poly, QColor color, QString label);
    void clearMissions();
    void readMissionsSignal();
    void writeMissionsSignal(QVector<Waypoint::WP> waypoints, uint16_t size);
    void clearMap();

public slots:
    void readMissions(Waypoint::WP * waypoints, uint16_t size);
    void writeMissionsStatus(bool success);
    void updateInteropMission(int index);

private:
    void testOutputJSON(QJsonObject o, int i);
    QJsonObject testReadJSON_mission(QString n);
    QJsonDocument testReadJSON_obstacle();

    Ui::MissionWidget *ui;

    // TEST TODO: Delete
    Waypoint::WP* testWaypoints();
};

#endif // MISSIONWIDGET_H
