#include "mapexecution.h"
#include "ui_mapexecution.h"

mapexecution::mapexecution(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mapexecution)
{
    ui->setupUi(this);
}

mapexecution::~mapexecution()
{
    delete ui;
}
