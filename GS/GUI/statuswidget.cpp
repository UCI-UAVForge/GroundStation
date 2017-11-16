#include <QDebug>
#include <QTime>
#include "statuswidget.h"

StatusWidget::StatusWidget(QWidget* parent) : QWidget( parent ) {
    ui.setupUi(this);
}

void StatusWidget::setLink(UdpLink * l) {
    link = l;
}

void StatusWidget::updateBattery(mavlink_battery_status_t battery) {
    ui.bat->setText(QString::number(battery.battery_remaining) + "%");
}



void StatusWidget::updateHeartbeat(mavlink_heartbeat_t heartbeat) {
   ui.connection->setText("UDP " + link->getHost().toString()+  ":" + QString::number(link->getPort()));
   ui.connectionTitle->setStyleSheet("QLabel{background-color: rgb(175, 225, 129)}");

}

