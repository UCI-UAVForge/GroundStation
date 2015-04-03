#include "mapexecution.h"
#include "ui_mapexecution.h"
#include "missionrecap.h"
#include "options.h"
#include "mainwindow.h"

mapexecution::mapexecution(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mapexecution)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("qrc:/res/html/maps.html"));
}

mapexecution::~mapexecution()
{
    delete ui;
}

void mapexecution::finishClicked()
{
    MissionRecap *missionRecap = new MissionRecap();
    this->close();
    missionRecap->showFullScreen();
}

void mapexecution::returnHomeClicked()
{
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->showFullScreen();
}

void mapexecution::cancelClicked()
{
    this->close();
}
