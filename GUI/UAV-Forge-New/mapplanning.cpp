#include "mapplanning.h"
#include "ui_mapplanning.h"
#include "popwindowmp.h"
#include <QApplication>
#include "mainwindow.h"
#include "javascriptoperations.h"


MapPlanning::MapPlanning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapPlanning)
{
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();
    //connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonWasClicked(int)));
    //delete = new  (row)
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_7_clicked()));
    JavaScriptOperations *jso = new JavaScriptOperations(ui->webView);
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("myoperations",jso);
    ui->webView->load(QUrl("qrc:/res/html/maps.html"));

    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("myoperations",jso);
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

/*void MapPlanning::buttonWasClicked(int buttonID)
{

}*/

void MapPlanning::on_pushButton_6_clicked()
{
    popup = new PopWindowMP();
    popup->show();
}

void MapPlanning::on_pushButton_5_clicked()
{
    model->insertRow();
    //QWebFrame* frame = ui->webView->page()->mainFrame();
    //frame->evaluateJavaScript("addLatLng()");
}


void MapPlanning::on_pushButton_7_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    model->removeRows(indexes);
}

void MapPlanning::on_pushButton_8_clicked()
{
     //qDebug() << "Widget";
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

void MapPlanning::addPointToTable(){
    qDebug() << "Called addPointToTable";
}
