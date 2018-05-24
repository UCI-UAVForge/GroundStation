#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <QObject>
#include "link.h"
#include <QtSerialPort/QSerialPort>
#include "mavlink.h"

class SerialLink : public Link {
public:
    QSerialPort * serialPort;
    SerialLink();
    void startLink(QString hostport);
    void sendData(mavlink_message_t msg);
    void recvData();
    void closeLink();
signals:
   // void messageReceived(mavlink_message_t);

public slots:
};

#endif // SERIALLINK_H
