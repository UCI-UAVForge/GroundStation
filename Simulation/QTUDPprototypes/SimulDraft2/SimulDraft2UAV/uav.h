#ifndef UAV_H
#define UAV_H

#include <QObject>
#include <QUdpSocket>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>

class UAV : public QObject
{
    Q_OBJECT
public:
    UAV(QWidget *parent = 0);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocket;

signals:

public slots:
};

#endif // UAV_H
