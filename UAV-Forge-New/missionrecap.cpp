#include "missionrecap.h"
#include "ui_missionrecap.h"

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
