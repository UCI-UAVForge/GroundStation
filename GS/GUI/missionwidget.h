#ifndef MISSIONWIDGET_H
#define MISSIONWIDGET_H

#include <QFileDialog>
#include <QWidget>
#include "interop.h"
#include "mission.h"
#include "interop.h"
#include "obstacles.h"
#include "mapwidget.h"
#include "waypoint.h"
#include <QLineEdit>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QGeoCoordinate>
#include <QTableView>
#include "point.hpp"
#include "plan_mission.hpp"
#include <QFile>
#include "style.h"

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
    void setCurrentButtonClicked();
//    void saveButtonClicked();
//    void loadButtonClicked();
    void saveMission();
    void loadMission();
    bool hasMission();
    void generateMission();
    void getMissions(Interop * i);
    QStandardItemModel *createMissionModel(const Mission *mission);
    void setTableModel(QTableView * tableView, QStandardItemModel * model);


    QVector<Mission*> missions;
    Mission *mission;
    QStandardItemModel * model;
    Obstacles obstacles;
    MapWidget * mapWidget;

    Style style;

    bool test_mission = true;

    ~MissionWidget();

signals:
    void drawMission(Mission *selectedMission);
    void drawWaypoints(QList<QVector2D> * wps);
    void drawObstacle(QPolygonF poly, QColor color, QString label);
    void clearMissions();
    void setCurrentMision(uint16_t i);
    void readMissionsSignal();
    void writeMissionsSignal(QVector<Waypoint::WP> waypoints, uint16_t size);
    void clearMap();

    void selectWaypoint(int wpNum);
    void editMode(bool editing);
    void moveWaypointSignal(int wpNum, QVector3D newCoord);
    void removeWaypointSignal(int wpNum, QVector3D coord);



public slots:
    void readMissions(Waypoint::WP * waypoints, uint16_t size);
    void writeMissionsStatus(bool success);
    void updateMission(int index);
    void updateDraw();
    void updateSetCurrentLen();
    void moveWaypoint(int wpNum, QKeyEvent * k);
    void removeWaypoint(int wpNum);
    void changeParams(QStandardItem * item);
    void addWaypoint(int wpNum);

private:
    QVector2D findMidPoint(QVector3D a, QVector3D b);
    void loadInteropMission(QString m, QString o,int num);
    int loadCount;

    Ui::MissionWidget *ui;

    // TEST TODO: Delete
    Waypoint::WP* testWaypoints();
};

#endif // MISSIONWIDGET_H
