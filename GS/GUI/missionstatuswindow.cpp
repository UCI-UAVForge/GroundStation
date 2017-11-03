#include "missionstatuswindow.h"
#include "ui_missionstatuswindow.h"

#include <QDebug>

MissionStatusWindow::MissionStatusWindow(QWidget *parent) : QDialog(parent),ui(new Ui::MissionStatusWindow) {
    ui->setupUi(this);
    //this->currentTelemetryPacket = EMPTY_TELEMETRY_PACKET ;
    //this->ui->MyStatusWidget->setCurrentTelemetryPacket( this->currentTelemetryPacket );
}

MissionStatusWindow::~MissionStatusWindow() {
    delete ui;
}

///\todo Return boolean for successful or failed initiation
void MissionStatusWindow::initiateWidgets() {
    this->initiateStatusWidget();
    this->initiateTimerWidget();
}

void MissionStatusWindow::stopWidgets() {
    this->stopStatusWidget() ;
    this->stopTimerWidget() ;
}

void MissionStatusWindow::stopStatusWidget() {
    //this->ui->MyStatusWidget->stop() ;
}

void MissionStatusWindow::stopTimerWidget() {
//    this->ui->TimeTimerWidget->stop() ;
}

void MissionStatusWindow::initiateStatusWidget() {
    //this->ui->MyStatusWidget->initiate();
}

void MissionStatusWindow::initiateTimerWidget() {
 //   this->ui->TimeTimerWidget->initiate();
}
/*
void MissionStatusWindow::setCurrentTelemetryPacket( Protocol::TelemetryPacket * tp ) {
    this->currentTelemetryPacket = tp;
    this->ui->MyStatusWidget->setCurrentTelemetryPacket( this->currentTelemetryPacket );
}*/

void MissionStatusWindow::setCurrentTelemetryData(TelemetryData *data) {
    this->currentTelemetryData = data;
    //this->ui->MyStatusWidget->setCurrentTelemetryData(this->currentTelemetryData);
}
