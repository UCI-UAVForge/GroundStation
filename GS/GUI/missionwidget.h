#ifndef MISSIONWIDGET_H
#define MISSIONWIDGET_H

#include <QWidget>
#include "interop.h"
#include "mission.h"
#include "interop.h"
#include "obstacles.h"
#include "mapwidget.h"
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

private:
    Ui::MissionWidget *ui;
};

#endif // MISSIONWIDGET_H
