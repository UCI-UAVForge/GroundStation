#include <QDebug>
#include <QTime>
#include "statuswidget.h"

StatusWidget::StatusWidget(QWidget* parent) : QWidget( parent ) {
    layout = new QGridLayout(this);
    battery = new TextBox("Battery", "green", this);
    layout->setSpacing(6);
    layout->addWidget(battery, 0, 0, 1, 3);
    setLayout(layout);
}

void StatusWidget::updateStatus(mavlink_sys_status_t status) {
    battery->setTxt(QString::number(status.battery_remaining) + "%");
}

