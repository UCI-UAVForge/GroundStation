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
//    Interop* attemptConnection();

    bool slideout = false;
    bool connected = false;
    QPropertyAnimation * slide;
    void toggleSlide();

    Style style;
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;
    float toFeet(float meters);
    float UAVlat;
    float UAVlon;
    float UAValt;
    float UAVheading;
//    bool ongoingMission;
signals:
    void loginSuccess(Interop * interop);

public slots:
    void updateGPS(mavlink_gps_raw_int_t gps);
    void updatePOS(mavlink_global_position_int_t g_pos);
//    void missionChange(bool change);

};

#endif // LOGINWIDGET_H
