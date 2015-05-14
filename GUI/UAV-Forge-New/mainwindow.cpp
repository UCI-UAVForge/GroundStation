#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "options.h"
#include "tutorial.h"
#include <QtWebKitWidgets/QWebView>
#include <QUrl>
#include "mapplanning.h"
#include "mapexecution.h"
#include "missionrecap.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),


    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->pushButton_8->setIcon(QIcon(":/res/longButtons/Mission_Execution_Button_Type_2.png"));
    //ui->pushButton_8->setIconSize(QSize(181,101));
    QPixmap pixmap(":/res/longButtons/Mission_Execution_Button_Type_2.png");
    QIcon ButtonIcon(pixmap);
    ui->pushButton_8->setIcon(ButtonIcon);
    ui->pushButton_8->setIconSize(pixmap.rect().size()/6);//QSize(ui->pushButton_8->width()+100,ui->pushButton_8->height()+200));

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
    tutorial -> showFullScreen();
}

void MainWindow::missionPlanningClicked()
{
    MapPlanning *mapPlanning = new MapPlanning();
    this->close();
    mapPlanning->showFullScreen();
}

void MainWindow::missionExecutionClicked()
{
    mapexecution *mapExecution = new mapexecution();
    this->close();
    mapExecution->showFullScreen();
}

void MainWindow::missionRecapClicked()
{
    MissionRecap *missionRecap = new MissionRecap();
    this->close();
    missionRecap->showFullScreen();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}
