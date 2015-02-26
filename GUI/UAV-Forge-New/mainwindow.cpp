#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "options.h"
#include "tutorial.h"
#include <QtWebKitWidgets/QWebView>
#include <QUrl>
#include "mapplanning.h"
#include "mapexecution.h"
#include "missionrecap.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::openOptions()
{
    Options *options = new Options();
    options -> show();
}*/

void MainWindow::openTutorial()
{
    Tutorial *tutorial = new Tutorial();
    this -> close();
    tutorial -> show();
}

void MainWindow:: missionPlanningClicked()
{
    MapPlanning *mapPlanning = new MapPlanning();
    this -> close();
    mapPlanning->show();
}

void MainWindow:: missionExecutionClicked()
{
    mapexecution *mapExecution = new mapexecution();
    this -> close();
    mapExecution->show();
}

void MainWindow:: missionRecapClicked()
{
    MissionRecap *missionRecap = new MissionRecap();
    this -> close();
    missionRecap->show();
}
