#ifndef STATUS_WIDGET_H
#define STATUS_WIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "textbox.h"
#include "mavlink.h"
#include "ui_statuswidget.h"
#include "udplink.h"

class StatusWidget : public QWidget
{
    Q_OBJECT
public:
    /// \brief Default constructor. Takes no arguments.
    explicit StatusWidget(QWidget* parent=0);
    Ui::StatusWidget ui;
    UdpLink * link;
    void setLink(UdpLink * l);

public slots:
    void updateBattery(mavlink_battery_status_t battery);
    void updateHeartbeat(mavlink_heartbeat_t heartbeat);

};
#endif
