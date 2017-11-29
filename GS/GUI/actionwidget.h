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
    bool armed;
    uint8_t mode = -1;
    QVector<QPushButton*> modeButtons;

    void setButtonColor(QPushButton * button, QString color);
    void setButtonOff(QPushButton * button);
    void setButtonsOff(QVector<QPushButton*> buttonList);

    void armClicked();
    void toggleArmButton(mavlink_heartbeat_t heartbeat);
    void toggleModeButtons(mavlink_heartbeat_t heartbeat);

signals:
    void setArm(bool armed);
    void setManual();
    void setAuto();
    void setGuided();

public slots:
};

#endif // ACTIONWIDGET_H
