#include "link.h"


link::link()
{
    recvUdpSocket.bind(UAV_PORT_NUM);
    connect(&recvUdpSocket, SIGNAL(readyRead()),
                this, SLOT(processPendingDatagrams()));
}

void link::sendAllMAVLinkMsgs(std::queue<mavlink_message_t> packets) {
    int size = packets.size();
    QTextStream(stdout) << "The size of the vector is " << size << endl;
    for(int i = 0; i < size; ++i) {
        sendMAVLinkMsg(packets.front());
        packets.pop();
    }
}

void link::sendAllMAVLinkMsgs(std::vector<mavlink_message_t> packets) {
    QTextStream(stdout) << "The size of the vector is " << packets.size() << endl;
    for(auto i = packets.begin(); i != packets.end(); ++i)
        sendMAVLinkMsg(*i);
}

void link::sendMAVLinkMsg(mavlink_message_t msg) {
    QByteArray datagram;
    uint8_t buf[MAVLINK_MAX_PAYLOAD_LEN];

    //Put mavlink message in buf
    mavlink_msg_to_send_buffer(buf, &msg);
    //Put buf in QByteArray datagram
    datagram = QByteArray((char*)buf, MAVLINK_MAX_PAYLOAD_LEN);

    //Send datagram through sendUdpSocket
    sendUdpSocket.writeDatagram(datagram.data(), datagram.size(), QHostAddress::LocalHost, GS_PORT_NUM);
}

void link::processPendingDatagrams() {
    QTextStream(stdout) << "Data received" << endl;
    while (recvUdpSocket.hasPendingDatagrams()) {
        //Initialize vars for receiving message
        QByteArray datagram;
        mavlink_message_t msg;
        mavlink_status_t status;
        //Resize datagram and read data from recvUdpSocket
        datagram.resize(recvUdpSocket.pendingDatagramSize());
        recvUdpSocket.readDatagram(datagram.data(), datagram.size());

        //Parse using mavlink library
        for (int i = 0; i < datagram.size(); i++) {
            if(mavlink_parse_char(1, datagram.data()[i], &msg, &status)) {
                QTextStream(stdout) << "Message received" << endl;
                emit messageReceived(msg);
            }
        }
    }
}

