#ifndef GSCLIENT_H
#define GSCLIENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <QList>
#include <QPair>
#include "net.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class GsClient{
public:
    GsClient();
    void set_list(QList<QPair<double , double > > cl);
    int gsc_connect_start();
    void gsc_send_message();
    //void sendStopMessage();
    void gsc_close_connection();
    void getCoordinates(QList<QPair<double, double> > cl);

private:
    int addressPartsInt[4];
    unsigned int sendport;
    net::GS_Socket my_socket;
    QList<QPair<double , double > > cor_list;
    rapidjson::StringBuffer bufferC;
};

#endif // GSCLIENT_H

