#include "mission.h"
#include "dbmanager.h"
#include <QDebug>

Mission::Mission(QObject *parent) : QObject(parent){

}

Mission::Mission(QJsonObject obj) {
    id = obj["id"].toInt();
    active = obj["active"].toBool();
    home_pos = posToPoint(obj["home_pos"].toObject());
    air_drop_pos = posToPoint(obj["air_drop_pos"].toObject());
    off_axis_odlc_pos = posToPoint(obj["off_axis_odlc_pos"].toObject());
    emergent_last_known_pos = posToPoint(obj["emergent_last_known_pos"].toObject());
    mission_waypoints = setMissionWaypoints(obj["mission_waypoints"].toArray());
    search_grid_points = set3DPoints(obj["search_grid_points"].toArray());
    fly_zones = setFlyZones(obj["fly_zones"].toArray());
}

QList<FlyZone> * Mission::setFlyZones(QJsonArray flyZoneArray) {
    QList<FlyZone> * fly_zones = new QList<FlyZone>();
    for (int i = 0; i < flyZoneArray.size(); i++) {
        FlyZone fly_zone = FlyZone();
        fly_zone.max_alt = flyZoneArray[i].toObject()["altitude_msl_max"].toDouble();
        fly_zone.min_alt = flyZoneArray[i].toObject()["altitude_msl_max"].toDouble();
        fly_zone.boundary_points = setPoints(flyZoneArray[i].toObject()["boundary_pts"].toArray());
        fly_zones->append(fly_zone);
    }
    return fly_zones;
}

MissionWaypoints Mission::setMissionWaypoints(QJsonArray pointArray) {
    MissionWaypoints missionWaypoints = MissionWaypoints();
    missionWaypoints.waypoints = set3DPoints(pointArray);
    missionWaypoints.actions = new QList<int>();
    for (int i = 0; i < missionWaypoints.waypoints->size();i++) {
        if (i == 0)
            missionWaypoints.actions->append(MAV_CMD_NAV_TAKEOFF);
        else if (i == missionWaypoints.waypoints->size() -1)
            missionWaypoints.actions->append(MAV_CMD_NAV_LAND);
        else
            missionWaypoints.actions->append(MAV_CMD_NAV_WAYPOINT);
    }
    return missionWaypoints;
}


QList<QVector2D> * Mission::setPoints(QJsonArray pointArray) {
    QList<QVector2D> * points = new QList<QVector2D>();
    for(int i = 0; i < pointArray.size(); ++i){
       points->insert(pointArray[i].toObject()["order"].toInt()-1,
                                  posToPoint(pointArray[i].toObject()));
    }
    return points;
}

QList<QVector3D> * Mission::set3DPoints(QJsonArray pointArray) {
    QList<QVector3D> * points = new QList<QVector3D>();
    for(int i = 0; i < pointArray.size(); ++i){
       points->insert(pointArray[i].toObject()["order"].toInt()-1,
                                  posTo3DPoint(pointArray[i].toObject()));
    }
    return points;
}

QVector3D Mission::posTo3DPoint(QJsonObject obj) {
    return QVector3D(posToPoint(obj), obj["altitude"].toDouble());
}

QVector2D Mission::posToPoint(QJsonObject obj) {
    return QVector2D(obj["latitude"].toDouble(), obj["longitude"].toDouble());
}

void Mission::setMission(QJsonDocument jsonD) {
//    jsonDoc = jsonD;
//    QJsonObject obj = jsonDoc.object();
//    off_axis_odlc_pos = obj["off_axis_odlc_pos"].toObject();
//    search_grid_points = obj["search_grid_points"].toArray();
//    mission_waypoints = obj["mission_waypoints"].toArray();
//    fly_zones = obj["fly_zones"].toArray();
//    emergent_last_known_pos = obj["emergent_last_known_pos"].toObject();
//    active = obj["active"].toBool();
//    id = obj["id"].toInt();
//    home_pos = obj["home_pos"].toObject();
//    air_drop_pos = obj["home_pos"].toObject();
}


