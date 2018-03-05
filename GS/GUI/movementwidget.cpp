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

void MovementWidget::updateGlobalPosition(mavlink_global_position_int_t g_pos) {
    ui.altRel->setText(QString::number((float)g_pos.relative_alt/1000, 'f', 2));
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

