#include "missionstatuswindow.h"
#include "ui_missionstatuswindow.h"

#include <QDebug>

MissionStatusWindow::MissionStatusWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MissionStatusWindow),
    currentTelemetryPacket( NULL )
{
    ui->setupUi(this);
    connect( this->ui->MyStatusWidget , SIGNAL( updateMe() ) , this , SIGNAL( updateStatusWidget() ) ) ;
}

MissionStatusWindow::~MissionStatusWindow()
{
    delete ui;
}

void MissionStatusWindow::initiateWidgets() {

    // Initiate status widget
    this->initiateStatusWidget();
    // Initiate timer widget
    this->initiateTimerWidget();

}

void MissionStatusWindow::initiateStatusWidget() {

    this->ui->MyStatusWidget->initiate();

}

void MissionStatusWindow::initiateTimerWidget() {

    this->ui->TimeTimerWidget->initiate();

}


void MissionStatusWindow::setCurrentTelemetryPacket( Protocol::TelemetryPacket * tp ) {

    this->currentTelemetryPacket = tp ;

    //Pass to StatusWidget. It will know how to parse the telemetry packet.
    this->ui->MyStatusWidget->showStatus( tp );

}
