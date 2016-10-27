#ifndef SERVER_H
#define SERVER_H

#include <QUdpSocket>
#include <QHostAddress>

class Server: public QObject
{
    Q_OBJECT
     public:
        Server();
        void initSocket();
        void readPendingDatagrams();
        ~Server();
    private:
        QUdpSocket* sender;
        QUdpSocket* getter;
        QHostAddress host;
        QHostAddress client;
};

#endif // SERVER_H
