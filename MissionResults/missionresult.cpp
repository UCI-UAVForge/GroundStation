#include "missionresult.h"
#include "ui_missionresult.h"

missionresult::missionresult(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::missionresult)
{
    ui->setupUi(this);
}

missionresult::~missionresult()
{
    delete ui;
}
