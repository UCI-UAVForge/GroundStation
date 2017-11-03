#include "link.h"

Link::Link() {
}

void Link::startLink() {
    recvUdpSocket = new QUdpSocket(this);
    sendUdpSocket = new QUdpSocket(this);
    recvUdpSocket->bind(GS_PORT_NUM);
    connect(recvUdpSocket, SIGNAL(readyRead()),
                this, SLOT(processPendingDatagrams()));
    qDebug() << "Link started";
}

void Link::sendAllMAVLinkMsgs(std::queue<mavlink_message_t> packets) {
    int size = packets.size();
    QTextStream(stdout) << "The size of the vector is " << size << endl;
    for(int i = 0; i < size; ++i) {
        sendMAVLinkMsg(packets.front());
        packets.pop();
    }
}

void Link::sendAllMAVLinkMsgs(std::vector<mavlink_message_t> packets) {
    QTextStream(stdout) << "The size of the vector is " << packets.size() << endl;
    for(auto i = packets.begin(); i != packets.end(); ++i)
        sendMAVLinkMsg(*i);
}

void Link::sendMAVLinkMsg(mavlink_message_t msg) {
    QByteArray datagram;
    uint8_t buf[MAVLINK_MAX_PAYLOAD_LEN];

    //Put mavlink message in buf
    mavlink_msg_to_send_buffer(buf, &msg);
    //Put buf in QByteArray datagram
    datagram = QByteArray((char*)buf, MAVLINK_MAX_PAYLOAD_LEN);

    //Send datagram through sendUdpSocket
    sendUdpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::LocalHost, UAV_PORT_NUM);
}

void Link::processPendingDatagrams() {
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


