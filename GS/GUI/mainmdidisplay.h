#ifndef MAINMDIDISPLAY_H
#define MAINMDIDISPLAY_H

#include <QMainWindow>
//#include "qttabtest.h"
#include "gsserver.h"
#include "missionplanningwindow.h"
#include "ui_mainmdidisplay.h"
#include "mapwidget.h"
#include "missionstatuswindow.h"
#include "mission.h"
#include "flightpath.h"
#include <assert.h>
#include "graphwidget.h"
#include "tablewidget.h"
#include "dataobjects.h"
#include "gscontrolpanel.h"

#define EMPTY_TELEMETRY_PACKET NULL

namespace Ui {
  class MainMDIDisplay;
}

enum MDIState{
    NONE,
    PLANNING,
    EXECUTION,
    RECAP
};

class MainMDIDisplay : public QMainWindow {
  Q_OBJECT

public:
  explicit MainMDIDisplay(QWidget *parent = 0);
  void addWindow( QWidget * );
  void addWindow( QWidget * , QString );
  ~MainMDIDisplay();
  void removeWindow(QWidget* targetWidget);

public slots:
  void onWindowClose();

private slots:
  void setupMapPaths();
  void changeState(MDIState newState);

  void startMissionPlanningSlot();
  void startMissionExecutionSlot();
  void startMissionRecapSlot();
  void rtnToMainMenu();

  //void receivePacket(Protocol::Packet* packet);
  void receiveTelemetryData(TelemetryData data);
  void showControlPanel();


private:
  Ui::MainMDIDisplay *ui;

  MDIState myState;

  //Jordan's vars for state transition
  FlightPath myFlightPath;
  Mission myMission;

  GsServer* myServer;
  //end Jordan's vars

  //MapWidget* map;
  MapWidget myMap;

  //TableWidget* table;

  TableWidget telemTable;
  TableWidget waypointTable;

  QWidget* mapExecutionStatusUIWidget;
  QVBoxLayout* MapExecutionStatusVBoxLayout;
  GSControlPanel* gscp;


  //GraphWidget * graph;

  GraphWidget myGraph;

  void startMissionPlanning();
  void endMissionPlanning();
  void startMissionExecution();
  void endMissionExecution();
  void startMissionRecap();
  void endMissionRecap();
  void plotPosition(double lat, double lng);

  void saveFlightPath();
  void loadFlightPath();
  void saveMission();
  void loadMission();
};

#endif // MAINMDIDISPLAY_H
