#include "actionwidget.h"
#include <QPalette>
ActionWidget::ActionWidget(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    style = Style();
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
    modeButtons.insert(ui.tuneButton, Modes::AUTOTUNE);

    foreach(QPushButton * p, this->findChildren<QPushButton*>()) {
       if (p->objectName() != "armButton") {
           connect(p, &QPushButton::clicked, this, &ActionWidget::modeClicked);
       }
    }
    setButtonsOff(modeButtons.keys());
    style.setButtonColor(ui.armButton, QColor(255, 80, 83));
}

void ActionWidget::modeClicked() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    int m = modeButtons.value(buttonSender);
    emit setMode(m);
}
void ActionWidget::armClicked() {
    emit setArm(armed);
}

void ActionWidget::setButtonsOff(QList<QPushButton*> buttonList) {
    for(int i = 0; i < buttonList.size(); i++) {
        style.setButtonDefault(buttonList.at(i));
    }
}

void ActionWidget::toggleArmButton(bool armState) {
    if (armed != armState) {
        armed = armState;
        if (!armed) {
            ui.armButton->setText("DISARMED");
            style.setButtonOff(ui.armButton);
        }
        else {
            ui.armButton->setText("ARMED");
            style.setButtonOn(ui.armButton);
        }
    }
}

void ActionWidget::toggleModeButtons(mavlink_heartbeat_t heartbeat) {
    if (mode != heartbeat.custom_mode) {
        setButtonsOff(modeButtons.keys());
        mode = heartbeat.custom_mode;
        style.setButtonOn(modeButtons.key(heartbeat.custom_mode));
    }
}


