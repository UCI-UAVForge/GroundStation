#include "actionwidget.h"
#include <QPalette>
ActionWidget::ActionWidget(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    activeColor = "rgb(60,200,103)";
    connect(ui.armButton, &QPushButton::clicked, this, &ActionWidget::armClicked);
    modeButtons.insert(ui.manualButton, Modes::MANUAL);
    modeButtons.insert(ui.circleButton, Modes::CIRCLE);
    modeButtons.insert(ui.guidedButton, Modes::GUIDED);
    modeButtons.insert(ui.autoButton, Modes::AUTO);
    modeButtons.insert(ui.stabilizeButton, Modes::STABILIZE);
    modeButtons.insert(ui.rtlButton, Modes::RTL);
    modeButtons.insert(ui.fbwaButton, Modes::FBWA);
    modeButtons.insert(ui.fbwbButton, Modes::FBWB);
    modeButtons.insert(ui.cruiseButton, Modes::CRUISE);
    modeButtons.insert(ui.loiterButton, Modes::LOITER);
    modeButtons.insert(ui.initButton, Modes::INITIALISING);

    foreach(QPushButton * p, this->findChildren<QPushButton*>()) {
       if (p->objectName() != "armButton") {
           connect(p, &QPushButton::clicked, this, &ActionWidget::modeClicked);
       }
    }
}

void ActionWidget::modeClicked() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    int m = modeButtons.value(buttonSender);
    qDebug() << "MODE:  " << m;
    emit setMode(m);
}
void ActionWidget::armClicked() {
    emit setArm(armed);
}

void ActionWidget::setButtonColor(QPushButton * button, QString color) {
   button->setStyleSheet("QPushButton{background-color: " + color + "} QPushButton:pressed{background-color: rgb(235, 235, 235)}");
}

void ActionWidget::setButtonOff(QPushButton * button) {
    setButtonColor(button, "rgb(60, 60, 60)");
}


void ActionWidget::setButtonsOff(QList<QPushButton*> buttonList) {
    for(int i = 0; i < buttonList.size(); i++) {
        setButtonOff(buttonList.at(i));
    }
}

void ActionWidget::toggleArmButton(bool armState) {
    if (armed != armState) {
        armed = armState;
        if (!armed) {
            ui.armButton->setText("DISARMED");
            setButtonColor(ui.armButton, "rgb(255, 80, 83)");
        }
        else {
            ui.armButton->setText("ARMED");
            setButtonColor(ui.armButton, activeColor);
        }
    }
}

void ActionWidget::toggleModeButtons(mavlink_heartbeat_t heartbeat) {
    if (mode != heartbeat.custom_mode) {
        setButtonsOff(modeButtons.keys());
        mode = heartbeat.custom_mode;
        setButtonColor(modeButtons.key(heartbeat.custom_mode), activeColor);
    }
}


