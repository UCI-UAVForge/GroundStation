#ifndef MAINMDIDISPLAY_H
#define MAINMDIDISPLAY_H

#include <QMainWindow>
#include "qttabtest.h"
#include "missionplanningwindow.h"
#include "ui_mainmdidisplay.h"
#include "mapwidget.h"
#include "missionstatuswindow.h"
#include "mission.h"
#include "flightpath.h"
#include <assert.h>

#include "gscontrolpanel.h"

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

private slots:
  void setupMapPaths();
  void changeState(MDIState newState);

private:
  Ui::MainMDIDisplay *ui;

  MDIState myState;
  FlightPath *myLoadedFlightPath;
  Mission *myLoadedMission;

  MapWidget* map;
  TableWidget* table;
  QWidget* mapExecutionStatusUIWidget;
  QVBoxLayout* MapExecutionStatusVBoxLayout;

  /**
     * @brief MissionStatusWindow holds StatusWidget and TimerWidget.
     */
  MissionStatusWindow msw ;

  /**
     * @brief Network log
     */
  messagebox mb ;

  GSControlPanel gscp ;

  void startMissionPlanning();
  void endMissionPlanning();
  void startMissionExecution();
  void endMissionExecution();
  void startMissionRecap();
  void endMissionRecap();
};



#endif // MAINMDIDISPLAY_H
