#include "gsserver.h"

GsServer::GsServer()
    :recieveport(30010){
    for (int i = 0; i < 4; ++i){
        addressPartsInt[i] = 0;
    }
}

int GsServer::gss_connect_start(){
    if(!net::InitializeSockets()){
        std::cout << "failed to initialize sockets" << std::endl;
        return 1;
    }

    int port = 30010;

    std::cout << "Enter port number to open" << std::endl;
    std::cin >> port;

    std::cout << "creating socket on port " << port << std::endl;

    //net::Socket socket;

    if (!my_socket.Open(port)){
        std::cout << "fialed to create socket!" << std::endl;
        return 1;
    }

    return 0;

}

void GsServer::gss_recieve_message(){
    net::GS_Address sender;
    unsigned char buffer[BUFSIZ];
    int bytes_read = my_socket.Receive(sender, buffer, sizeof(buffer));
    if(!bytes_read)
        std::cout << "No bytes to read";
        //break;
    std::cout << sender.GetA() << sender.GetB() << sender.GetC() << sender.GetD() << buffer << std::endl;


}
