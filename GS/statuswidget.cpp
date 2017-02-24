#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <QDebug>

#include "StatusWidget.h"

///\todo Get rid of unnecessary includes in missionstatuswindow, statuswidget, and timerwidget.

///\todo Why does "explicit" cause problems? i.e. ctor illegal storage class
/* explicit */ StatusWidget::StatusWidget(QWidget* parent) : QPlainTextEdit( parent )
{
    //connect(StatusTimer, SIGNAL(timeout()), this, SLOT(showStatus()));
    connect(&StatusTimer, SIGNAL(timeout()), this, SIGNAL(updateMe()));
}

StatusWidget::~StatusWidget()
{
}

void StatusWidget::initiate()
{
    //Start the timer
    StatusTimer.start(200);
    //Clear the GUI
    this->showStatus( EMPTY_TELEMETRY_PACKET );
}

/*
QTimer StatusWidget::getStatusTimer()
{
    return StatusTimer ;
}
*/

void StatusWidget::showStatus( Protocol::TelemetryPacket * tp )
{
    float vX;
    float vY;
    float vZ;
    float pitch;
    float roll;
    float yaw;
    double lat;
    double lon;
    float alt;
    if ( tp == EMPTY_TELEMETRY_PACKET )
    {
        clear();
        appendPlainText("Empty: ");
        appendPlainText(QTime::currentTime().toString("hh:mm:ss"));
    }
    else
    {
        tp->GetVelocity(&vX, &vY,&vZ);
        tp->GetLocation(&lat, &lon, &alt );
        tp->GetOrientation(&pitch, &roll, & yaw);
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

/*
void StatusWidget::setStatusTimer(QTimer newStatusTimer)
{
    this->StatusTimer = newStatusTimer ;
}
*/
