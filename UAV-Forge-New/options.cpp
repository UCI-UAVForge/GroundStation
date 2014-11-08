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
    MapPlanning *mapPlanning = new MapPlanning();
    mapPlanning->show();
}

void Options:: missionExecutionClicked()
{
    mapexecution *mapExecution = new mapexecution();
    mapExecution->show();
}

void Options:: missionRecapClicked()
{
    MissionRecap *missionRecap = new MissionRecap();
    missionRecap->show();
}

