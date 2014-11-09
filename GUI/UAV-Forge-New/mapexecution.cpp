#include "mapexecution.h"
#include "ui_mapexecution.h"
#include "missionrecap.h"
#include "options.h"
mapexecution::mapexecution(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mapexecution)
{
    ui->setupUi(this);
}

mapexecution::~mapexecution()
{
    delete ui;
}

void mapexecution::finishClicked()
{
    MissionRecap *missionRecap = new MissionRecap();
    missionRecap->show();
}

void mapexecution::returnHomeClicked()
{
    this->close();
}

void mapexecution::cancelClicked()
{
    this->close();
}
