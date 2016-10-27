#ifndef QTTABTEST_H
#define QTTABTEST_H

#include <QMainWindow>
#include "options.h"
#include <QPropertyAnimation>
#include <QShortcut>
#include <QPixmap>
#include <QDebug>
#include <iostream>
#include <QtWebKitWidgets/QWebView>
#include <QUrl>

#include "options.h"
#include "tutorial.h"
#include "mapplanning.h"
#include "mapexecution.h"
#include "missionrecap.h"
#include "maprecap.h"
#include "connectiondialog.h"

namespace Ui {

    class QtTabTest;

}

class QtTabTest : public QMainWindow {

    Q_OBJECT

    friend class MainMDIDisplay;

public:

    explicit QtTabTest(QWidget *parent = 0);

    ~QtTabTest();

    void addNewTab( QWidget * , QString );

    void deleteTabIndex( int );

    MapPlanning * getMapPlanningUIWidget() const;

    void setMapPlanningUIWidget( MapPlanning * );

    MapExecution * getMapExecutionUIWidget() const;

    void setMapExecutionUIWidget( MapExecution * );

private slots:

    void startMapExecution();

    void startMapRecap();

    /*

    void openTutorial();

    void missionPlanningClicked();

    void missionExecutionClicked();

    void missionRecapClicked();

    void on_actionQuit_triggered();

    /**
      * @brief implemented the four menubar options: (Save,Map Planning,Mission Execution, Mission Recap)
      *
      * @author Kevin Phan
      * @date 2016-2-26
      */

    /*

    void on_actionSave_triggered();

    void on_actionMap_Planning_triggered();

    void on_actionMission_Execution_triggered();

    void on_actionMission_Recap_triggered();

    void checkFinishStatus(int status);

    void showMissionPlanning();

    void showMissionExecution();

    void showMissionRecap();

    void showTutorial();

    */

private:

    Ui::QtTabTest *ui;

    MapPlanning * testMAP;

    MapPlanning * MapPlanningUIWidget = NULL;

    MapExecution * MapExecutionUIWidget;

    MapRecap * MapRecapUIWidget;

    QWidget * MapRecapUI_MapTab;

    QWidget * MapRecapUI_TableTab;

    QWidget * MapRecapUI_GraphTab;

    bool isFirstTabEmpty;

    //QPropertyAnimation *animation;

};

#endif // QTTABTEST_H
