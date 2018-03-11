#include "uavbutton.h"
#include "ui_uavbutton.h"

UAVButton::UAVButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UAVButton)
{
    ui->setupUi(this);
    style = Style();
    eEffect= new QGraphicsColorizeEffect(ui->uavButton);
    eEffect->setColor(QColor(Qt::red));
    eEffect->setEnabled(false);
    ui->uavButton->setGraphicsEffect(eEffect);
    changeColor = QColor(Qt::blue);
    style.setButtonOff(ui->uavButton);
    pulse = new QPropertyAnimation(eEffect, "color");
    connect(ui->uavButton, &QPushButton::clicked, this, &UAVButton::openConnection);
    timer = new QTimer(this);
    timer->start(timeoutMS);
    connect(timer, &QTimer::timeout, this, &UAVButton::timeout);

}

void UAVButton::updateBattery(mavlink_sys_status_t battery) {
    ui->uavButton->setText("UAV: " + QString::number(battery.battery_remaining) + "%");
    if (battery.battery_remaining < 30) {
        changeColor = QColor(Qt::red);
    }
}

void UAVButton::timeout() {
    ui->uavButton->setText("CONNECT");
    eEffect->setEnabled(false);
    emit(changeStatus("Disconnected"));
}

void UAVButton::openConnection() {
    emit(openConn());
}

void UAVButton::updateHeartbeat(mavlink_heartbeat_t heartbeat) {
    timer->start(timeoutMS);
    emit(changeStatus("Connected"));
    eEffect->setEnabled(true);
    if (!downbeat) {
        downbeat = true;
        pulse->setDuration(300);
        pulse->setEndValue(QColor(Qt::black));
        pulse->start();
    }
   else {
        downbeat = false;
        pulse->setDuration(300);
        pulse->setEndValue(changeColor);
        pulse->start();
    }
}

UAVButton::~UAVButton()
{
    delete ui;
}
