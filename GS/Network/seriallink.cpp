#include "seriallink.h"
#include <QDebug>

seriallink::seriallink(){

}
void seriallink::startLink() {
    link = new QSerialPort();
    link->setPortName("COM4");
    link->setBaudRate(QSerialPort::Baud9600);
    link->setDataBits(QSerialPort::Data8);
    link->setParity(QSerialPort::NoParity);
    link->setStopBits(QSerialPort::OneStop);
    link->setFlowControl(QSerialPort::NoFlowControl);
    if (link->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected";
    } else {
       qDebug() << "no.";
    }
    connect(link, &QSerialPort::readyRead, this, &seriallink::recvData);
}
void seriallink::sendData(mavlink_message_t msg) {}

void seriallink::recvData() {
    bool msgReceived = false;
    mavlink_message_t msg;
    mavlink_status_t status;
    QByteArray datagram  = link->readAll();// probably have to do with the readall()
    for (int i = 0; i < datagram.size(); i++) { // size of the packet
        if(mavlink_parse_char(1, datagram.data()[i], &msg, &status)) {
            msgReceived = true;
            emit messageReceived(msg);
        }
    }
    if (!msgReceived) {
        //QTextStream(stdout) << "Message incomplete" << endl;
    }
}
