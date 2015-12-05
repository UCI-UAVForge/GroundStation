#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<winsock2.h>
#include <iostream>
#include <string>
#include <chrono>
#include <stdint.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#include "Packet.h"
#include "AckPacket.h"
#include "ActionPacket.h"
#include "InfoPacket.h"
#include "TelemetryPacket.h"

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

using namespace std; 

int main()
{
	SOCKET Rec_Socket = INVALID_SOCKET;
	struct sockaddr_in server, s_other;
	WSADATA wsa;

	char recbuf[BUFLEN];
	char telbuf[BUFLEN];
	int recbuflen = 0, slen;
	long len = BUFLEN;

	slen = sizeof(s_other);

	/*Initializing Winsock*/
	printf("Initializing UAV server simulation\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Error at startup: %ld\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	printf("Startup successful!\n");

	/*Setup sockets*/
	if ((Rec_Socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Error at socket: %ld\n", WSAGetLastError());
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	printf("Socket creation successful!\n");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	/*Bind sockets*/
	if (bind(Rec_Socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Error at binding: %ld\n", WSAGetLastError());
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	puts("Bind Sucessful!");

	while (1)
	{
		printf("Waiting for packets...");
		using namespace std::chrono;
		auto ep = high_resolution_clock::from_time_t(0);
		auto now = high_resolution_clock::now();
		fflush(stdout);
		Protocol::Packet* packet;

		
		/*Clear the buffer*/
		memset(recbuf, 0, BUFLEN);

		/*Receive data packets*/
		/*Used code from Jordan's network listener to receive packets*/
		char packets[16];

		if (recbuflen = recvfrom(Rec_Socket, packets, 16, 0, (struct sockaddr *)&s_other, &slen) == SOCKET_ERROR)
		{
			printf("recfrom() failed with error code : ", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		std::cout << packets << std::endl;
		int numOfPackets;
		try {
			numOfPackets = std::stoi(packets);
		}
		catch (std::invalid_argument) {
			numOfPackets = 0;
			std::cout << "Bad message format recieved" << std::endl;
		}
		std::cout << numOfPackets << "packets incoming" << std::endl;
		long numbytes = 0;
		for (int i = 0; i < numOfPackets; i++) {
			long bytes = 0;
			if ((bytes = recv(Rec_Socket, recbuf, len - 1, 0)) == -1) {
				perror("recv");
				return 0;
			}
			recbuflen = bytes; 
			std::cout << "Reciving " << bytes << " bytes: " << recbuf << std::endl;
			numbytes += bytes;
		}
		//printf("Received packets from %s:%d\n", inet_ntoa(s_other.sin_addr), ntohs(s_other.sin_port));

		packet = Protocol::Packet::Parse((uint8_t *)recbuf, len-1);
		printf("Data received: %s", packet->GetBytes((uint8_t *)recbuf, len - 1));

		/*Sends telemetry packet every 200 millis.*/
		if (duration_cast<milliseconds>(now - ep).count() == 200)
		{
			Protocol::TelemetryPacket telpacket;
			strcpy(telbuf, recbuf);
			telpacket.GetBytes((uint8_t *) telbuf, len - 1); 
			if (sendto(Rec_Socket, telbuf, recbuflen, 0, (struct sockaddr *)&s_other, slen) == SOCKET_ERROR)
			{
				printf("Telemetry Packet send failed with error code: ", WSAGetLastError());
			}
		}
		/*Once packet is parsed. Sends back data depending on packet type*/
		if (sendto(Rec_Socket, recbuf, recbuflen, 0, (struct sockaddr *)&s_other, slen) == SOCKET_ERROR)
		{
			printf("Packet send failed with error code: ", WSAGetLastError());
		}

		if (strcmp(packets, "init"))
		{
			printf("Sending coordinates");
			/*Add equivalent function for QCreator based sendCoordinates() */
		}
		/*else if (split on comma = 3 elements)
		{
			logTelemetry(recbuf); equivalent
		}
		*/
		closesocket(Rec_Socket);
		WSACleanup();

		return 0; 


		


	}


}