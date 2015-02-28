#include "gsclient.h"


GsClient::GsClient()
    :sendport(30005){
    for (int i = 0; i < 4; ++i){
        addressPartsInt[i] = 0;
    }
    std::cout << "Please dont devour my mortal soul" << std::endl;
}

int GsClient::gsc_connect_start(){
    std::string addressLine;
    std::string addressParts[4];
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

    int port = 30001;

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
    char data[BUFSIZ];
    strcpy(data, "Mortal soul devaoured");

   // std::cin.getline(data , BUFSIZ);
    net::GS_Address myAddress = net::GS_Address(addressPartsInt[0], addressPartsInt[1],
            addressPartsInt[2], addressPartsInt[3], sendport);

    my_socket.Send(myAddress , data, sizeof(data));

}

void GsClient::gsc_close_connection(){
    net::ShutdownSockets();
}

