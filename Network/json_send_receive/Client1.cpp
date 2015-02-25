/*
This is a modified version of the gafferon games program. This program only sends packets and prompts
users for an address to send to, a port to send to and a port to open for sending.
Source: "Networking for Game Programmers" - http://www.gaffer.org/networking-for-game-programmers
*/
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Net.h"

using namespace std;
using namespace net;

using namespace rapidjson;



struct Msg{
std::string  userName;
std::string  msg;
};

struct Coordinates{
double latitude;
double longitude;
};

class jsonObj{
public:
jsonObj();
void addMessage(struct Msg);
void addCoordinate(struct Coordinates);

std::string messageExtractString();
std::string coordinatesExtractString();

private:
std::vector<std::string> varName;
std::vector<std::string> value;
std::vector<double> latitude;
std::vector<double> longitude;
};

jsonObj::jsonObj(){
}

void jsonObj::addMessage(struct Msg command){
//	varName.push_back("userName");
varName.push_back(command.userName);
//	value.push_back("value");
value.push_back(command.msg);
}

void jsonObj::addCoordinate(struct Coordinates coordinate)
{
//	std::cout << coordinate.latitude << " " <<  coordinate.longitude << std::endl;
latitude.push_back(coordinate.latitude);
longitude.push_back(coordinate.longitude);
}

std::string jsonObj::messageExtractString(){
std::string jsonMsg;
int varSize = varName.size();
jsonMsg.append("{");
for (int i = 0; i < varSize; i++){
jsonMsg.append("\"");
jsonMsg.append(varName[i]);
jsonMsg.append("\"");
jsonMsg.append(" : \"");
jsonMsg.append(value[i]);
jsonMsg.append("\",");
}
jsonMsg.erase(jsonMsg.length() - 1); //gets rid of the last comma
jsonMsg.append("}");
return jsonMsg;
}

std::string jsonObj::coordinatesExtractString() {
std::string jsonMsg;
int varSize = latitude.size();
jsonMsg.append("{");
for (int i = 0; i < varSize; i++)
{
jsonMsg.append("\"latitude\":");
std::string lat = std::to_string(latitude[i]);

jsonMsg.append(lat);
jsonMsg.append(" , \"longitude\":");
std::string lon = std::to_string(longitude[i]);
jsonMsg.append(lon + ",");
}
jsonMsg.erase(jsonMsg.length() - 1); //gets rid of the last comma
jsonMsg.append("}");
return jsonMsg;
};

int main(int argc, char * argv[])
{
	Coordinates coord;

	jsonObj coordJ;

	coord.latitude = 56.003;
	coord.longitude = 55.993;

	std::cin >> coord.latitude;
	std::cin >> coord.longitude;
	getchar();

	coordJ.addCoordinate(coord);
	std::string coords = coordJ.coordinatesExtractString();
	int len = coords.length();
	char ccoords[1024];
	int i;
	for (i = 0; i < len; i++)
	ccoords[i] = coords[i];
	ccoords[i] = '\0';
	const char* jsonStrC = ccoords;
	std::cout << ccoords << std::endl;

	Document documentC;
	documentC.Parse(jsonStrC);
	StringBuffer bufferC;
	PrettyWriter<StringBuffer> writerC(bufferC);
	documentC.Accept(writerC);

	std::cout << "rapidJson version:" << std::endl;
	std::cout << bufferC.GetString() << std::endl;
	std::cout << documentC["longitude"].GetDouble() << std::endl;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////Network//////////////////////////////////////////////////
	string addressLine;
	string addressParts[4];
	int addressPartsInt[4] = { 0 };
	unsigned int sendPort = 30005;

	cout << "Enter address to send to: ";
	getline(cin, addressLine);
	cout << "Enter port number to send to: ";
	cin >> sendPort;

	stringstream addressStream(addressLine);

    getline(addressStream, addressParts[0], '.');
	getline(addressStream, addressParts[1], '.');
	getline(addressStream, addressParts[2], '.');
	getline(addressStream, addressParts[3], '.');

	for (int i = 0; i < 4; i++)
		addressPartsInt[i] = stoi(addressParts[i]);

	// initialize socket layer

	if (!InitializeSockets())
	{
		printf("failed to initialize sockets\n");
		return 1;
	}

	// create socket

	int port = 30000;

	cout << "Enter port number to open: ";
	cin >> port;

	printf("creating socket on port %d\n", port);

	Socket socket;

	if (!socket.Open(port))
	{
		printf("failed to create socket!\n");
		return 1;
	}

	string to_send = bufferC.GetString();
	char to_send_c[256];
	int sendLen = to_send.length();
	for (i = 0; i < sendLen; i++)
		to_send_c[i] = to_send[i];
	to_send_c[i] = '\0';
	while (true)
	{
		//char data[256];

		//cin.getline(data, 256);
		Address addra = Address(addressPartsInt[0], addressPartsInt[1], addressPartsInt[2], addressPartsInt[3], sendPort);

		socket.Send(addra, to_send_c, sizeof(to_send_c));


		wait(0.25f);
	}


	// shutdown socket layer

	ShutdownSockets();

	return 0;
}
