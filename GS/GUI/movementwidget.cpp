#include "movementwidget.h"

MovementWidget::MovementWidget(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
}

void MovementWidget::updateTelemetry(mavlink_gps_raw_int_t gps) {
    ui.alt->setText(QString::number((float)gps.alt/1000,'f', 4) + " m.");
    ui.loc->setText(QString::number((float)gps.lat/10000000, 'f', 4) + ", " + QString::number((float)gps.lon/10000000, 'f', 4));
}

void MovementWidget::updateAttitude(mavlink_attitude_t att) {
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
