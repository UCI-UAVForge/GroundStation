#include "gsclient.h"
#include "jsonobject.h"
#include <QQueue>

using namespace std;
using namespace net;
using namespace rapidjson;

GsClient::GsClient()
    :sendport(30005){
    for (int i = 0; i < 4; ++i){
        addressPartsInt[i] = 0;
    }
    std::cout << "Please dont devour my mortal soul" << std::endl;
}


void GsClient::set_list(QList<QPair<double , double > > cl){
    cor_list = cl;
}


void GsClient::getCoordinates(QList<QPair<double, double> > cl){

    QQueue<Coordinates> cor_queue;
    jsonObj coordJ;

    Coordinates tempC;
    for(QPair<double,double> pair : cl){
        tempC.latitude = pair.first;
        tempC.longitude = pair.second;
        cor_queue.enqueue(tempC);
    }

    while(!cor_queue.empty())
        coordJ.addCoordinate(cor_queue.dequeue());

    std::string coords = coordJ.coordinatesExtractString();
    int len = coords.length();
    char ccoords[4096];
    int i;
    for (i = 0; i < len; i++)
        ccoords[i] = coords[i];
    ccoords[i] = '\0';
    const char* jsonStrC = ccoords;
    std::cout << ccoords << std::endl;

    Document documentC;
    documentC.Parse(jsonStrC);
    PrettyWriter<StringBuffer> writerC(bufferC);
    documentC.Accept(writerC);

    std::cout << "rapidJson version:" << std::endl;
    std::cout << bufferC.GetString() << std::endl;
}



int GsClient::gsc_connect_start(){
    getCoordinates(cor_list);
//    std::string addressLine;
//    std::string addressParts[4];
//    int addressPartsInt[4] = {0};
//    unsigned int sendport = 30005;

//    std::cout << "Enter address to send: ";
//    std::getline(std::cin, addressLine);
//    std::cout << "Enter port number to send to";
//    std::cin >> sendport;

//    std::stringstream addressStream(addressLine);

//    std::getline(addressStream, addressParts[0], '.');
//    std::getline(addressStream, addressParts[1], '.');
//    std::getline(addressStream, addressParts[2], '.');
//    std::getline(addressStream, addressParts[3], '.');


//    for (int i = 0; i < 4; i++)
//        addressPartsInt[i] = std::atoi(addressParts[i].c_str());
    addressPartsInt[0] = 169;
    addressPartsInt[1] = 234;
    addressPartsInt[2] = 63;
    addressPartsInt[3] = 153;
    sendport = 30010;

    // initialize socket layer

    if (!net::InitializeSockets())
    {
        std::cout << "failed to initialize sockets" << std::endl;
        return 1;
    }

    // create socket

    int port = 31100;

//    std::cout << "Enter port number to open: ";
//    std::cin >> port;

    std::cout << "creating socket on port" <<  port << std::endl;

    //net::Socket socket;

    if (!my_socket.Open(port))
    {
        std::cout << "failed to create socket!" << std::endl;
        return 1;
    }

    return 0;

}

void GsClient::gsc_send_message(){
//    char data[4096];
//    strcpy(data, "Mortal soul devaoured");

//   // std::cin.getline(data , BUFSIZ);
//    net::GS_Address myAddress = net::GS_Address(addressPartsInt[0], addressPartsInt[1],
//            addressPartsInt[2], addressPartsInt[3], sendport);

//    my_socket.Send(myAddress , data, sizeof(data));
    string to_send = bufferC.GetString();
    char to_send_c[BUFSIZ];
    int sendLen = to_send.length();
    int i;
    for (i = 0; i < sendLen; i++)
        to_send_c[i] = to_send[i];
    to_send_c[i] = '\0';
    std::cout << to_send_c << std::endl;
    char buffer[BUFSIZ];
   // int recvBytes = 0;

    for(int i = 0; i < 100; i++)
    {
        //char data[256];

        //cin.getline(data, 256);
        net::GS_Address addra = net::GS_Address(addressPartsInt[0], addressPartsInt[1], addressPartsInt[2], addressPartsInt[3], sendport);
       // Address sender;
        strcpy(buffer, "Mortal soul devoured.");
    //	recvBytes = socket.Receive(sender, buffer, sizeof(buffer));  //receive currently not working
        my_socket.Send(addra, to_send_c, sizeof(to_send_c));
    }

}

void GsClient::gsc_close_connection(){
    net::ShutdownSockets();
}

