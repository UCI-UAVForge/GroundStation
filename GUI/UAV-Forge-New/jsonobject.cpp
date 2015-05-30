#include "jsonobject.h"
#include <fstream>
#include <sstream>

jsonObj::jsonObj(){
}

//adding coordinates from the Coordinates struct to latitude and longitude vectors
void jsonObj::addCoordinate(struct Coordinates coordinate)
{
    latitude.push_back(coordinate.latitude);
    longitude.push_back(coordinate.longitude);
}

//takes latitude and logngitude values from their respective vectors
//and then puts the data into a json array string
std::string jsonObj::coordinatesExtractString() {
    std::string jsonMsg;
    std::stringstream ss;
    size_t varSize = latitude.size();
    jsonMsg.append("[");
    for (int i = 0; i < varSize; i++)
    {
        jsonMsg.append("{\"latitude\":");
        ss << latitude[i];

        jsonMsg.append(ss.str());
        jsonMsg.append(" , \"longitude\":");
        ss.str("");
        ss << longitude[i];
        jsonMsg.append(ss.str() + "},");
        ss.str("");
    }
    jsonMsg.erase(jsonMsg.length() - 1); //gets rid of the last comma
    jsonMsg.append("]");
    return jsonMsg;
}
