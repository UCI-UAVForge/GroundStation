#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "interop.h"

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
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;
signals:
    void loginSuccess(Interop * interop);

};

#endif // LOGINWIDGET_H
