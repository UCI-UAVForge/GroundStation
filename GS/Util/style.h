#ifndef STYLE_H
#define STYLE_H

#include <QPushButton>
#include <QColor>

class Style{
public:
    Style();
    void setButtonColor(QPushButton * button, QColor color);
    void setButtonOff(QPushButton * button);
    void setButtonDefault(QPushButton * button);
    void setButtonOn(QPushButton * button);
};

#endif // STYLE_H
