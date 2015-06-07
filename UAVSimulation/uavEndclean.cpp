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

struct Coordinates{
	double latitude;
	double longitude;
};

//class to store points and make JSON array of objects, with each object containing latitude and longitude.
class jsonObj{
public:
	jsonObj();
	void addCoordinate(struct Coordinates);
	std::string coordinatesExtractString();

private:
	std::vector<double> latitude;
	std::vector<double> longitude;
};

jsonObj::jsonObj(){
}

//adds latitudes and longitudes to their respective vectors
void jsonObj::addCoordinate(struct Coordinates coordinate)
{
	//	std::cout << coordinate.latitude << " " <<  coordinate.longitude << std::endl;
	latitude.push_back(coordinate.latitude);
	longitude.push_back(coordinate.longitude);
}

//makes JSON array of objects
std::string jsonObj::coordinatesExtractString() {
	std::string jsonMsg;
	std::stringstream ss;
	size_t varSize = latitude.size();
	jsonMsg.append("[");
	for (int i = 0; i < varSize; i++)
	{
		jsonMsg.append("{\"latitude\":");
		ss << latitude[i];
		//        std::string lat = std::to_string(latitude[i]);

		jsonMsg.append(ss.str());
		jsonMsg.append(" , \"longitude\":");
		//        std::string lon = std::to_string(longitude[i]);
		ss.str("");
		ss << longitude[i];
		jsonMsg.append(ss.str() + "},");
		ss.str("");
	}
	jsonMsg.erase(jsonMsg.length() - 1); //gets rid of the last comma
	jsonMsg.append("]");
	return jsonMsg;
};

int main(int argc, char * argv[])
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////Network/////////////////////////////////////////////////////

	// initialize socket layer

	if (!InitializeSockets())
	{
		printf("failed to initialize sockets\n");
		return 1;
	}

	// create socket

	//hard coded port number
	int port = 30010;

	printf("creating socket on port %d\n", port);

	Socket socket;

	if (!socket.Open(port))
	{
		printf("failed to create socket!\n");
		return 1;
	}


	int bytes_read = 0, buflen = 0; //need buflen because linux sends "0" bytes no matter what
	char buffer[BUFSIZ];
	buffer[0] = '\0';
	char fullbuff[65536];
	char awkBuf[BUFSIZ];
	strcpy(awkBuf, "UAVCOORDRECVD");
	Address sender;
	//receive json string from sender
	while (bytes_read == 0 && buflen == 0){
		bytes_read = socket.Receive(sender, buffer, sizeof(buffer));
		buflen = strlen(buffer);
		if (socket.Send(sender, awkBuf, sizeof(awkBuf)))
			std::cout << "sent awknoledgement" << std::endl;
	}

		//std::cout << "Coordinates received: " << buffer << std::endl;
		//////////////////////////////////////test coordinates//////////////////////////////
		//Coordinates c;
		//c.latitude = 5.0001;
		//c.longitude = 666.0;
		//jsonObj jo;
		//jo.addCoordinate(c);
		//std::string coords = jo.coordinatesExtractString();
		//int len = coords.length();
		//char ccoords[1024];
		//int i;
		//for (i = 0; i < len; i++)
		//	ccoords[i] = coords[i];
		//ccoords[i] = '\0';


		///////////////////////////////////////////////////////////////////////////////////

		const char* jsonCoord = buffer; //for actual received coordinates
		//const char* jsonCoord = ccoords; //for test coordinates

		//store received json string into iterateble object
		Document documentC;
		documentC.Parse(jsonCoord);
		StringBuffer bufferC;
		PrettyWriter<StringBuffer> writerC(bufferC);
		documentC.Accept(writerC);

		//iterate through received json string and store lat. and lon. into array of coordinate structs
		Coordinates coord[1000];
		int docSize = documentC.Size();
		for (int i = 0; i < docSize; i++){
			coord[i].latitude = documentC[i]["latitude"].GetDouble();
			coord[i].longitude = documentC[i]["longitude"].GetDouble();
		}

		//print out values of array of coordinate structs
		for (int i = 0; i < docSize; i++){
			std::cout << "longitude value " << i << " is: " << coord[i].longitude << std::endl;
			std::cout << "latitude value " << i <<  " is : " << coord[i].latitude << std::endl;
		}

		////////////////Sending back coordinates not fully functional//////////////////////////

		// rapidjson::StringBuffer sb;
		// rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

		// //std::cout << "Getting one coordinate from json string in json format: " << sb.GetString() << std::endl;
		// std::string bufStr;
		// int bufStrLen = 0;
		// bool uavStopped = false; //placeholder for some sort of status from uav indicating that it has stopped/disconnected/etc.
		// for (int i = 0; i < docSize; i++){
		// 	memset(buffer, '/0', sizeof(buffer));
		// 	documentC[i].Accept(writer);
		// 	bufStr = sb.GetString();
		// 	bufStrLen = bufStr.length();
		// 	int j;
		// 	for (j = 0; j < bufStrLen; j++)
		// 		buffer[j] = bufStr[j];
		// 	buffer[j] = '\0';
		// 	std::cout << "Sent this thing: " << buffer << std::endl;
		// 	socket.Send(sender, buffer, sizeof(buffer));
		// 	std::cout << "Yo, hello... HEY" << std::endl;
		// 	std::cout << bufStr << std::endl;
		// 	writer.Reset(sb);
		// 	sb.Clear();
			
		// 	wait(2);

		// }
		// memset(awkBuf, '\0', sizeof(awkBuf));
		// strcpy(awkBuf, "UAVFINISHED");
		// socket.Send(sender, awkBuf, sizeof(awkBuf));
		// std::cout << "Finished sending back coordinates" << std::endl;


		// system("PAUSE");

		//////////////////////////////////////////////////////////////////////////////////////



	// shutdown socket layer

	ShutdownSockets();

	return 0;
}
