#ifndef INFOWIDGET_H
#define INFOWIDGET_H


#include <QWidget>
#include "mavlink.h"
#include "ui_movementwidget.h"
#include <QHBoxLayout>
#include <QDebug>

class MovementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MovementWidget(QWidget *parent = nullptr);
    QGridLayout *layout;
    Ui::MovementWidget ui;
    void mousePressEvent(QMouseEvent *) override;

signals:

public slots:
    void updateTelemetry(mavlink_gps_raw_int_t gps);
    void updateAttitude(mavlink_attitude_t att);
    void updateLocalPosition(mavlink_local_position_ned_t l_pos);
};

#endif // INFOWIDGET_H
