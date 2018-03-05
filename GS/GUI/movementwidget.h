#ifndef INFOWIDGET_H
#define INFOWIDGET_H


#include <QWidget>
#include "mavlink.h"
#include "ui_movementwidget.h"
#include <QHBoxLayout>
#include "uav.h"
#include <QDebug>

class MovementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MovementWidget(QWidget *parent = nullptr);
    ~MovementWidget();
    QGridLayout *layout;
    Ui::MovementWidget ui;
    void mousePressEvent(QMouseEvent *) override;
private:
    UAV * uav;

signals:

public slots:
    void updateTelemetry(mavlink_vfr_hud_t vfr_hud);
    void updateAttitude(mavlink_attitude_t att);
    void updateGlobalPosition(mavlink_global_position_int_t g_pos);
};

#endif // INFOWIDGET_H
