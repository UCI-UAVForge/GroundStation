#ifndef MAINMDIDISPLAY_H
#define MAINMDIDISPLAY_H

#include <QMainWindow>
#include "qttabtest.h"
#include "missionplanningwindow.h"
#include "ui_mainmdidisplay.h"

#include <assert.h>

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

    ~MainMDIDisplay();

    QtTabTest * getQttWidget() const;

    void setQttWidget( QtTabTest * );

    void clearMapExecution();

    //TODO Make this a switch to execution function
    void changePlanningToExecutionWindow();

    void switchToPlanningWindow();

    void switchToRecapWindow();

private slots:

    void destroy();

    void beginMapExecution();

    void clickedFinishButton_MainDisplay();

    void clickedCancelButton_MainDisplay();

    //void clickedBackButton_MainDisplay();

private:

    Ui::MainMDIDisplay *ui;

    QtTabTest * qttWidget;

    /* Figure out a way so that we only have one MapPlanning object instead of a pointer to one
        in qttWidget and here. */

    MapPlanning * tempMapPlanningUIWidget;

    QWebView * MapPlanningMapUIWidget;

    MissionPlanningWindow * missionPlanningWindowUIWidget;

    MapExecution * tempMapExecutionUIWidget;

    MapRecap * tempMapRecapUIWidget ;

    QWidget * mapExecutionStatusUIWidget;

    QVBoxLayout * MapExecutionStatusVBoxLayout;

};

#endif // MAINMDIDISPLAY_H
