#include "movementwidget.h"
#include <QDebug>

MovementWidget::MovementWidget(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    style = Style();
    foreach(QPushButton * p, this->findChildren<QPushButton*>()) {
       style.setButtonColor(p, QColor(40,40,40));
    }
    connect(ui.alt, &QPushButton::clicked, this, &MovementWidget::toggleAltUnits);
    connect(ui.relAlt, &QPushButton::clicked, this, &MovementWidget::toggleRelAltUnits);
    connect(ui.Climb, &QPushButton::clicked, this, &MovementWidget::toggleClimbUnits);
    connect(ui.gSpeed, &QPushButton::clicked, this, &MovementWidget::toggleGroundSpdUnits);
    connect(ui.airSpeed, &QPushButton::clicked, this, &MovementWidget::toggleAirSpdUnits);
    groundSpdKnots = false;
    airSpdKIAS = false;
}

MovementWidget::~MovementWidget(){
}

void MovementWidget::toggleAltUnits() {
    altFt = altFt ? false : true;
}

void MovementWidget::toggleRelAltUnits() {
    relAltFt = relAltFt ? false : true;
}

void MovementWidget::toggleClimbUnits() {
    ClimbFt = !ClimbFt;
}

void MovementWidget::toggleGroundSpdUnits() {
    groundSpdKnots = groundSpdKnots ? false : true;
}

void MovementWidget::toggleAirSpdUnits() {
    airSpdKIAS = airSpdKIAS ? false : true;
}

void MovementWidget::updateTelemetry(mavlink_vfr_hud_t vfr_hud) {
    if (altFt) {
        ui.alt->setText(QString::number(vfr_hud.alt * 3.28084) + " ft.");
    } else {
        ui.alt->setText(QString::number(vfr_hud.alt) + " m.");
    }
    if (groundSpdKnots)
        ui.gSpeed->setText(QString::number(metersToKnots(vfr_hud.groundspeed), 'f', 2) + " knots.");
    else
        ui.gSpeed->setText(QString::number(vfr_hud.groundspeed, 'f', 2) + " m/s.");
    if (airSpdKIAS)
        ui.airSpeed->setText(QString::number(metersToKnots(vfr_hud.airspeed), 'f', 2) + " KIAS.");
    else
        ui.airSpeed->setText(QString::number(vfr_hud.airspeed, 'f', 2) + " m/s.");
    ui.Climb->setText(QString::number(vfr_hud.climb, 'f', 2) + " m/s.");
    ui.throttle->setText(QString::number(vfr_hud.throttle) + " %.");
}

void MovementWidget::updateAttitude(mavlink_attitude_t att) {
// Attitude -> Roll/Yaw/Pitch
}

void MovementWidget::updateGlobalPosition(mavlink_global_position_int_t g_pos) {
    if (relAltFt)
        ui.relAlt->setText(QString::number((float)g_pos.relative_alt/1000 * 3.28084, 'f', 2) + " ft.");
    else
        ui.relAlt->setText(QString::number((float)g_pos.relative_alt/1000, 'f', 2) + " m.");
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

float MovementWidget::metersToKnots(float meters) {
    return meters * 1.94384;
}

