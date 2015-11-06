#ifndef GROUNDSTATION_H
#define GROUNDSTATION_H

#include <QObject>
#include <QUdpSocket>

class GroundStation : public QObject
{
    Q_OBJECT
public:
    explicit GroundStation(QObject *parent = 0);
    void initSocket();
    void readPendingDatagrams();

signals:

public slots:

private:
    QUdpSocket* sender;
    QUdpSocket* getter;
    QHostAddress host;
    QHostAddress client;
};

#endif // GROUNDSTATION_H
