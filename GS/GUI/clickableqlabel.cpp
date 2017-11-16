#include "clickableqlabel.h"

clickableQLabel::clickableQLabel() : QLabel()
{

}

void clickableQLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
