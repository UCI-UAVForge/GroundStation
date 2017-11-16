#include "actionwidget.h"
#include <QPalette>
ActionWidget::ActionWidget(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.armButton, &QPushButton::clicked, this, &ActionWidget::setArm);
    connect(ui.manualButton, &QPushButton::clicked, this, &ActionWidget::setManual);
    connect(ui.guidedButton, &QPushButton::clicked, this, &ActionWidget::setGuided);
    connect(ui.autoButton, &QPushButton::clicked, this, &ActionWidget::setAuto);
    modeButtons << ui.manualButton << ui.guidedButton << ui.autoButton;
}

void ActionWidget::setLink(UdpLink *l) {
    link = l;
}

void ActionWidget::setArm() {
    mavlink_message_t msg;
    if (!armed)
        mavlink_msg_command_long_pack(255, 1, &msg, 1, 0, 400, 1, 1, 0, 0, 0, 0, 0, 0);
    else
        mavlink_msg_command_long_pack(255, 1, &msg, 1, 0, 400, 1, 0, 0, 0, 0, 0, 0, 0);
    link->sendMsg(msg);
}

void ActionWidget::setButtonOn(QPushButton * button) {
   button->setStyleSheet("QPushButton{background-color: rgb(169, 248, 157)}");
}

void ActionWidget::setButtonOff(QPushButton * button) {
    button->setStyleSheet("QPushButton{background-color:rgb(200, 200, 200)};");
}

void ActionWidget::setButtonsOff(QVector<QPushButton*> buttonList) {
    for(int i = 0; i < buttonList.size(); i++) {
        setButtonOff(buttonList.at(i));
    }
}

void ActionWidget::toggleArmButton() {
    if (!armed) {
        armed = true;
        ui.armButton->setText("ARMED");
        setButtonOn(ui.armButton);
    }
    else {
        armed = false;
        ui.armButton->setText("DISARMED");
        setButtonOff(ui.armButton);
    }
}

void ActionWidget::armFailed() {
    ui.armButton->setStyleSheet("QPushButton{background-color:rgb(180,10, 10)};");
    if (!armed) {
        ui.armButton->setText("FAILED TO ARM");
    } else {
        ui.armButton->setText("FAILED TO DISARM");
    }
}

void ActionWidget::setManual() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(255,  1 , &msg, 1, 1, 0);
    link->sendMsg(msg);
}
void ActionWidget::setGuided() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(255,  1 , &msg, 1, 1, 15);
    link->sendMsg(msg);
}
void ActionWidget::setAuto() {
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(255,  1 , &msg, 1, 1, 10);
    link->sendMsg(msg);
}


void ActionWidget::toggleModeButtons(mavlink_heartbeat_t heartbeat) {
    if (mode != heartbeat.custom_mode) {
        setButtonsOff(modeButtons);
        qDebug()<< heartbeat.custom_mode;
        mode = heartbeat.custom_mode;
        switch(heartbeat.custom_mode) {
            case 0:
                setButtonOn(ui.manualButton);
            break;
            case 10:
                setButtonOn(ui.autoButton);
            break;
            case 15:
                setButtonOn(ui.guidedButton);
            break;
            default:
            break;
        }
    }
}


