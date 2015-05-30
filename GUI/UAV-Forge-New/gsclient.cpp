#include "gsclient.h"
#include "jsonobject.h"
#include <QQueue>

using namespace std;
using namespace net;
using namespace rapidjson;

//Initiates port for sending to 30005 and the array for address to 0
GsClient::GsClient()
    :sendport(30005){
    for (int i = 0; i < 4; ++i){
        addressPartsInt[i] = 0;
    }
}

// Sets list of coordinate to cl
void GsClient::set_list(QList<QPair<double , double > > cl){
    cor_list = cl;
}

// Receive coordinates cl to put into a queue of coordinates
// A helper function to gsc_send_message(); Input is field cor_list    
void GsClient::getCoordinates(QList<QPair<double, double> > cl){

    QQueue<Coordinates> cor_queue;
    jsonObj coordJ;
    // Transfer elements of cl to the queue cor_queue
    Coordinates tempC;
    for(QPair<double,double> pair : cl){
        tempC.latitude = pair.first;
        tempC.longitude = pair.second;
        cor_queue.enqueue(tempC);
    }

    // Transfer cor_queue elements to the jsonObj coordj
    while(!cor_queue.empty())
        coordJ.addCoordinate(cor_queue.dequeue());

    // Receive coordinates in JSON format
    std::string coords = coordJ.coordinatesExtractString();
    // Converts the string coords to C-string
    size_t len = coords.length();
    char ccoords[4096];
    int i;
    for (i = 0; i < len; i++)
        ccoords[i] = coords[i];
    ccoords[i] = '\0';
    const char* jsonStrC = ccoords;
    std::cout << ccoords << std::endl;

    // Document Orientated Modeling: have document read JSONobj and then have a writer format the JSONobj onto document
    Document documentC;
    documentC.Parse(jsonStrC);
    PrettyWriter<StringBuffer> writerC(bufferC);
    documentC.Accept(writerC);

    std::cout << "rapidJson version:" << std::endl;
    std::cout << bufferC.GetString() << std::endl;
}


//initialize the connection using hard coded ip address
int GsClient::gsc_connect_start(){
    //hard code ip address and port to send to
    //ip address is split into the four parts of an ip address
    //e.g. part0.part1.part2.part3
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

    std::cout << "creating socket on port" <<  port << std::endl;

    if (!my_socket.Open(port))
    {
        std::cout << "failed to create socket!" << std::endl;
        return 1;
    }

    return 0;

}

void GsClient::gsc_send_message(){
    getCoordinates(cor_list);
    //convert string from json string buffer to c string
    //"Send" function uses c function "sendto" which only accepts c strings
    string to_send = bufferC.GetString();
    char to_send_c[BUFSIZ];
    size_t sendLen = to_send.length();
    int i;
    for (i = 0; i < sendLen; i++)
        to_send_c[i] = to_send[i];
    to_send_c[i] = '\0';
    std::cout << to_send_c << std::endl;

    //assign ip address and send the coordinates
        net::GS_Address addra = net::GS_Address(addressPartsInt[0], addressPartsInt[1], addressPartsInt[2],            addressPartsInt[3], sendport);
        my_socket.Send(addra, to_send_c, sizeof(to_send_c));

}
    // Sends the UAV to stop moving physically 
/*void GsClient::sendStopMessage(){
    bufferC << "Empty String";
    qDebug() << bufferC;
    string to_send = bufferC.GetString();
    char to_send_c[BUFSIZ];
    int sendLen = to_send.length();
    int i;
    for (i = 0; i < sendLen; i++)
        to_send_c[i] = to_send[i];
    to_send_c[i] = '\0';
    std::cout << to_send_c << std::endl;
    char buffer[BUFSIZ];
    //int recvBytes = 0;
    for(int i = 0; i < 100; i++) {
        net::GS_Address addra = net::GS_Address(addressPartsInt[0], addressPartsInt[1], addressPartsInt[2], addressPartsInt[3], sendport);
        // Address sender;
        strcpy(buffer, "Mortal soul devoured.");
        my_socket.Send(addra, to_send_c, sizeof(to_send_c));
    }
}*/

//close the socket connection
void GsClient::gsc_close_connection(){
    net::ShutdownSockets();
}
