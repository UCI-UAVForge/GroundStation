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

class jsonObj{
public:
	jsonObj();
	void addVar(struct Msg);
	std::string extractString();
private:
	std::vector<std::string> varName;
	std::vector<std::string> value;
};

jsonObj::jsonObj(){
}

void jsonObj::addVar(struct Msg command){
//	varName.push_back("userName");
	varName.push_back(command.userName);
//	value.push_back("value");
	value.push_back(command.msg);
}

std::string jsonObj::extractString(){
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
	jsonMsg.erase(jsonMsg.length() - 1);
	jsonMsg.append("}");
	return jsonMsg;
}

int main()
{
	Msg my_message;
	jsonObj jo;

	my_message.userName = "Steve";
	my_message.msg = "Hello!";

	std::cout << "Message contains: " << std::endl <<
		my_message.userName << std::endl << my_message.msg << std::endl << std::endl;

	jo.addVar(my_message);

	const char* jsonStr = jo.extractString().data();

	std::cout << "Json string: " << std::endl << jsonStr << std::endl;
	rapidjson::Document document;
	document.Parse(jsonStr);

	rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<StringBuffer> writer(buffer); //Pretty Optional
	document.Accept(writer);;
	std::cout << "rapidjson version:" << std::endl;
	std::cout << buffer.GetString() << std::endl;
	std::cout << document["Steve"].GetString() << std::endl;

	return 0;
}


