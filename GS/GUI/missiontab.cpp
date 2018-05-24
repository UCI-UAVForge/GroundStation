#include "missiontab.h"
#include "ui_missiontab.h"

MissionTab::MissionTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionTab)
{
    ui->setupUi(this);

}

//void MissionTab::addWaypoint() {
//    //ui->missionTable->getSelections
//}

MissionTab::~MissionTab()
{
    delete ui;
}
