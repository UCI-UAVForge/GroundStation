#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "interop.h"
#include "style.h"
#include "mavlink.h"
#include <QTimer>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    Interop * interop;
    void attemptConnection();
    bool slideout = false;
    bool connected = false;
    QPropertyAnimation * slide;
    void toggleSlide();

    Style style;
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;
    float UAVlat;
    float UAVlon;
    float UAValt;
    int UAVheading;
//    bool ongoingMission;
signals:
    void loginSuccess(Interop * interop);

public slots:
    void updateGPS(mavlink_gps_raw_int_t gps);
    void updateVFR(mavlink_vfr_hud_t vfr);
//    void missionChange(bool change);

};

#endif // LOGINWIDGET_H
