#include "missionrecap.h"
#include "ui_missionrecap.h"
#include "mapexecution.h"
MissionRecap::MissionRecap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionRecap)
{
    ui->setupUi(this);
}

MissionRecap::~MissionRecap()
{
    delete ui;
}

void MissionRecap:: replayMissionClicked()
{
    this->close();
    mapexecution *mapExecution = new mapexecution();
    mapExecution->show();
}
