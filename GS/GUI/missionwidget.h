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
    void loadMission();
    void getMissions(Interop * i);
    QStandardItemModel * createMissionModel(Mission * mission);

    QVector<Mission*> * missions;
    QStandardItemModel * model;
    Obstacles obstacles;
    MapWidget * mapWidget;

    ~MissionWidget();

signals:
    void drawMission(Mission * selectedMission);
    void clearMissions();
    void readMissionsSignal();
    void writeMissionsSignal(Waypoint::WP * waypoints, uint16_t size);

public slots:
    void readMissions(Waypoint::WP * waypoints, uint16_t size);
    void writeMissionsStatus(bool success);

private:
    Waypoint::WP* constructWaypoints(const Mission& mission);

    Ui::MissionWidget *ui;
};

#endif // MISSIONWIDGET_H
