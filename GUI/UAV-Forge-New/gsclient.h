#ifndef GSCLIENT_H
#define GSCLIENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "net.h"


class GsClient{
public:
    GsClient();
    int gsc_connect_start();
    void gsc_send_message();
    void gsc_close_connection();

private:
    int addressPartsInt[4];
    unsigned int sendport;
    net::GS_Socket my_socket;


};

#endif // GSCLIENT_H

