#ifndef JSONOBJECT
#define JSONOBJECT

#include <iostream>
#include <vector>

class jsonObj{
public:
    jsonObj();
    void addCoordinate(struct Coordinates);

    std::string coordinatesExtractString();

private:
    std::vector<std::string> varName;
    std::vector<std::string> value;
    std::vector<double> latitude;
    std::vector<double> longitude;
};

struct Msg{
    std::string  userName;
    std::string  msg;
};

struct Coordinates{
    double latitude;
    double longitude;
};

#endif // JSONOBJECT

