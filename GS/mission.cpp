#include "mission.h"

Mission::Mission(){

}

Mission::Mission(FlightPath flightPath) : myFlightPath(flightPath){

}

Mission::~Mission() {

}

FlightPath *Mission::getFlightPath(){
    return &myFlightPath;
}

void Mission::addPacket(Protocol::TelemetryPacket telemPacket){
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

    if (values.size() == 0){
        for(int i = 0; i < 10; i++){
            values.append(new QVector<double>);
        }
    }
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

