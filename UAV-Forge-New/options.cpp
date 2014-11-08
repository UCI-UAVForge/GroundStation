#include "options.h"
#include "ui_options.h"
#include "mapplanning.h"
#include "mapexecution.h"
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
