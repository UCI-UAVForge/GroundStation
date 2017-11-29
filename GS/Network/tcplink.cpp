#include "tcplink.h"

TcpLink::TcpLink()
{

}

void TcpLink::startLink() {
    tcp = new QTcpSocket();
    connect(tcp, &QTcpSocket::readyRead, this, &TcpLink::recvData);
    tcp->connectToHost(QHostAddress("127.0.0.1"), 5760);
}

void TcpLink::sendData(mavlink_message_t msg) {
    QByteArray datagram;
    uint8_t buf[MAVLINK_MAX_PAYLOAD_LEN];
    uint8_t len;
    //Put mavlink message in buf
    len = mavlink_msg_to_send_buffer(buf, &msg);
    //Put buf in QByteArray datagram
    datagram = QByteArray((char*)buf, len);
    if (tcp->waitForConnected()) {
        tcp->write(datagram);
        qDebug() << "wrote data";
    }
}

void TcpLink::recvData() {
    bool msgReceived = false;
    QByteArray datagram = tcp->readAll();
    mavlink_message_t msg;
    mavlink_status_t status;
    for (int i = 0; i < datagram.size(); i++) {
        if(mavlink_parse_char(1, datagram.data()[i], &msg, &status)) {
            msgReceived = true;
            emit messageReceived(msg);
        }
    }
    if (!msgReceived) {
        QTextStream(stdout) << "Message incomplete" << endl;
    }
}
