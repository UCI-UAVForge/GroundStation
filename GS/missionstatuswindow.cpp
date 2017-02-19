#include "missionstatuswindow.h"
#include "ui_missionstatuswindow.h"

MissionStatusWindow::MissionStatusWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MissionStatusWindow)
{
    ui->setupUi(this);
}

MissionStatusWindow::~MissionStatusWindow()
{
    delete ui;
}
