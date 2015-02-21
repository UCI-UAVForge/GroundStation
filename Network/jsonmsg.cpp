#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "rapidjson/prettywriter.h"
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
	for(int i = 0 ; i < varSize;i++)
	{
		jsonMsg.append("\"latitude\":");
		std::string lat = std::to_string(latitude[i]);

		jsonMsg.append(lat);
		jsonMsg.append(" , \"longitude\":");
		std::string lon = std::to_string(longitude[i]);
		jsonMsg.append(lon+",");
	}
	jsonMsg.erase(jsonMsg.length() - 1); //gets rid of the last comma
	jsonMsg.append("}");
	return jsonMsg;
};


int main()
{

	Coordinates coord;

	jsonObj coordJ;

	coord.latitude=9000.00;
	coord.longitude=69696.69;

	coordJ.addCoordinate(coord);
	const char* jsonStrC = coordJ.coordinatesExtractString().data();

	Document documentC;
	documentC.Parse(jsonStrC);
	StringBuffer bufferC;
	PrettyWriter<StringBuffer> writerC(bufferC);
	documentC.Accept(writerC);

	std::cout << "rapidJson version:" << std::endl;
	std::cout << bufferC.GetString() << std::endl;
	std::cout << documentC["longitude"].GetDouble() << std::endl;

//	Msg my_message;
//	jsonObj jo;
//	my_message.userName = "Steve";
//	my_message.msg = "Hello!";
//	std::cout << "Message contains: " << std::endl <<
//		my_message.userName << std::endl << my_message.msg << std::endl << std::endl;
//
//	jo.addMessage(my_message);
//	const char* jsonStr = jo.messageExtractString().data();
//	std::cout << jsonStrC;
//	std::cout << "Json string: " << std::endl << jsonStr << std::endl;
//	rapidjson::Document document;
//	document.Parse(jsonStr);
//	rapidjson::StringBuffer buffer;
//    rapidjson::PrettyWriter<StringBuffer> writer(buffer); //PrettyWriter Optional
//	document.Accept(writer);
//	std::cout << "rapidjson version:" << std::endl;
//	std::cout << buffer.GetString() << std::endl;
//	std::cout << document["Steve"].GetString() << std::endl;

	return 0;
}


