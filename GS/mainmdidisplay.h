#ifndef MAINMDIDISPLAY_H
#define MAINMDIDISPLAY_H

#include <QMainWindow>
#include "qttabtest.h"
#include "missionplanningwindow.h"
#include "ui_mainmdidisplay.h"
#include "mapwidget.h"
#include "missionstatuswindow.h"
#include <assert.h>

#include "gscontrolpanel.h"

//FOR NOW...
#include "mapplanning.h"

#include "maprecap.h"

//TODO Getters and setters. C'mon...

namespace Ui {
  class MainMDIDisplay;
}

class MainMDIDisplay : public QMainWindow {
  Q_OBJECT

public:
  explicit MainMDIDisplay(QWidget *parent = 0);
  void addWindow( QWidget * );
  void addWindow( QWidget * , QString );
  ~MainMDIDisplay();

private slots:
  void setupMapPaths();
private:
  Ui::MainMDIDisplay *ui;
  MapWidget *map;
  QWidget * mapExecutionStatusUIWidget;
  QVBoxLayout * MapExecutionStatusVBoxLayout;

  /**
     * @brief MissionStatusWindow holds StatusWidget and TimerWidget.
     */
  MissionStatusWindow msw ;

  /**
     * @brief Network log
     */
  messagebox mb ;

  GSControlPanel gscp ;

};

#endif // MAINMDIDISPLAY_H
