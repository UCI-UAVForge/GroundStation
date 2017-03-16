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
#include "qttabtest.h"

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

  void receivePacket(Protocol::Packet* packet);
  void showControlPanel();
private:
  Ui::MainMDIDisplay *ui;

  MDIState myState;

  //Jordan's vars for state transition
  FlightPath *myLoadedFlightPath;
  Mission *myLoadedMission;

  GsServer* myServer;
  //end Jordan's vars

  MapWidget* map;
  TableWidget* table;
  QWidget* mapExecutionStatusUIWidget;
  QVBoxLayout* MapExecutionStatusVBoxLayout;

  GSControlPanel* gscp ;

  //TableWidget tw ;

  //Temporary tabbed display widget
  QtTabTest* qtt ;

  void startMissionPlanning();
  void endMissionPlanning();
  void startMissionExecution();
  void endMissionExecution();
  void startMissionRecap();
  void endMissionRecap();
  void plotPosition(double lat, double lng);
  void saveFlightPath();
  void loadFlightPath();

  GraphWidget * graph;

  QString folder;
  const char kPathSeparator =
      #ifdef _WIN32
                              '\\';
      #else
                              '/';
      #endif
};

#endif // MAINMDIDISPLAY_H
