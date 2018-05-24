#include "style.h"

Style::Style(){
}

void Style::setButtonColor(QPushButton * button, QColor color) {
   button->setStyleSheet("QPushButton{background-color: " + color.name() + "} "
                         "QPushButton:pressed{background-color: " + color.lighter(145).name() + "} "
                         "QPushButton:hover:!pressed{background-color: " + color.lighter(120).name() + "}");
}

void Style::setButtonOff(QPushButton * button) {
    setButtonColor(button, QColor(255, 80, 83));
}

void Style::setButtonDefault(QPushButton * button) {
    setButtonColor(button, QColor(60,60,60));
}

void Style::setButtonOn(QPushButton * button) {
    setButtonColor(button, QColor(60,200,103));
}
