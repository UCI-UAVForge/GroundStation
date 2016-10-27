#ifndef MAINMDIDISPLAY_H
#define MAINMDIDISPLAY_H

#include <QMainWindow>
#include "qttabtest.h"
#include "missionplanningwindow.h"
#include "ui_mainmdidisplay.h"

//FOR NOW...
#include "mapplanning.h"

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

private slots:

    void destroy();

    void beginMapExecution();

private:

    Ui::MainMDIDisplay *ui;

    QtTabTest * qttWidget;

    /* Figure out a way so that we only have one MapPlanning object instead of a pointer to one
        in qttWidget and here. */

    MapPlanning * tempMapPlanningUIWidget;

    QWebView * MapPlanningMapUIWidget;

    MissionPlanningWindow * missionPlanningWindowUIWidget;

    MapExecution * tempMapExecutionUIWidget;

    QWidget * mapExecutionStatusUIWidget;

    QVBoxLayout * MapExecutionStatusVBoxLayout;

};

#endif // MAINMDIDISPLAY_H
