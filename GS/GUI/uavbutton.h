#ifndef UAVBUTTON_H
#define UAVBUTTON_H

#include <QWidget>
#include <QPropertyAnimation>
#include "mavlink.h"
#include <QGraphicsColorizeEffect>
#include "QTime"
#include "QTimer"
#include "connectionwidget.h"
#include "style.h"

namespace Ui {
class UAVButton;
}

class UAVButton : public QWidget
{
    Q_OBJECT

public:
    explicit UAVButton(QWidget *parent = 0);
    ~UAVButton();
    Style style;
    void updateBattery(mavlink_sys_status_t battery);
    void updateHeartbeat(mavlink_heartbeat_t heartbeat);
    bool downbeat = false;
    QPropertyAnimation * pulse;
    QGraphicsColorizeEffect * eEffect;
    QColor changeColor;
    QTimer * timer;
    int timeoutMS = 3000;
    void timeout();
    void openConnection();
signals:
    void openConn();
    void changeStatus(QString status);
private:
    Ui::UAVButton *ui;
};

#endif // UAVBUTTON_H
