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
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_7_clicked()));

    ui->webView->load(QUrl("file:///Users/kelvinwu/UCI-SoftwareDev/GUI/UAV-Forge-New/maps.html"));
    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());
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
    QWebFrame* frame = ui->webView->page()->mainFrame();
    frame->evaluateJavaScript("addLatLng()");
}


void MapPlanning::on_pushButton_7_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    model->removeRows(indexes);
}
