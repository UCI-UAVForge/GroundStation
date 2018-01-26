#include "actionwidget.h"
#include <QPalette>
ActionWidget::ActionWidget(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.armButton, &QPushButton::clicked, this, &ActionWidget::armClicked);
    connect(ui.manualButton, &QPushButton::clicked, this, &ActionWidget::setManual);
    connect(ui.guidedButton, &QPushButton::clicked, this, &ActionWidget::setGuided);
    connect(ui.autoButton, &QPushButton::clicked, this, &ActionWidget::setAuto);
    modeButtons << ui.manualButton << ui.guidedButton << ui.autoButton;
}

void ActionWidget::armClicked() {
    emit setArm(armed);
}

void ActionWidget::setButtonColor(QPushButton * button, QString color) {
   button->setStyleSheet("QPushButton{background-color: " + color + "} QPushButton:pressed{background-color: rgb(235, 235, 235)}");
}

void ActionWidget::setButtonOff(QPushButton * button) {
    setButtonColor(button, "rgb(200, 200, 200)");
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
                setButtonColor(ui.armButton, "rgb(60, 200, 103)");
            }
        break;
    }
}


void ActionWidget::toggleModeButtons(mavlink_heartbeat_t heartbeat) {
    if (mode != heartbeat.custom_mode) {
        setButtonsOff(modeButtons);
        mode = heartbeat.custom_mode;
        switch(heartbeat.custom_mode) {
            case 0:
                setButtonColor(ui.manualButton, "rgb(60, 200, 103)");
            break;
            case 10:
                setButtonColor(ui.autoButton, "rgb(60, 200, 103)");
            break;
            case 15:
                setButtonColor(ui.guidedButton, "rgb(60, 200, 103)");
            break;
            default:
            break;
        }
    }
}


