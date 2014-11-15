#include "mapplanning.h"
#include "ui_mapplanning.h"
#include "popwindowmp.h"
#include <QApplication>


MapPlanning::MapPlanning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapPlanning)
{
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonWasClicked(int)));

    //delete = new  (row)

    ui->webView->load(QUrl("file:///Users/adrianvazquez/Desktop/UAVForge/maps.html"));
}

MapPlanning::~MapPlanning()
{
    delete ui;
    delete model;
    delete popup;
}

void MapPlanning::buttonWasClicked(int buttonID)
{
}

void MapPlanning::on_pushButton_6_clicked()
{
    popup = new PopWindowMP();
    popup->show();
}

void MapPlanning::on_pushButton_5_clicked()
{
    model->insertRow();
}
