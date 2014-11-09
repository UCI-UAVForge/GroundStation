#include "mapplanning.h"
#include "ui_mapplanning.h"
#include "popwindowmp.h"

MapPlanning::MapPlanning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapPlanning)
{
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonWasClicked(int)));
    ui->webView->load(QUrl("https://www.google.com/maps"));
}

MapPlanning::~MapPlanning()
{
    delete ui;
}

void MapPlanning::buttonWasClicked(int buttonID)
{
    ui->tableWidget->removeRow(buttonID);
}

void MapPlanning::on_pushButton_6_clicked()
{
    PopWindowMP *pw = new PopWindowMP();
    pw->show();
}

void MapPlanning::on_pushButton_5_clicked()
{
    int i = 0;
    ui->tableWidget->insertRow(i);
    ui->tableWidget->setCellWidget(i, 0, new QComboBox);
    ui->tableWidget->setCellWidget(i, 2, new QComboBox);
    ui->tableWidget->setCellWidget(i, 3, new QPushButton("Delete"));
    //buttonGroup->addButton(*(ui->tableWidget->cellWidget(i, 3)), i);
    i++;
}
