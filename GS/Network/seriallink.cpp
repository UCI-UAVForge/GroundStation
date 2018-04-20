#include "seriallink.h"
#include <QDebug>
#include <QSerialPortInfo>

SerialLink::SerialLink(){

}

void SerialLink::startLink(QString hostport) {
    serialPort = new QSerialPort();
    serialPort->setPortName(hostport);
    serialPort->setBaudRate(QSerialPort::Baud57600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Link started";
    } else {
        emit(connectError(serialPort->errorString()));
        qDebug() << serialPort->errorString();
    }
    connect(serialPort, &QSerialPort::readyRead, this, &SerialLink::recvData);
}
void SerialLink::sendData(mavlink_message_t msg) {
    QByteArray datagram;
    uint8_t buf[MAVLINK_MAX_PAYLOAD_LEN];
    uint8_t len;
    len = mavlink_msg_to_send_buffer(buf, &msg);
    datagram = QByteArray((char*)buf, len);
    if (serialPort->isOpen()) {
        serialPort->write(datagram);
    }
}

void SerialLink::recvData() {
    bool msgReceived = false;
    mavlink_message_t msg;
    mavlink_status_t status;
    QByteArray datagram  = serialPort->readAll();
    for (int i = 0; i < datagram.size(); i++) {
        if(mavlink_parse_char(1, datagram.data()[i], &msg, &status)) {
            msgReceived = true;
            emit messageReceived(msg);
        }
    }
    if (!msgReceived) {
        //QTextStream(stdout) << "Message incomplete" << endl;
    }
}

void SerialLink::closeLink() {
    serialPort->close();
}
