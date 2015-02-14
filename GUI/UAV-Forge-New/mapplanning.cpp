#include "mapplanning.h"
#include "ui_mapplanning.h"
#include "popwindowmp.h"
#include <QApplication>
#include "mainwindow.h"

MapPlanning::MapPlanning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapPlanning)
{
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();

    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_7_clicked()));
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()));

    ui->webView->load(QUrl("qrc:/res/html/maps.html"));

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

void MapPlanning::addClickListener(){
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("myoperations",this);
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


void MapPlanning::on_pushButton_7_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    model->removeRows(indexes);
}

void MapPlanning::on_pushButton_8_clicked()
{
     updateMap();
}

void MapPlanning::on_pushButton_clicked()
{
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->show();
}

void MapPlanning::updateMap(){
    ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");
    for(int i = 0; i < model->getList().size(); i++){
        QList<QString> list = model->getList()[i];
        if(list[2] == "W"){
            list[1] = "-"+list[1];
        }
        if(list[4] == "S"){
            list[3] = "-"+list[3];
        }

        ui->webView->page()->mainFrame()->evaluateJavaScript("addLatLngCoords("+list[3]+","+list[1]+")");
    }
}

void MapPlanning::addPointToTable(double lat, double lng){
    model->insertRow(lng,lat);
}
