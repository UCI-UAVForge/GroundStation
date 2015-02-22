#ifndef UAVCON_H
#define UAVCON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "net.h"

class GsClient{
public:
    GsClient();
    int connect_start();
    void send_message();
    void close_connection();

private:
    int addressPartsInt[4];
    unsigned int sendport;
    net::Socket socket;


};

class GsServer {
public:
    GsServer();
    int connect_start();
    void recieve_message();
    void close_connection();

private:
     int addressPartsInt[4];
     unsigned int recieveport;


};

#endif // UAVCON_H

