#include "mapplanning.h"
#include "ui_mapplanning.h"

MapPlanning::MapPlanning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapPlanning)
{
    ui->setupUi(this);
}

MapPlanning::~MapPlanning()
{
    delete ui;
}
