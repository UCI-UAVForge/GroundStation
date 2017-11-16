#include "qfiwidget.h"
#include <QDebug>

QFIWidget::QFIWidget( QWidget *parent ) :
        QWidget( parent )
{
    layout = new QVBoxLayout(this);
    layout->setSpacing(6);

    // Primary Flight Display
    m_pfd = new qfi_PFD(parent);
    m_pfd->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pfd->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pfd->setFixedSize(250,250);
    layout->addWidget(m_pfd);
    layout->setSizeConstraint(QLayout::SetFixedSize);


    // Turn Coordinator Instrument
//    m_tc = new qfi_TC(parent);
//    m_tc->setMinimumSize(400,400);
//    m_tc->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    m_tc->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    layout->addWidget(m_tc);

    setLayout(layout);
}

/*
PFD Instrument:
Roll - Attitude
Pitch - Attitude
FlightPathMarker
    AOA - X
    Sideslip - X
TurnRate - X
BarH/V - X
DotH/V - X
Altitude - VFR_Hud
Pressure - Scaled Pressure
Airspeed - VFR_Hud
MachNo - X
Heading - VFR_Hud
ClimbRate - VFR_Hud
*/

void QFIWidget::updateVFR(mavlink_vfr_hud_t vfr)
{
    this->setAirspeed(vfr.airspeed);
    this->setAltitude(vfr.alt);
    this->setClimbRate(vfr.climb);
    this->setHeading(vfr.heading);
    this->update();
}

void QFIWidget::updateAttitude(mavlink_attitude_t att)
{
    this->setRoll(att.roll);
    this->setPitch(att.pitch);
    this->update();
}

void QFIWidget::updatePressure(mavlink_scaled_pressure_t p)
{
    this->setPressure(p.press_abs);
}
