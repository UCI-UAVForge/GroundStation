#include "uavbutton.h"
#include "ui_uavbutton.h"

UAVButton::UAVButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UAVButton)
{
    ui->setupUi(this);
    eEffect= new QGraphicsColorizeEffect(ui->uavButton);
    eEffect->setColor(QColor(Qt::red));
    changeColor = QColor(Qt::blue);
    pulse = new QPropertyAnimation(eEffect,"color");
    connect(ui->uavButton, &QPushButton::clicked, this, &UAVButton::doit);
    timer = new QTimer(this);
    timer->start(10000);
    connect(timer, &QTimer::timeout, this, &UAVButton::timeout);

}

void UAVButton::updateBattery(mavlink_battery_status_t battery) {
    ui->uavButton->setText("UAV: " + QString::number(battery.battery_remaining) + "%");
    if (battery.battery_remaining < 30) {
        changeColor = QColor(Qt::red);
    }
}

void UAVButton::timeout() {
    ui->uavButton->setText("UAV: --%");
    ui->uavButton->setGraphicsEffect(nullptr);
}

void UAVButton::doit() {
}

void UAVButton::updateHeartbeat(mavlink_heartbeat_t heartbeat) {
    timer->start(10000);
    ui->uavButton->setGraphicsEffect(eEffect);
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
