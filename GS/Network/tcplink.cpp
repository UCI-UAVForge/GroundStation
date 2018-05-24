#include "tcplink.h"

TcpLink::TcpLink()
{

}

void TcpLink::startLink(QString hostport) {
    tcp = new QTcpSocket();
    connect(tcp, &QTcpSocket::readyRead, this, &TcpLink::recvData);
    QStringList hp = hostport.split(':');
    tcp->connectToHost(QHostAddress(hp[0]), hp[1].toInt());
    if (!tcp->isOpen()) {
        emit(connectError(tcp->errorString()));
    } else {
        qDebug() << "Link started";
    }
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

void TcpLink::closeLink() {
    tcp->close();
}
