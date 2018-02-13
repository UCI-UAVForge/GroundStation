#include "movementwidget.h"
#include <QDebug>

MovementWidget::MovementWidget(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    uav = new UAV();
}

MovementWidget::~MovementWidget(){

}

void MovementWidget::updateTelemetry(mavlink_vfr_hud_t vfr_hud) {
    ui.alt->setText(QString::number(vfr_hud.alt));
    ui.gSpeed->setText(QString::number(vfr_hud.groundspeed));
    ui.airSpeed->setText(QString::number(vfr_hud.airspeed));
}

void MovementWidget::updateAttitude(mavlink_attitude_t att) {
// Attitude -> Roll/Yaw/Pitch
}

void MovementWidget::updateLocalPosition(mavlink_local_position_ned_t l_pos) {
    // Velocity's units are unclear
  //  ui.velX->setText(QString::number((float) l_pos.vx * 1000, 'f', 1));
 //   ui.velY->setText(QString::number((float) l_pos.vy * 1000, 'f', 1));
  //  ui.velZ->setText(QString::number((float) l_pos.vz * 1000, 'f', 1));
}


void MovementWidget::mousePressEvent(QMouseEvent *event) {
//    if (ui.details->isVisible()) {
//        ui.details->hide();
//        ui.alt->resize(width(), 50);
//        ui.altTitle->resize(width(), 50);
//        resize(width(), 100);
//        adjustSize();

//    }
//    else {
//       // setMaximumHeight(100);
//        ui.details->show();

//    }

}

