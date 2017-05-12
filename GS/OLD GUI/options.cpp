#include "options.h"

#include "ui_options.h"

Options::Options(QWidget *parent) : QWidget(parent), ui(new Ui::Options) {
    ui->setupUi(this);
}

Options::~Options() {
    delete ui;
}

void Options:: on_missionPlanningButton_clicked() {
    this->close();
    MapPlanning *mapPlanning = new MapPlanning();
    mapPlanning->show();
}

void Options:: on_missionExecutionButton_clicked() {
    this->close();
    MapExecution *mapExecution = new MapExecution();
    mapExecution->show();
}

void Options:: on_missionRecapButton_clicked() {
    this->close();
    MissionRecap *missionRecap = new MissionRecap();
    missionRecap->show();
}

