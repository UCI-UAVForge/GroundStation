#include "loginwidget.h"
#include "ui_loginwidget.h"


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWidget::attemptConnection);
    ui->login->setMaximumWidth(0);
    style = Style();
    style.setButtonOff(ui->loginButton);
    slide = new QPropertyAnimation(ui->login, "maximumWidth");
    connect(slide, &QPropertyAnimation::finished, this, &LoginWidget::toggleSlide);

}

void LoginWidget::toggleSlide() {
    slideout = slideout ? slideout : !slideout;
}

//Attempt to login to interop server
void LoginWidget::attemptConnection() {
    if (!connected) {
        if (!slideout) {
            slide->setDuration(500);
            slide->setEndValue(700);
            slide->start();        //pulse->setEndValue(0);
        }
        else {
            try {
                interop = new Interop(ui->user->text().toStdString(), ui->pass->text().toStdString());
                slide->setDuration(500);
                slide->setEndValue(0);
                slide->start();
                ui->loginButton->setText("INTEROP");
                ui->loginButton->setEnabled(false);
                style.setButtonOn(ui->loginButton);
                emit (loginSuccess(interop));
            }
            catch (QNetworkReply::NetworkError err) {
                qDebug() << "Failure";
                connected = false;
            }
            connected = true;
        }
    }
}

//Interop* LoginWidget::attemptConnection() {
//    if (!connected) {
//        if (!slideout) {
//            slide->setDuration(500);
//            slide->setEndValue(700);
//            slide->start();        //pulse->setEndValue(0);
//        }
//        else {
//            try {
//                interop = new Interop(ui->user->text().toStdString(), ui->pass->text().toStdString());
//                slide->setDuration(500);
//                slide->setEndValue(0);
//                slide->start();
//                ui->loginButton->setText("INTEROP");
//                ui->loginButton->setEnabled(false);
//                style.setButtonOn(ui->loginButton);
//                emit (loginSuccess(interop));
//            }
//            catch (QNetworkReply::NetworkError err) {
//                qDebug() << "Failure";
//                connected = false;
//            }
//            connected = true;
//            return interop;
//        }
//    }
//}

void LoginWidget::updateGPS(mavlink_gps_raw_int_t gps) {
    UAVlat = (float)gps.lat/10000000;
    UAVlon = (float)gps.lon/10000000;
    if (connected)
        interop->sendTelemetry(UAVlat, UAVlon, toFeet(UAValt), UAVheading);
}

void LoginWidget::updatePOS(mavlink_global_position_int_t g_pos) {
    UAValt = g_pos.alt / 1000; // Change to relative_alt if needed
    UAVheading = (float)g_pos.hdg / 100;
}

float LoginWidget::toFeet(float meters) {
    return meters * 3.28084;
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
