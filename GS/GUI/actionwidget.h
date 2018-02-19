#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include "udplink.h"
#include "mavlink.h"
#include "ui_actionwidget.h"
#include <QVector>
#include <QMap>
#include <QList>


class ActionWidget : public QWidget
{
    Q_OBJECT
    enum Modes {
        AUTO = 10,
        MANUAL = 0,
        GUIDED = 15,
        CIRCLE = 1,
        STABILIZE = 2,
        FBWA = 5,
        FBWB = 6,
        CRUISE = 7,
        RTL = 11,
        LOITER = 12,
        INITIALISING = 16
    };
public:
    explicit ActionWidget(QWidget *parent = nullptr);
    Ui::ActionWidget ui;
    bool armed;
    uint8_t mode = -1;
    QString activeColor;
    QMap<QPushButton*, int> modeButtons;


    void setButtonColor(QPushButton * button, QString color);
    void setButtonOff(QPushButton * button);
    void setButtonsOff(QList<QPushButton*> buttonList);

    void armClicked();
    void modeClicked();
    void toggleArmButton(mavlink_heartbeat_t heartbeat);
    void toggleModeButtons(mavlink_heartbeat_t heartbeat);

signals:
    void setArm(bool armed);
    void setMode(int mode);

public slots:
};

#endif // ACTIONWIDGET_H
