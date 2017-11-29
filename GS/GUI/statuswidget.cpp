#include <QDebug>
#include <QTime>
#include "statuswidget.h"
#include <QTimer>
StatusWidget::StatusWidget(QWidget* parent) : QWidget( parent ) {
    ui.setupUi(this);
    timer = new QTimer(this);
    timer->start(10000);
    connect(timer, &QTimer::timeout, this, &StatusWidget::timeout);
}

void StatusWidget::setLink(Link * l) {
    link = l;
}

void StatusWidget::updateBattery(mavlink_battery_status_t battery) {
    ui.bat->setText(QString::number(battery.battery_remaining) + "%");
}

void StatusWidget::timeout() {
    ui.connection->setText("Disconnected");
    ui.connectionTitle->setStyleSheet("QLabel{background-color: rgb(255, 225, 129)}");
}

void StatusWidget::updateHeartbeat(mavlink_heartbeat_t heartbeat) {
   timer->start(10000);
   ui.connection->setText("Ready");
   ui.connectionTitle->setStyleSheet("QLabel{background-color: rgb(175, 225, 129)}");

}

