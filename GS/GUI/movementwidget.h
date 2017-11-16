#ifndef INFOWIDGET_H
#define INFOWIDGET_H


#include <QWidget>
#include "textbox.h"
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
    TextBox *alt, *lon, *lat, *vel, *pitch, *roll, *yaw;
    Ui::MovementWidget ui;

    void mousePressEvent(QMouseEvent *) override;

signals:

public slots:
    void updateTelemetry(mavlink_gps_raw_int_t gps);
    void updateAttitude(mavlink_attitude_t att);
};

#endif // INFOWIDGET_H
