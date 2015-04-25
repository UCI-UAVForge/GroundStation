#ifndef GSSERVER_H
#define GSSERVER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <QPair>

#include "net.h"

class GsServer {
public:
    GsServer();
    int gss_connect_start();
    void gss_recieve_message();
    void gs_close_connection();

private:
     int addressPartsInt[4];
     unsigned int recieveport;
     net::GS_Socket my_socket;

/*signals:
     QPair<double, double> pointRecieved();*/
};
#endif // GSSERVER_H

