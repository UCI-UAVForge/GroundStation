
#include <uavcon.h>

GsServer::GsServer()
    :recieveport(30010){
    for (int i = 0; i < 4; ++i){
        addressPartsInt[i] = 0;
    }
}

int GsServer::connect_start(){
    if(!net::InitializeSockets()){
        std:cout << "failed to initialize sockets" << std::endl;
        return 1;
    }

    int port = 30010;

    std::cout << "Enter port number to open" << std::endl;
    std::cin >> port;

    std::cout << "creating socket on port " << port << std::endl;

    net::Socket socket;

    if (!net::socket.Open(port)){
        std::cout << "fialed to create socket!" << std::endl;
        return 1;
    }

    return 0;

}

void GsServer::recieve_message(){
    net::Address sender;
    unsigned char buffer[BUFSIZ];
    int bytes_read = net::socket.Recieve(sender, buffer, sizeof(buffer));
    if(!byte_read)
        break;
    std::cout << sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(), buffer << std::endl;


}

GsClient::GsClient()
    :sendport(30005){
    for (int i = 0; i < 4; ++i){
        addressPartsInt[i] = 0;
    }
}

int GsClient::connect_start(){
    std::string addressLine;
    std::string addressParts[4];
//    int addressPartsInt[4] = {0};
//    unsigned int sendport = 30005;

    std::cout << "Enter address to send: ";
    getline(cin, addressline);
    std::cout << "Enter port number to send to";
    std::cin >> sendPort;

    std::stringstream addressStream(addressLine);

    std::getline(addressStream, addressParts[0], '.');
    std::getline(addressStream, addressParts[1], '.');
    std::getline(addressStream, addressParts[2], '.');
    std::getline(addressStream, addressParts[3], '.');


    for (int i = 0; i < 4; i++)
        addressPartsInt[i] = std::stoi(addressParts[i]);

    // initialize socket layer

    if (!InitializeSockets())
    {
        std::cout << "failed to initialize sockets" << std::endl;
        return 1;
    }

    // create socket

    int port = 30000;

    std::cout << "Enter port number to open: ";
    std::cin >> port;

    std::cout << "creating socket on port" <<  port << std::endl;

    Socket socket;

    if (!socket.Open(port))
    {
        std::cout << "failed to create socket!" << std::endl;
        return 1;
    }

    return 0;

}

void GsClient::send_message(){
    char data[BUFSIZ];

    cin.getline(data , BUFSIZ);

    net::socket.Send(net::Address((addressPartsInt[0], addressPartsInt[1],
                addressPartsInt[2], addressPartsInt[3], sendPort), data, sizeof(data)));

}

void GsClient::close_connection(){
    net::ShutdownSockets();
}
