#include "infowidget.h"


InfoWidget::InfoWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    alt = new TextBox("Altitude");
    lon = new TextBox("Latitude");
    lat = new TextBox("Longitude");
    vel = new TextBox("Velocity(GPS)");
    layout->addWidget(alt, 0, 0, 1, 2);
    layout->addWidget(lat, 1, 0, 1, 1);
    layout->addWidget(lon, 1, 1, 1, 1);
    layout->addWidget(vel, 2, 0, 1, 2);
    setLayout(layout);
}

void InfoWidget::updateTelemetry(mavlink_gps_raw_int_t gps) {
    alt->setTxt(QString::number((float)gps.alt/1000,'f', 3));
    lat->setTxt(QString::number((float)gps.lat/1000000, 'f', 3));
    lon->setTxt(QString::number((float)gps.lon/1000000, 'f', 3));
    vel->setTxt(QString::number(gps.vel));
}
