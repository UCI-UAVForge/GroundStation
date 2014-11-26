#include "options.h"
#include "ui_options.h"
#include "mapplanning.h"
#include "mapexecution.h"
#include "missionrecap.h"
Options::Options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
}

Options::~Options()
{
    delete ui;
}

void Options:: missionPlanningClicked()
{
    this->close();
    MapPlanning *mapPlanning = new MapPlanning();
    mapPlanning->show();
}

void Options:: missionExecutionClicked()
{
    this->close();
    mapexecution *mapExecution = new mapexecution();
    mapExecution->show();
}

void Options:: missionRecapClicked()
{
    this->close();
    MissionRecap *missionRecap = new MissionRecap();
    missionRecap->show();
}

