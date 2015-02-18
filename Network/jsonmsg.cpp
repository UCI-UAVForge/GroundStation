#include<iostream>
#include<string>
#include<vector>

struct Msg{
	std::string userName;
	std::string msg;
};

class jsonObj{
public:
	jsonObj();
	void addVar(std::string vName, std::string val);
	std::string extractString();
private:
	std::vector<std::string> varName;
	std::vector<std::string> value;
};

jsonObj::jsonObj(){
}

void jsonObj::addVar(std::string vName, std::string val){
	varName.push_back(vName);
	value.push_back(val);
}

std::string jsonObj::extractString(){
	std::string jsonMsg;
	int varSize = varName.size();
	jsonMsg.append("{");
	for (int i = 0; i < varSize; i++){
		jsonMsg.append(varName[i]);
		jsonMsg.append(":\"");
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

	jo.addVar("userName", my_message.userName);
	jo.addVar("msg", my_message.msg);

	std::string jsonStr = jo.extractString();

	std::cout << "Json string: " << std::endl << jsonStr << std::endl;


	return 0;
}