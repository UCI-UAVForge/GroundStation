#ifndef LINK_H
#define LINK_H

#include "mavlink.h"
#include <QObject>

class Link: public QObject{
    Q_OBJECT
public:
    virtual void startLink(QString hostport) = 0;
    virtual void sendData(mavlink_message_t msg) = 0;
    virtual void recvData() = 0;
    virtual void closeLink() = 0;
    virtual ~Link(){}

signals:
    void messageReceived(mavlink_message_t msg);
    void connectError(QString errorString);
};

#endif // LINK_H
