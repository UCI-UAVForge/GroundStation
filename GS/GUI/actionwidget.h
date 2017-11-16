#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include "udplink.h"
#include "mavlink.h"
#include "ui_actionwidget.h"
#include <QVector>

class ActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ActionWidget(QWidget *parent = nullptr);
    Ui::ActionWidget ui;
    UdpLink * link;
    void setLink(UdpLink * link);
    bool armed;
    uint8_t mode = -1;
    QVector<QPushButton*> modeButtons;

    void setButtonOn(QPushButton * button);
    void setButtonOff(QPushButton * button);
    void setButtonsOff(QVector<QPushButton*> buttonList);

    void setArm();
    void setManual();
    void setGuided();
    void setAuto();

    void toggleArmButton();
    void armFailed();
    void toggleModeButtons(mavlink_heartbeat_t heartbeat);
signals:

public slots:
};

#endif // ACTIONWIDGET_H