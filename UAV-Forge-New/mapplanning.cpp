#include "mapplanning.h"
#include "ui_mapplanning.h"

MapPlanning::MapPlanning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapPlanning)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Hover");
}

MapPlanning::~MapPlanning()
{
    delete ui;
}

/*void MapPlanning::ComboBox() {
    width: 200;
    model: [ "Banana", "Apple", "Coconut" ];
}*/
