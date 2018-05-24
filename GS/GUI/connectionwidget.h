#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <QDialog>
#include <QButtonGroup>
#include <QDebug>
#include <QSerialPortInfo>
#include "link.h"
#include "seriallink.h"
#include "tcplink.h"
#include "udplink.h"
#include "style.h"

namespace Ui {
class ConnectionWidget;
}

class ConnectionWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionWidget(QWidget *parent = 0);
    void connectUAV();
    void refresh();
    ~ConnectionWidget();
    QButtonGroup * buttons;
    Ui::ConnectionWidget *ui;
    void setStatus(QString status);

    Style style;

signals:
    void connectTo(Link * newLink, QString hostport);
private:
};

#endif // CONNECTIONWIDGET_H
