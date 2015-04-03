#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "options.h"
#include "tutorial.h"
#include <QtWebKitWidgets/QWebView>
#include <QUrl>
#include "mapplanning.h"
#include "mapexecution.h"
#include "missionrecap.h"
// <<<<<<< HEAD
#include <iostream>
// =======
//erase later
// >>>>>>> GUI

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
// <<<<<<< HEAD

//    QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
//    std::cout << "New animation" << std::endl;
//    animation->setDuration(10000);
//    animation->setStartValue(QSize(width, window_height_min));
//    animation->setEndValue(QSize(width, window_height_min+expand_general_to));
//    animation->setEasingCurve(QEasingCurve::InBack);

//    animation->start();
//    std::cout << "Animation start" << std::endl;
    this -> close();
    tutorial -> show();
// =======
//     this->close();
//     tutorial->showFullScreen();
// >>>>>>> GUI
}

void MainWindow:: missionPlanningClicked()
{
    MapPlanning *mapPlanning = new MapPlanning();
    this->close();
    mapPlanning->showFullScreen();
}

void MainWindow:: missionExecutionClicked()
{
    mapexecution *mapExecution = new mapexecution();
    this->close();
    mapExecution->showFullScreen();
}

void MainWindow:: missionRecapClicked()
{
    MissionRecap *missionRecap = new MissionRecap();
    this->close();
    missionRecap->showFullScreen();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}
