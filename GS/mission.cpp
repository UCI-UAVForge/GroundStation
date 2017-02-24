#include "mission.h"
#include "dbmanager.h"

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
    DbManager db(filename);

    /// @todo update these lines with values from the database
    foreach (MissionData data, db.missionGet()) {
        values.at(0)->append(data.heading);
        values.at(1)->append(data.lat);
        values.at(2)->append(data.lon);
        values.at(3)->append(data.alt);
        values.at(4)->append(data.pitch);
        values.at(5)->append(data.roll);
        values.at(6)->append(data.yaw);
        values.at(7)->append(data.xvel);
        values.at(8)->append(data.yvel);
        values.at(9)->append(data.zvel);
    };

    /// @todo any remaining database functions for safe file handling if needed
    db.close();
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
    DbManager db(filename);
    db.missionClear();

    for(int i = 0; i < values.at(0)->length(); i++){
        MissionData data;
        int index = 0;
        data.heading = values.at(index++)->at(i);
        data.lat = values.at(index++)->at(i);
        data.lon = values.at(index++)->at(i);;
        data.alt = values.at(index++)->at(i);
        data.pitch = values.at(index++)->at(i);
        data.roll = values.at(index++)->at(i);
        data.yaw = values.at(index++)->at(i);
        data.xvel = values.at(index++)->at(i);
        data.yvel = values.at(index++)->at(i);
        data.zvel = values.at(index++)->at(i);

        /// @todo write each of the above variables to the database
        db.missionAdd(data);
    }

    /// @todo any remaining database functions for safe file handling if needed
    db.missionSaveToFile();
    db.close();

    return true;
}
