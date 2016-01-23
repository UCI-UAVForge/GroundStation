#include "gsserver.h"
#include <errno.h>
#include <signal.h>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <winsock.h>
#include <windows.h>

#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#include<Ws2tcpip.h>
#include<signal.h>

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46
#endif

void GsServer::waitNet(unsigned millis){
  Sleep(millis);
}
#else
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
void GsServer::waitNet(unsigned millis){
    usleep(millis * 1000);
}
#endif

#define BACKLOG 10   // how many pending connections queue will hold

#define BUFSIZE 256

char listenPort[10];  // the port users will be connecting to
char sendPort[10];
char buf[BUFSIZE];

//--------

GsServer::GsServer(messagebox *myMessageBox): networkListener(myMessageBox){
    this->myMessageBox = myMessageBox;
    myAddressInt = (127 << 24) | 1;
    port = 3495;
}

GsServer::GsServer(net::GS_Address myAddress, messagebox *myMessageBox): networkListener(myMessageBox){
    this->myMessageBox = myMessageBox;
    myAddressInt = myAddress.GetAddress();
    port = myAddress.GetPort();
}

GsServer::~GsServer(){
    networkListener.stop();
    delete myMessageBox;
    free(this);
}


//--------------

 /*void sigchldHandler()
{
  // waitpid() might overwrite errno, so we save and restore it:
  int saved_errno = errno;
  while(waitpid(-1, NULL, WNOHANG) > 0);
  errno = saved_errno;
}*/
// get sockaddr, IPv4 or IPv6:
void* get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void GsServer::run(){
    openServer();
}

int GsServer::openServer(){
    std::cout<< "Starting Server..." << std::endl;
    unsigned short listenPort = port;
    int sockfd;  // listen on sock_fd, new connection on uav_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    //struct sigaction sa;
    const char yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    if ((rv = getaddrinfo(std::to_string(myAddressInt).c_str(), std::to_string(listenPort).c_str(), &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                           p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                     sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            net::ShutdownSockets();//close(sockfd);
            perror("server: bind");
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo);
    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }
    std::cout<<"Server started with socket: "<<sockfd<<std::endl;
    ///std::cout<<"Waiting for connections..."<<std::endl;
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
    //sa.sa_handler = sigchldHandler; // reap all dead processes
    //sigemptyset(&sa.sa_mask);
    //sa.sa_flags = SA_RESTART;
   // if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    //    perror("sigaction");
    //    exit(1);
   // }

    ///@todo move from this line to end into a seperate accept thread

    std::cout<<"Waiting for connections..."<<std::endl;

    //bool finished = false;
    //while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        uav_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (uav_fd == -1) {
            perror("accept");
            //continue;
        }
        //inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        std::cout << "server: got connection from " << s << std::endl;
        networkListener.setId(uav_fd);
        networkListener.start();
        return 0;
}

void GsServer::formatCoordinatesToSend(char *charArr, int len, QList<QPair<double, double> > coords){
    char returnArr[len];
    int size = 0;
    for(QPair<double, double> pair : coords){
        //qDebug() << "Size: " << size << endl;
        char coord[100];
        if (size + formatCoord(coord, pair) < len-2){
            //strcat(returnArr,coord);
            strcpy(&returnArr[size],coord);
            size = strlen(returnArr);
            returnArr[size++] = ';';
        } else {
            break;
        }
    }
    returnArr[size-1] = '\0';
    strcpy(charArr, returnArr);
}

int GsServer::formatCoord(char *charArr, QPair<double, double> coord){
    double lat = coord.first;
    double lng = coord.second;
    std::string coordString = std::to_string(lat) + "," + std::to_string(lng);
    strcpy(charArr, (coordString).c_str());
    return coordString.length();
}

int GsServer::sendMessage(char *charArr, int len, int packSize, int target){
    std::cout << "Will require " << len/packSize+1 << " packets." << std::endl;
    if (send(target, std::to_string(len/packSize+1).c_str(), 16, 0) == -1){
        perror("send");
        return 4;
        waitNet(5);
    }
    for (int n = 0; n <= len/packSize; n++){
        if (send(target, charArr,packSize, 0) == -1){
            perror("send");
            return 5;
        }
        charArr += packSize;
        waitNet(5);
    }
    return 0;
}
