#ifndef STATUS_WIDGET_H
#define STATUS_WIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "mavlink.h"
#include "ui_statuswidget.h"
#include "link.h"

class StatusWidget : public QWidget
{
    Q_OBJECT
public:
    /// \brief Default constructor. Takes no arguments.
    explicit StatusWidget(QWidget* parent=0);
    Ui::StatusWidget ui;
    Link * link;
    QTimer * timer;
    void setLink(Link * l);

public slots:
    void timeout();
    void updateBattery(mavlink_battery_status_t battery);
    void updateHeartbeat(mavlink_heartbeat_t heartbeat);

};
#endif
