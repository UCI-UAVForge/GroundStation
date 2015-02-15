#include "mapplanning.h"
#include "ui_mapplanning.h"
#include "popwindowmp.h"
#include <QApplication>
#include "mainwindow.h"
#include <QString>

MapPlanning::MapPlanning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapPlanning) {
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();
    //connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_7_clicked()));

    //Recreates the c++/JS bridge when the JavaScript window is refreshed
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()));

    ui->webView->load(QUrl("qrc:/res/html/maps.html"));

    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());
}

MapPlanning::~MapPlanning() {
    delete ui;
    delete model;
    delete popup;
}

void MapPlanning::addClickListener() {
    /* Since c++/JS bridges are broken when the JS page refreshes this slot
     is used to rebruild the bridge each time when triggered by a
     javaScriptWindowObjectCleared signal from the page frame. Function
     added by Jordan Dickson Feb 14th 2015. */

    //Creates the bridge called cbridge between the java script object and this class.
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}

void MapPlanning::on_pushButton_6_clicked() {
    popup = new PopWindowMP();
    popup->show();
}

void MapPlanning::on_pushButton_5_clicked() {
    model->insertRow();
}


void MapPlanning::on_pushButton_7_clicked() {
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    model->removeRows(indexes);
    updateMap();
}

void MapPlanning::on_pushButton_8_clicked() {
     updateMap();
}

void MapPlanning::on_pushButton_clicked() {
    MainWindow *mainwindow = new MainWindow();
    this -> close();
    mainwindow->show();
}

void MapPlanning::updateMap() {
    /* Sends a request for the map to clear itself, causing the JavaScript page
    to reload itself. This function then cycles through each entry on the table
    and enters the coordinates on the map one by one in order. Function added by
    Jordan Dickson Feb 14th 2015. */
    //Sends clearMap request.
    ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");
    //Loops through table entries
    for(int i = 0; i < model->getList().size(); i++){
        QList<QString> list = model->getList()[i];
        //Converts West and South coordinates to negative numbers.
        double lat = list[3].toDouble();
        double lng = list[1].toDouble();
        if(list[2] == "W"){
            lng *= -1.0;
        }
        if(list[4] == "S"){
            lat *= -1.0;
        }
        //Sends the add point request with its parameters.
        ui->webView->page()->mainFrame()->evaluateJavaScript("addLatLngCoords("+QString::number(lat)+","+QString::number(lng)+")");
    }
}

void MapPlanning::addPointToTable(double lat, double lng) {
    /* Passer function for adding entries to the table with coordinates recived
    from the JavaScript file. See tablemodel.cpp file for more information.
    Added by Jordan Dickson Feb 14th 2015.*/
    model->insertRow(lng,lat);
}
