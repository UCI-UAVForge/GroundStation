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
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(delete_button_clicked()));
    //delete = new  (row)

    ui->webView->load(QUrl("file:///Users/adrianvazquez/Desktop/UAVForge/maps.html"));
    model = new TableModel();
    ui->tableView->setModel(model);
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

void MapPlanning::delete_button_clicked() {
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    model->removeRows(indexes);
}
