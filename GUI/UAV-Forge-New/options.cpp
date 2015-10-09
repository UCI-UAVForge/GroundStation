#include "options.h"

#include "ui_options.h"

Options::Options(QWidget *parent) : QWidget(parent), ui(new Ui::Options) {
    ui->setupUi(this);
}

Options::~Options() {
    delete ui;
}

void Options:: missionPlanningClicked() {
    this->close();
    MapPlanning *mapPlanning = new MapPlanning();
    mapPlanning->show();
}

void Options:: missionExecutionClicked() {
    this->close();
    MapExecution *mapExecution = new MapExecution();
    mapExecution->show();
}

void Options:: missionRecapClicked() {
    this->close();
    MissionRecap *missionRecap = new MissionRecap();
    missionRecap->show();
}

