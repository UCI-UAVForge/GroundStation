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
    mavlink_msg_command_long_pack(255, 1, &msg, 1, 0, 400, 1, !armed, 0, 0, 0, 0, 0, 0);
    link->sendMsg(msg);
}

void ActionWidget::setButtonColor(QPushButton * button, QString color) {
   button->setStyleSheet("QPushButton{background-color: " + color + "} QPushButton:pressed{background-color: rgb(235, 235, 235)}");
}

void ActionWidget::setButtonOff(QPushButton * button) {
    button->setStyleSheet("QPushButton{background-color:rgb(200, 200, 200)} QPushButton:pressed{background-color: rgb(235, 235, 235)}");
}


void ActionWidget::setButtonsOff(QVector<QPushButton*> buttonList) {
    for(int i = 0; i < buttonList.size(); i++) {
        setButtonOff(buttonList.at(i));
    }
}

void ActionWidget::toggleArmButton(mavlink_heartbeat_t heartbeat) {
    switch(heartbeat.base_mode) {
        case 81: case 89:
            if (armed) {
                armed = false;
                ui.armButton->setText("DISARMED");
                setButtonColor(ui.armButton, "rgb(255, 80, 83)");
            }
        break;
        case 209: case 217:
            if (!armed) {
                armed = true;
                ui.armButton->setText("ARMED");
                setButtonColor(ui.armButton, "rgb(169, 248, 157)");
            }
        break;
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
        mode = heartbeat.custom_mode;
        switch(heartbeat.custom_mode) {
            case 0:
                setButtonColor(ui.manualButton, "rgb(169, 248, 157)");
            break;
            case 10:
                setButtonColor(ui.autoButton, "rgb(169, 248, 157)");
            break;
            case 15:
                setButtonColor(ui.guidedButton, "rgb(169, 248, 157)");
            break;
            default:
            break;
        }
    }
}