void Mission::loadWaypoint(mavlink_mission_request_t mrequest) {
    float params[7] = {0, 0, 0, 0, -35.3609161377, 149.1624603271, 40.40};
    int cmd = 16;
    if (mrequest.seq == 0) {
        cmd = 22;
    }
    cmd =22;
    emit (loadToUAV(mrequest.seq, cmd, params));
}



//QJsonObject Mission::get_off_axis_odlc_pos(){
//    return off_axis_odlc_pos;
//}

//QJsonArray Mission::get_search_grid_points(){
//    return search_grid_points;
//}
//QJsonArray Mission::get_mission_waypoints(){
//    return mission_waypoints;
//}

//QJsonArray Mission::get_fly_zones(){
//    return fly_zones;
//}

//QJsonObject Mission::get_emergent_last_known_pos(){
//    return emergent_last_known_pos;
//}

//bool Mission::isActive(){
//    return active;
//}

//int Mission::get_id(){
//    return id;
//}

//QJsonObject Mission::get_home_pos(){
//    return home_pos;
//}

//QJsonObject Mission::get_air_drop_pos(){
//    return air_drop_pos;
//}

void Mission::loadMissionObjects(QQuickWidget * mapWidget){
//    if (!active)
//        return;

//    //-----------------------------------------------------Search Grid Points------------------------------------------------
//    QJsonArray pathlat;
//    QJsonArray pathlon;
//    for(int i=0; i<search_grid_points.size();++i){
//        pathlat.append(search_grid_points[i].toObject()["latitude"]);
//        pathlon.append(search_grid_points[i].toObject()["longitude"]);

//        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
//                Q_ARG(QVariant, ""),
//                Q_ARG(QVariant, "images/blue_pin"),
//                Q_ARG(QVariant, search_grid_points[i].toObject()["latitude"].toVariant()),
//                Q_ARG(QVariant, search_grid_points[i].toObject()["longitude"].toVariant()),
//                Q_ARG(QVariant, "/2"),
//                Q_ARG(QVariant, ""),
//                Q_ARG(QVariant, "1"));
//    }
//    if (search_grid_points.size() > 1){
//        pathlat.append(search_grid_points[0].toObject()["latitude"]);
//        pathlon.append(search_grid_points[0].toObject()["longitude"]);

//        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addLine",
//                                  Q_ARG(QVariant, ""),
//                                  Q_ARG(QVariant, 3),
//                                  Q_ARG(QVariant, "blue"),
//                                  Q_ARG(QVariant, pathlat),
//                                  Q_ARG(QVariant, pathlon),
//                                  Q_ARG(QVariant, search_grid_points.size()),
//                                  Q_ARG(QVariant, "1"));
//    }
//    clearArr(pathlat);
//    clearArr(pathlon);


//    //-----------------------------------------------------Mission Waypoints------------------------------------------------
//    for(int i=0; i<mission_waypoints.size();++i){
//        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
//                Q_ARG(QVariant, ""),
//                Q_ARG(QVariant, "images/green_pin"),
//                Q_ARG(QVariant, mission_waypoints[i].toObject()["latitude"].toVariant()),
//                Q_ARG(QVariant, mission_waypoints[i].toObject()["longitude"].toVariant()),
//                Q_ARG(QVariant, "/2"),
//                Q_ARG(QVariant, ""),
//                Q_ARG(QVariant, "1"));
//    }
//    if (mission_waypoints.size() > 1){
//        pathlat.append(mission_waypoints[0].toObject()["latitude"]);
//        pathlon.append(mission_waypoints[0].toObject()["longitude"]);

//        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addLine",
//                                  Q_ARG(QVariant, ""),
//                                  Q_ARG(QVariant, 3),
//                                  Q_ARG(QVariant, "blue"),
//                                  Q_ARG(QVariant, pathlat),
//                                  Q_ARG(QVariant, pathlon),
//                                  Q_ARG(QVariant, mission_waypoints.size()),
//                                  Q_ARG(QVariant, "1"));
//    }
//    clearArr(pathlat);
//    clearArr(pathlon);

//    //-----------------------------------------------------No-Fly Zone Boundary Points (also contains max/min altitude)------------------------------------------------
//    for(int i=0; i<fly_zones.size();++i){
//        QJsonObject temp2 = fly_zones[i].toObject();
//        QJsonArray temp3 = temp2["boundary_pts"].toArray();
//        for (int j=0;j<temp3.size();++j){
//            pathlat.append(temp3[j].toObject()["latitude"]);
//            pathlon.append(temp3[j].toObject()["longitude"]);
//            QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
//                    Q_ARG(QVariant, ""),
//                    Q_ARG(QVariant, "images/yellow_pin"),
//                    Q_ARG(QVariant, temp3[j].toObject()["latitude"].toVariant()),
//                    Q_ARG(QVariant, temp3[j].toObject()["longitude"].toVariant()),
//                    Q_ARG(QVariant, "/2"),
//                    Q_ARG(QVariant, ""),
//                    Q_ARG(QVariant, "1"));
//        }


//        if (temp3.size() > 1){
//            pathlat.append(temp3[0].toObject()["latitude"]);
//            pathlon.append(temp3[0].toObject()["longitude"]);

//            QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addLine",
//                                      Q_ARG(QVariant, ""),
//                                      Q_ARG(QVariant, 3),
//                                      Q_ARG(QVariant, "yellow"),
//                                      Q_ARG(QVariant, pathlat),
//                                      Q_ARG(QVariant, pathlon),
//                                      Q_ARG(QVariant, temp3.size()+1),
//                                      Q_ARG(QVariant, "1"));
//        }

//    }

//    //-----------------------------------------------------Off Axis Odlc Position------------------------------------------------
//    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
//            Q_ARG(QVariant, ""),
//            Q_ARG(QVariant, "images/blue_circle"),
//            Q_ARG(QVariant, off_axis_odlc_pos["latitude"].toVariant()),
//            Q_ARG(QVariant, off_axis_odlc_pos["longitude"].toVariant()),
//            Q_ARG(QVariant, "/2"),
//            Q_ARG(QVariant, "/2"),
//            Q_ARG(QVariant, "1"));

//    //-----------------------------------------------------Emergent Last Known Position------------------------------------------------
//    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
//            Q_ARG(QVariant, ""),
//            Q_ARG(QVariant, "images/green_circle"),
//            Q_ARG(QVariant, emergent_last_known_pos["latitude"].toVariant()),
//            Q_ARG(QVariant, emergent_last_known_pos["longitude"].toVariant()),
//            Q_ARG(QVariant, "/2"),
//            Q_ARG(QVariant, "/2"),
//            Q_ARG(QVariant, "1"));

//    //-----------------------------------------------------Home Position------------------------------------------------
//    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
//            Q_ARG(QVariant, ""),
//            Q_ARG(QVariant, "images/tent"),
//            Q_ARG(QVariant, home_pos["latitude"].toVariant()),
//            Q_ARG(QVariant, home_pos["longitude"].toVariant()),
//            Q_ARG(QVariant, "/2"),
//            Q_ARG(QVariant, "/2"),
//            Q_ARG(QVariant, "1"));

//    //-----------------------------------------------------Air Drop Position------------------------------------------------
//    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
//            Q_ARG(QVariant, ""),
//            Q_ARG(QVariant, "images/crosshair"),
//            Q_ARG(QVariant, air_drop_pos["latitude"].toVariant()),
//            Q_ARG(QVariant, air_drop_pos["longitude"].toVariant()),
//            Q_ARG(QVariant, "/2"),
//            Q_ARG(QVariant, "/2"),
//            Q_ARG(QVariant, "1"));


}

void Mission::clearArr(QJsonArray &arr){
    for (int i=0; i<arr.size(); ++i){
        arr.removeFirst();
    }
}


void Mission::clearMission(QQuickWidget * mapWidget){
    int size = mapWidget->rootObject()->childItems().back()->childItems().length();
    for (int i=0; i<size; ++i){
        if (mapWidget->rootObject()->childItems().back()->childItems()[i]->property("someNumber") == 1){
            delete mapWidget->rootObject()->childItems().back()->childItems()[i];
            --i;
            --size;
        }
    }
}

void Mission::printJDoc(){
    //qDebug()<<jsonDoc;
}

//bool Mission::DNE(){
//  //  return jsonDoc.isEmpty();
//}
