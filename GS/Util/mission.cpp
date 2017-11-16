#include "mission.h"
#include "dbmanager.h"
#include <QDebug>

Mission::Mission(){
    myFlightPath = FlightPath();
    this->initValues();
}

Mission::Mission(FlightPath flightPath): myFlightPath(flightPath){
    this->initValues();
}

Mission::Mission(QJsonDocument document):
    jsonDoc(document)
{

    QJsonObject obj = jsonDoc.object();
    off_axis_odlc_pos = obj["off_axis_odlc_pos"].toObject();
    search_grid_points = obj["search_grid_points"].toArray();
    mission_waypoints = obj["mission_waypoints"].toArray();
    fly_zones = obj["fly_zones"].toArray();
    emergent_last_known_pos = obj["emergent_last_known_pos"].toObject();
    active = obj["active"].toBool();
    id = obj["id"].toInt();
    home_pos = obj["home_pos"].toObject();
    air_drop_pos = obj["home_pos"].toObject();

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

    std::cout << "created mission with " << values.at(0)->size() << " entries." << std::endl;

    /// @todo any remaining database functions for safe file handling if needed
    db.close();
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

int Mission::numOfEntries(){
    return values.at(0)->size();
}


QJsonObject Mission::get_off_axis_odlc_pos(){
    return off_axis_odlc_pos;
}

QJsonArray Mission::get_search_grid_points(){
    return search_grid_points;
}

QJsonArray Mission::get_mission_waypoints(){
    return mission_waypoints;
}

QJsonArray Mission::get_fly_zones(){
    return fly_zones;
}

QJsonObject Mission::get_emergent_last_known_pos(){
    return emergent_last_known_pos;
}

bool Mission::isActive(){
    return active;
}

int Mission::get_id(){
    return id;
}

QJsonObject Mission::get_home_pos(){
    return home_pos;
}

QJsonObject Mission::get_air_drop_pos(){
    return air_drop_pos;
}

void Mission::loadMissionObjects(QQuickWidget * mapWidget){
    if (!active)
        return;




    //-----------------------------------------------------Search Grid Points------------------------------------------------
    QJsonArray pathlat;
    QJsonArray pathlon;
    for(int i=0; i<search_grid_points.size();++i){
        pathlat.append(search_grid_points[i].toObject()["latitude"]);
        pathlon.append(search_grid_points[i].toObject()["longitude"]);

        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                Q_ARG(QVariant, ""),
                Q_ARG(QVariant, "images/blue_pin"),
                Q_ARG(QVariant, search_grid_points[i].toObject()["latitude"].toVariant()),
                Q_ARG(QVariant, search_grid_points[i].toObject()["longitude"].toVariant()),
                Q_ARG(QVariant, "/2"),
                Q_ARG(QVariant, ""));
    }
    if (search_grid_points.size() > 1){
        pathlat.append(search_grid_points[0].toObject()["latitude"]);
        pathlon.append(search_grid_points[0].toObject()["longitude"]);

        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addLine",
                                  Q_ARG(QVariant, ""),
                                  Q_ARG(QVariant, 3),
                                  Q_ARG(QVariant, "blue"),
                                  Q_ARG(QVariant, pathlat),
                                  Q_ARG(QVariant, pathlon),
                                  Q_ARG(QVariant, search_grid_points.size()));
    }
    Clear(pathlat);
    Clear(pathlon);


    //-----------------------------------------------------Mission Waypoints------------------------------------------------
    for(int i=0; i<mission_waypoints.size();++i){
        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                Q_ARG(QVariant, ""),
                Q_ARG(QVariant, "images/green_pin"),
                Q_ARG(QVariant, mission_waypoints[i].toObject()["latitude"].toVariant()),
                Q_ARG(QVariant, mission_waypoints[i].toObject()["longitude"].toVariant()),
                Q_ARG(QVariant, "/2"),
                Q_ARG(QVariant, ""));
    }
    if (mission_waypoints.size() > 1){
        pathlat.append(mission_waypoints[0].toObject()["latitude"]);
        pathlon.append(mission_waypoints[0].toObject()["longitude"]);

        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addLine",
                                  Q_ARG(QVariant, ""),
                                  Q_ARG(QVariant, 3),
                                  Q_ARG(QVariant, "blue"),
                                  Q_ARG(QVariant, pathlat),
                                  Q_ARG(QVariant, pathlon),
                                  Q_ARG(QVariant, mission_waypoints.size()));
    }
    Clear(pathlat);
    Clear(pathlon);

    //-----------------------------------------------------No-Fly Zone Boundary Points (also contains max/min altitude)------------------------------------------------
    for(int i=0; i<fly_zones.size();++i){
        QJsonObject temp2 = fly_zones[i].toObject();
        QJsonArray temp3 = temp2["boundary_pts"].toArray();
        for (int j=0;j<temp3.size();++j){
            pathlat.append(temp3[j].toObject()["latitude"]);
            pathlon.append(temp3[j].toObject()["longitude"]);
            QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                    Q_ARG(QVariant, ""),
                    Q_ARG(QVariant, "images/yellow_pin"),
                    Q_ARG(QVariant, temp3[j].toObject()["latitude"].toVariant()),
                    Q_ARG(QVariant, temp3[j].toObject()["longitude"].toVariant()),
                    Q_ARG(QVariant, "/2"),
                    Q_ARG(QVariant, ""));
        }


        if (temp3.size() > 1){
            pathlat.append(temp3[0].toObject()["latitude"]);
            pathlon.append(temp3[0].toObject()["longitude"]);

            QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addLine",
                                      Q_ARG(QVariant, ""),
                                      Q_ARG(QVariant, 3),
                                      Q_ARG(QVariant, "yellow"),
                                      Q_ARG(QVariant, pathlat),
                                      Q_ARG(QVariant, pathlon),
                                      Q_ARG(QVariant, temp3.size()+1));
        }

    }

    //-----------------------------------------------------Off Axis Odlc Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/blue_circle"),
            Q_ARG(QVariant, off_axis_odlc_pos["latitude"].toVariant()),
            Q_ARG(QVariant, off_axis_odlc_pos["longitude"].toVariant()),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"));

    //-----------------------------------------------------Emergent Last Known Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/green_circle"),
            Q_ARG(QVariant, emergent_last_known_pos["latitude"].toVariant()),
            Q_ARG(QVariant, emergent_last_known_pos["longitude"].toVariant()),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"));

    //-----------------------------------------------------Home Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/tent"),
            Q_ARG(QVariant, home_pos["latitude"].toVariant()),
            Q_ARG(QVariant, home_pos["longitude"].toVariant()),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"));

    //-----------------------------------------------------Air Drop Position------------------------------------------------
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/crosshair"),
            Q_ARG(QVariant, air_drop_pos["latitude"].toVariant()),
            Q_ARG(QVariant, air_drop_pos["longitude"].toVariant()),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"));


}

void Mission::Clear(QJsonArray &arr){
    for (int i=0; i<arr.size(); ++i){
        arr.removeFirst();
    }
}
