#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "StatusWidget.h"


explicit StatusWidget::StatusWidget(QObject* parent)
{
    connect(StatusTimer, SIGNAL(timeout()), this, SLOT(showStatus()));
}

StatusWidget::~StatusWidget()
{
}

void StatusWidget::initiate(messagebox * mbin)
{
    mb = mbin;
    StatusTimer->start(200);
    showStatus();
}

QTimer StatusWidget::getStatusTimer()
{
    return StatusTimer ;
}

void StatusWidget::showStatus()
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
//    float heading;
    if (mb->get_telem_packets().empty())
    {
        clear();
        appendPlainText("Empty: ");
        appendPlainText(QTime::currentTime().toString("hh:mm:ss"));
    }
    else
    {
        Protocol::TelemetryPacket last = mb->get_telem_packets().back();
        last.GetVelocity(&vX, &vY,&vZ);
        last.GetLocation(&lat, &lon, &alt );
        last.GetOrientation(&pitch, &roll, & yaw);
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

void StatusWidget::setStatusTimer(QTimer newStatusTimer)
{
    this->StatusTimer = newStatusTimer ;
}
