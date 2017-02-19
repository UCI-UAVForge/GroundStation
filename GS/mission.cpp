#include "mission.h"

Mission::Mission(){
    myFlightPath = FlightPath();
    this->initValues();
}

Mission::Mission(FlightPath flightPath): myFlightPath(flightPath){
    this->initValues();
}

Mission::Mission(QString filename){
    this->initValues();

    //reuse the FlightPath's load method
    this->myFlightPath = FlightPath(filename+"_fp");

    /// @todo any database initialization and error checking if necesary

    /// @todo get the number of lines in the database
    int lines = 10;

    for (int i = 0; i < lines; i++){
        /// @todo update these lines with values from the database
        float heading = 0.0f;
        double lat = 0.0;
        double lon = 0.0;
        float alt = 0.0f;
        float pitch = 0.0f;
        float roll = 0.0f;
        float yaw = 0.0f;
        float xvel = 0.0f;
        float yvel = 0.0f;
        float zvel = 0.0f;

        values.at(0)->append(heading);
        values.at(1)->append(lat);
        values.at(2)->append(lon);
        values.at(3)->append(alt);
        values.at(4)->append(pitch);
        values.at(5)->append(roll);
        values.at(6)->append(yaw);
        values.at(7)->append(xvel);
        values.at(8)->append(yvel);
        values.at(9)->append(zvel);
    }

    /// @todo any remaining database functions for safe file handling if needed
}

Mission::~Mission() {
}

FlightPath *Mission::getFlightPath(){
    return &myFlightPath;
}

void Mission::initValues(){
    for(int i = 0; i < 10; i++){
        values.append(new QVector<double>);
    }
}

void Mission::addPacket(Protocol::TelemetryPacket telemPacket){
    std::cout<<"MISSION: Recieving new telem packet" << std::endl;
    float headingF;
    double lat,lon;
    float alt;
    float pitch,roll,yaw;
    float xvel,yvel,zvel;

    telemPacket.GetHeading(&headingF);
    telemPacket.GetLocation(&lat,&lon,&alt);
    telemPacket.GetOrientation(&pitch,&roll,&yaw);
    telemPacket.GetVelocity(&xvel,&yvel,&zvel);
    double headingD = headingF;

    values.at(0)->append(headingD);
    values.at(1)->append(lat);
    values.at(2)->append(lon);
    values.at(3)->append(alt);
    values.at(4)->append(pitch);
    values.at(5)->append(roll);
    values.at(6)->append(yaw);
    values.at(7)->append(xvel);
    values.at(8)->append(yvel);
    values.at(9)->append(zvel);
}


// values[id][index] = some value (double)
QVector<double> *Mission::getValuesForID(int id){
    return values.at(id);
}

QVector<double> *Mission::getValuesForIndex(int index){
    QVector<double> *rtnList = new QVector<double>();
    for (int id = 0; id < values.size(); id++){
        rtnList->append(values.at(id)->at(index));
    }
    return rtnList;
}

double Mission::getValueForIndexAndID(int index,int id){
    return values.at(id)->at(index);
}

bool Mission::save(QString filename){
    //Reuse the FlightPath save function.
    if(!myFlightPath.save(filename+"_fp")){
        return false; //return false if saving the FlightPath causes an error.
    }

    /// @todo any database initialization and error checking.

    for(int i = 0; i < values.at(0)->length(); i++){
        int index = 0;
        float heading = values.at(index++)->at(i);
        double lat = values.at(index++)->at(i);
        double lon = values.at(index++)->at(i);;
        float alt = values.at(index++)->at(i);
        float pitch = values.at(index++)->at(i);
        float roll = values.at(index++)->at(i);
        float yaw = values.at(index++)->at(i);
        float xvel = values.at(index++)->at(i);
        float yvel = values.at(index++)->at(i);
        float zvel = values.at(index++)->at(i);

        /// @todo write each of the above variables to the database


    }

    /// @todo any remaining database functions for safe file handling if needed

    return true;
}
