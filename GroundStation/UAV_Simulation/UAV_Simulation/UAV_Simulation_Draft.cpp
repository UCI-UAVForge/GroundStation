#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

#undef UNICODE

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

#pragma comment (lib, "Ws2_32.lib")



int main()
{
	SOCKET Rec_Socket = INVALID_SOCKET;
	WSADATA wsa; 

	char recbuf[DEFAULT_BUFLEN];
	int recResult, sendResult;
	int recbuflen = DEFAULT_BUFLEN;

	int start_Result = WSAStartup(MAKEWORD(2, 2), &wsa);
	
	if (start_Result != 0)
	{
		printf("WSAStartup failed: %d\n", start_Result);
		return 1; 
	}

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	start_Result = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

	if (start_Result != 0)
	{
		printf("getaddrinfo failed: %d\n", start_Result);
		WSACleanup();
		return 1;
	}



	Rec_Socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (Rec_Socket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1; 
	}

	start_Result = bind(Rec_Socket, result->ai_addr, (int)result->ai_addrlen);
	
	if (start_Result == SOCKET_ERROR)
	{
		printf("bind failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	if (listen(Rec_Socket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(Rec_Socket);
		WSACleanup();
		return 1; 
	}

	SOCKET clientSocket = INVALID_SOCKET;

	clientSocket = accept(Rec_Socket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(Rec_Socket);
		WSACleanup();
		return 1; 
	}
	do
	{
		recResult = recv(clientSocket, recbuf, recbuflen, 0);

		if (recResult > 0)
		{
			printf("Bytes received: %d\n", recResult);

			sendResult = send(clientSocket, recbuf, recResult, 0);
			if (sendResult == SOCKET_ERROR)
			{
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(clientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", sendResult);
		}
		else if (recResult == 0)
		{
			printf("Connection closing...\n");
		}
		else
		{
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(clientSocket);
			WSACleanup();
			return 1; 
		}

	} while (recResult > 0);

	recResult = shutdown(clientSocket, SD_SEND);
	if (recResult == SOCKET_ERROR)
	{
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return 1; 
	}

	closesocket(clientSocket);
	WSACleanup();
	
	return 0; 
}