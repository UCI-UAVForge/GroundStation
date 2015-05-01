/*  The MainWindow class is the user's starting point in the program. From
 * here, the user can access Mission Planning, Mission Execution, Mission
 * Recap, and the Tutorial.
 *
 * File added sometime prior to April 30 2015.
 */

#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tutorial.h"
#include "mapplanning.h"
#include "mapexecution.h"
#include "missionrecap.h"

/* MainWindow class usage:

    MainWindow window;
    window.showMaximized();

    ========OR=========

    MainWindow *window = new MainWindow();
    window->showMaximized();

No parameters necessary. The window will not appear until one of the show
functions is run such as showMaximized(), showFullScreen(), or show().
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/* Class destructor. */
MainWindow::~MainWindow() {
    delete ui;
}

/* Triggered by the button "Tutorials". This function opens a new window
 displaying user tutorials. Will also close the current MainWindow object.

Function added sometime prior to April 30 2015.*/
void MainWindow::openTutorial() {
    Tutorial *tutorial = new Tutorial();

//    QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
//    std::cout << "New animation" << std::endl;
//    animation->setDuration(10000);
//    animation->setStartValue(QSize(width, window_height_min));
//    animation->setEndValue(QSize(width, window_height_min+expand_general_to));
//    animation->setEasingCurve(QEasingCurve::InBack);

//    animation->start();
//    std::cout << "Animation start" << std::endl;
    tutorial -> show();
    this -> close();
// =======
//     tutorial->showFullScreen();
//     this->close();
// >>>>>>> GUI
}

/* Triggered by the button "Mission Planning". This function opens a new window
 displaying the mission planing UI. Will also close the current MainWindow
 object.

Function added sometime prior to April 30 2015.*/
void MainWindow::missionPlanningClicked() {
    MapPlanning *mapPlanning = new MapPlanning();
    mapPlanning->showFullScreen();
    this->close();
}

/* Triggered by the button "Mission Execution". This function opens a new window
 displaying the mission execution UI. By default, there will be no mission
 loaded in the new window. Will also close the current MainWindow object.

Function added sometime prior to April 30 2015.*/
void MainWindow::missionExecutionClicked() {
    mapexecution *mapExecution = new mapexecution();
    mapExecution->showFullScreen();
    this->close();
}

/* Triggered by the button "Mission Recap". This function opens a new window
 displaying the mission recap UI. Will also close the current MainWindow object.

Function added sometime prior to April 30 2015.*/
void MainWindow::missionRecapClicked() {
    MissionRecap *missionRecap = new MissionRecap();
    missionRecap->showFullScreen();
    this->close();
}

/* Enables OS quit commands such as Command-Q.

 Function added sometime prior to April 30 2015.*/
void MainWindow::on_actionQuit_triggered() {
    this->close();
}
