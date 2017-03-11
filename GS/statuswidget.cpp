#include <QDebug>
#include <QTime>
#include "StatusWidget.h"

StatusWidget::StatusWidget(QWidget* parent) : QPlainTextEdit( parent ) {
    connect(&StatusTimer, SIGNAL(timeout()), this, SLOT(showStatus()));
    this->currentTelemetryPacket = EMPTY_TELEMETRY_PACKET ;
}

StatusWidget::~StatusWidget() {}

void StatusWidget::initiate() {
    StatusTimer.start(200);
    clear();
}

void StatusWidget::stop() {
    StatusTimer.stop();
}

void StatusWidget::showStatus() {
    float vX,vY,vZ,pitch,roll,yaw,alt;
    double lat,lon;
    if ( this->currentTelemetryPacket == EMPTY_TELEMETRY_PACKET ) {
        clear();
        appendPlainText("Empty: ");
        appendPlainText(QTime::currentTime().toString("hh:mm:ss"));
    }
    else {
        this->currentTelemetryPacket->GetVelocity(&vX, &vY,&vZ);
        this->currentTelemetryPacket->GetLocation(&lat, &lon, &alt );
        this->currentTelemetryPacket->GetOrientation(&pitch, &roll, & yaw);
        QString text;
        text.append("Location: ");
        text.append(QString::number(lat,'f',2) + ", " + QString::number(lon,'f',2) + ", " + QString::number(alt,'f',2));
        text.append("\nVelocity: ");
        text.append(QString::number(vX,'f',2) + ", " + QString::number(vY,'f',2) + ", " + QString::number(vZ,'f',2));
        text.append("\nOrientation: ");
        text.append(QString::number(pitch,'f',2) + ", " + QString::number(roll,'f',2) + ", " + QString::number(yaw,'f',2));
        clear();
        appendPlainText(text);
    }
}

Protocol::TelemetryPacket StatusWidget::getCurrentTelemetryPacket() {
    return *( this->currentTelemetryPacket ) ;
}

void StatusWidget::setCurrentTelemetryPacket( Protocol::TelemetryPacket * currentTelemetryPacket ) {
    this->currentTelemetryPacket = currentTelemetryPacket ;
}
