#ifndef MAINMDIDISPLAY_H
#define MAINMDIDISPLAY_H

#define MINIMUM_NUMBER_OF_POINTS 1

#include <QMainWindow>
#include "qttabtest.h"
#include "missionplanningwindow.h"
#include "ui_mainmdidisplay.h"

#include <assert.h>

//FOR NOW...
#include "mapplanning.h"

#include "maprecap.h"

//TODO Getters and setters. C'mon...

#define BLANK_QSTRING QString( "" )

#define SAVE_SUCCESSFUL true

enum Menu { Startup , Planning , Execution , Recap } ;

namespace Ui {

    class MainMDIDisplay;

}

class MainMDIDisplay : public QMainWindow {

    Q_OBJECT

public:

    explicit MainMDIDisplay(QWidget *parent = 0);

    QMdiSubWindow * addWindow( QWidget * );

    void addWindow( QWidget * , QString );

    ~MainMDIDisplay();

    QtTabTest * getQttWidget() const;

    void setQttWidget( QtTabTest * );

    void clearMapExecution();

    void clearMapRecap();

    //TODO Make this a switch to execution function
    void changePlanningToExecutionWindow();

    void switchToPlanningWindow();

    void switchToRecapWindow();

private slots:

    void destroy();

    void beginMapExecution();

    void clickedFinishButton_MainDisplay();

    void clickedCancelButton_MainDisplay();

    void clickedBackToPlanningButton_MainDisplay();

    void clickedBackButton_MainDisplay();

    void clickedLoadMissionButton_MainDisplay() ;

    void clickedSaveMissionButton_MainDisplay() ;

    void onMapUpdated() ;

private:

    Ui::MainMDIDisplay *ui;

    Menu currentMenu ;

    QtTabTest * qttWidget;

    /* Figure out a way so that we only have one MapPlanning object instead of a pointer to one
        in qttWidget and here. */

    MapPlanning * tempMapPlanningUIWidget;

    //QWebView * MapPlanningMapUIWidget;

    MissionPlanningWindow * missionPlanningWindowUIWidget;

    MapExecution * tempMapExecutionUIWidget;

    MapRecap * tempMapRecapUIWidget ;

    QWidget * mapExecutionStatusUIWidget;

    QVBoxLayout * MapExecutionStatusVBoxLayout;

    /* Buttons */

    //TODO Put all the buttons/other UI elements for the GUI here to organize everything in one spot

    QPushButton * backToPlanningButton , * saveMissionButton , * loadMissionButton ;

    QLineEdit * saveMissionByNameLineEdit ;

    QLabel * saveMissionByNameLabel ;

    /* Tabs */

    QWidget * MapRecapUI_TableTab , * MapRecapUI_GraphTab ;

    QMdiSubWindow * MapSubWindow , * MissionControlSubWindow ;

    FlightPath * missionPlanningFlightPath ;

signals:

    void switchedToPlanning() ;

    void switchedToRecap() ;

    void switchedToExecution() ;

};

#endif // MAINMDIDISPLAY_H
