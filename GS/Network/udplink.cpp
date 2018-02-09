#include "udplink.h"


UdpLink::UdpLink() {
}

int UdpLink::getPort() {
   return UAV_PORT;
}

QHostAddress UdpLink::getHost() {
    return UAV_HOST;
}

void UdpLink::startLink(QString hostport) {
    recvUdpSocket = new QUdpSocket(this);
    sendUdpSocket = new QUdpSocket(this);
    recvUdpSocket->bind(GCS_PORT);
    QStringList hp = hostport.split(':');
    if (hp.length() == 2)
        sendUdpSocket->connectToHost(QHostAddress(hp[0]), hp[1].toInt());
    qDebug() << hp[0];
    if (!sendUdpSocket->isOpen()) {
        emit(connectError(sendUdpSocket->errorString()));
    } else {
        qDebug() << "Link started";
    }
    connect(recvUdpSocket, &QUdpSocket::readyRead,
                this, &UdpLink::recvData);

}

void UdpLink::sendAllMAVLinkMsgs(std::queue<mavlink_message_t> packets) {
    int size = packets.size();
    QTextStream(stdout) << "The size of the vector is " << size << endl;
    for(int i = 0; i < size; ++i) {
       // sendMsg(packets.front());
        packets.pop();
    }
}

void UdpLink::sendAllMAVLinkMsgs(std::vector<mavlink_message_t> packets) {
    QTextStream(stdout) << "The size of the vector is " << packets.size() << endl;
    //for(auto i = packets.begin(); i != packets.end(); ++i)
       // sendMsg(*i);
}

void UdpLink::sendData(mavlink_message_t msg) {
    QByteArray datagram;
    uint8_t buf[MAVLINK_MAX_PAYLOAD_LEN];
    uint8_t len;
    //Put mavlink message in buf
    len = mavlink_msg_to_send_buffer(buf, &msg);
    //Put buf in QByteArray datagram
    datagram = QByteArray((char*)buf, len);

    //Send datagram through sendUdpSocket
    sendUdpSocket->write(datagram.data(), datagram.size());
}

void UdpLink::recvData() {
    while (recvUdpSocket->hasPendingDatagrams()) {
        //Initialize vars for receiving message
        QByteArray datagram;
        mavlink_message_t msg;
        mavlink_status_t status;
        bool msgReceived = false;
        //Resize datagram and read data from recvUdpSocket
        datagram.resize(recvUdpSocket->pendingDatagramSize());
        recvUdpSocket->readDatagram(datagram.data(), datagram.size());
        //Parse using mavlink library
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
}

void UdpLink::closeLink() {
    sendUdpSocket->close();
    recvUdpSocket->close();
}


