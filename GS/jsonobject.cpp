#include "jsonobject.h"
#include <fstream>
#include <sstream>

jsonObj::jsonObj(){
}


void jsonObj::addCoordinate(struct Coordinates coordinate)
{
    latitude.push_back(coordinate.latitude);
    longitude.push_back(coordinate.longitude);
}


std::string jsonObj::coordinatesExtractString() {
    std::string jsonMsg;
    std::stringstream ss;
    size_t varSize = latitude.size();
    jsonMsg.append("[");
    for (unsigned int i = 0; i < varSize; i++)
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
}
