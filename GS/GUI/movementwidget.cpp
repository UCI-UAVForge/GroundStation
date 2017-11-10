#include "movementwidget.h"

MovementWidget::MovementWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    alt = new TextBox("Altitude", "blue", this);
    lon = new TextBox("Latitude", "red", this);
    lat = new TextBox("Longitude", "red", this);
    vel = new TextBox("Velocity(GPS)", "green", this);
    pitch = new TextBox("Pitch", "blue", this);
    roll = new TextBox("Roll", "blue", this);
    yaw = new TextBox("Yaw", "blue", this);
    layout->setSpacing(6);
    layout->addWidget(alt, 0, 0, 1, 3);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(lat);
    hbox->addWidget(lon);
   // layout->addWidget(lat, 1, 0, 1, 1);
   // layout->addWidget(lon, 1, 1, 1, 2);
    layout->addLayout(hbox, 1, 0, 1, 3);
    layout->addWidget(vel, 2, 0, 1, 3);
    layout->addWidget(pitch, 3, 0, 1, 1);
    layout->addWidget(roll, 3, 1, 1, 1);
    layout->addWidget(yaw, 3, 2, 1, 1);
    setLayout(layout);
}

void MovementWidget::updateTelemetry(mavlink_gps_raw_int_t gps) {
    alt->setTxt(QString::number((float)gps.alt/1000,'f', 3));
    lat->setTxt(QString::number((float)gps.lat/10000000, 'f', 3));
    lon->setTxt(QString::number((float)gps.lon/10000000, 'f', 3));
    vel->setTxt(QString::number(gps.vel));
}

void MovementWidget::updateAttitude(mavlink_attitude_t att) {
    pitch->setTxt(QString::number(att.pitch));
    roll->setTxt(QString::number(att.roll));
    yaw->setTxt(QString::number(att.yaw));
}
