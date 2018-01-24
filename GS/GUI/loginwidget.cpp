#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWidget::attemptConnection);
    ui->login->setMaximumWidth(0);
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
            connected = true;
            try {
                interop = new Interop(ui->user->text().toStdString(), ui->pass->text().toStdString());
                slide->setDuration(500);
                slide->setEndValue(0);
                slide->start();
                ui->loginButton->setText("INTEROP");
                ui->loginButton->setEnabled(false);
                ui->loginButton->setStyleSheet("QPushButton{background-color: rgb(60, 200, 103);}");
                emit (connectionSuccess(interop));
            }
            catch (QNetworkReply::NetworkError err) {
                qDebug() << "Failure";
                connected = false;
            }
        }
    }
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
