#include "mission.h"
#include "dbmanager.h"
#include <QDebug>


//--------------------------------------------------------
//                          Constructors
//--------------------------------------------------------
Mission::Mission(QObject *parent) : QObject(parent){
}

Mission::Mission(bool therewasaweirdoverloadederror) {
    defaultLandingTakeoff();

    generatedPath.waypoints.prepend(takeoff);
    generatedPath.waypoints.append(landing.waypoints);
}


Mission::Mission(QJsonObject obj) {
    loadInteropJson(obj);
    defaultLandingTakeoff();

    generatedPath.waypoints.prepend(takeoff);
    generatedPath.waypoints.append(landing.waypoints);
}

Mission::Mission(QJsonObject mission_obj, QJsonDocument obstacles_doc) {
    loadInteropJson(mission_obj);
    obstacles = Obstacles(obstacles_doc);
    /* Default takeoff+landing */
    takeoff.setDefaultTakeoff(20, 45, home_pos);
    QList<QVector3D> landingPath({QVector3D(33.770980, -117.694640, 5)});
    landing.setDefaultLanding(landingPath, QVector2D(33.771031, -117.694890), 15);

    generatedPath.waypoints.append(landing.waypoints);
    generatedPath.waypoints.prepend(takeoff);
}

//--------------------------------------------------------
//                          Loading
//--------------------------------------------------------
void Mission::loadJson(QJsonObject obj){
    id                      = obj["id"].toInt();
    active                  = obj["active"].toBool();
    home_pos                = posToPoint(obj["home_pos"].toObject());
    air_drop_pos            = posToPoint(obj["air_drop_pos"].toObject());
    off_axis_odlc_pos       = posToPoint(obj["off_axis_odlc_pos"].toObject());
    emergent_last_known_pos = posToPoint(obj["emergent_last_known_pos"].toObject());

    interopPath             = setMissionPath2(obj["mission_waypoints"].toArray());
    generatedPath           = interopPath;

    search_grid_points      = set3DPoints(obj["search_grid_points"].toArray());
    fly_zones = setFlyZones(obj["fly_zones"].toArray());
}

void Mission::loadInteropJson(QJsonObject &obj){
    id                      = obj["id"].toInt();
    active                  = obj["active"].toBool();
    home_pos                = posToPoint(obj["home_pos"].toObject());
    air_drop_pos            = posToPoint(obj["air_drop_pos"].toObject());
    off_axis_odlc_pos       = posToPoint(obj["off_axis_odlc_pos"].toObject());
    emergent_last_known_pos = posToPoint(obj["emergent_last_known_pos"].toObject());
    interopPath             = setMissionPath(obj["mission_waypoints"].toArray());
    generatedPath           = interopPath;
    search_grid_points      = set3DPoints(obj["search_grid_points"].toArray());
    fly_zones = setFlyZones(obj["fly_zones"].toArray());
}

QVector3D Mission::posTo3DPoint(QJsonObject obj) {
    return QVector3D(posToPoint(obj), obj["altitude_msl"].toDouble());
}

QVector2D Mission::posToPoint(QJsonObject obj) {
    return QVector2D(obj["latitude"].toDouble(), obj["longitude"].toDouble());
}

QList<FlyZone> Mission::setFlyZones(QJsonArray flyZoneArray) {
    QList<FlyZone> fly_zones;
    for (int i = 0; i < flyZoneArray.size(); i++) {
        FlyZone fly_zone;
        fly_zone.max_alt = flyZoneArray[i].toObject()["altitude_msl_max"].toDouble();
        fly_zone.min_alt = flyZoneArray[i].toObject()["altitude_msl_max"].toDouble();
        fly_zone.boundary_points = setPoints(flyZoneArray[i].toObject()["boundary_pts"].toArray());
        fly_zones.append(fly_zone);
    }
    return fly_zones;
}

MissionPath Mission::setMissionPath(QJsonArray pointArray) {
    MissionPath missionPath = MissionPath();
    for(int i = 0; i < pointArray.size(); ++i){
        QVector3D coords = posTo3DPoint(pointArray[i].toObject());
        Waypt waypt = Waypt(coords);
        int order = pointArray[i].toObject()["order"].toInt()-1;
        missionPath.addWaypoint(waypt, order);
    }
    return missionPath;
}

MissionPath Mission::setMissionPath2(QJsonArray pointArray) {
    MissionPath missionPath = MissionPath();
    for(int i = 0; i < pointArray.size(); ++i){
        QJsonObject temp = pointArray[i].toObject();
        Waypt waypt;
        waypt.coords = QVector3D(temp["x"].toDouble(),temp["y"].toDouble(),temp["z"].toDouble());
        waypt.action = temp["action"].toInt();
        waypt.speed = temp["speed"].toDouble();
        waypt.autocontinue = temp["autocontinue"].toInt();
        waypt.param1 = temp["param1"].toDouble();
        waypt.param2 = temp["param2"].toDouble();
        waypt.param3 = temp["param3"].toDouble();
        waypt.param4 = temp["param4"].toDouble();
        int order = pointArray[i].toObject()["order"].toInt()-1;

        missionPath.addWaypoint(waypt, order);
    }
    return missionPath;
}

QList<QVector2D> Mission::setPoints(QJsonArray pointArray) {
    QList<QVector2D> points;
    for(int i = 0; i < pointArray.size(); ++i){
       points.insert(pointArray[i].toObject()["order"].toInt()-1,
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

Obstacles Mission::getObstacles() {
    return obstacles;
}


//--------------------------------------------------------
//                          Mission Stuffs
//--------------------------------------------------------

void Mission::defaultLandingTakeoff() {
    takeoff.setDefaultTakeoff(20, 45, home_pos);
    QList<QVector3D> landingPath({QVector3D(33.770980, -117.694640, 5)});
    landing.setDefaultLanding(landingPath, QVector2D(33.771031, -117.694890), 15);
}

QVector<Waypoint::WP> Mission::constructWaypoints() {
    QVector<Waypoint::WP> waypoints;

    waypoints.append(missionPrologue());
    waypoints.append(generatedPath.generateWaypoints(1));

    return waypoints;
}

QList<QPolygonF> Mission::get_obstacles() {
    QList<QPolygonF> polys;
    for (QJsonValueRef o : obstacles.get_stationary_obstacles()) {
        QJsonObject obstacle = o.toObject();
        double obs_lat = obstacle["latitude"].toDouble();
        double obs_lon = obstacle["longitude"].toDouble();
        double radius = obstacle["cylinder_radius"].toDouble();
        double delta = meters_to_deg(radius, obs_lat);

        QVector<QPointF> obstacle_footprint_points;
        for (double theta = 0; theta < 2*M_PI; theta += M_PI/360) {
            obstacle_footprint_points << QPointF(obs_lat + (delta * cos(theta)), obs_lon + (delta * sin(theta)));
        }
        polys.append(QPolygonF(obstacle_footprint_points));
    }
    return polys;
}

Waypoint::WP Mission::missionPrologue() {
    Waypoint::WP wp = {0,0,16,0,1,0,0,0,0,0,0,0};
    return wp;
}

QList<QVector3D> *Mission::toList() {
    QList<QVector3D> *list = new QList<QVector3D>();
    foreach (Waypt wp, generatedPath.waypoints)
        list->append(wp.coords);
    return list;
}


//--------------------------------------------------------
//                          Editing
//--------------------------------------------------------
QVector3D Mission::moveWaypoint(int wpNum, QKeyEvent * k) {
    double modifier = 0.00001;
    if (k->modifiers() & Qt::ShiftModifier) {
        modifier = 0.0002;
    }
    if (wpNum == 0) // Takeoff unmodifiable
        return QVector3D(home_pos);
    QVector3D wp = generatedPath.waypoints.at(wpNum).coords;
    switch (k->key()) {
        case Qt::Key_Up:
            wp.setX(wp.x()+modifier);
        break;
        case Qt::Key_Down:
            wp.setX(wp.x()-modifier);
        break;
        case Qt::Key_Left:
            wp.setY(wp.y()-modifier);
        break;
        case Qt::Key_Right:
            wp.setY(wp.y()+modifier);
        break;
    }
    generatedPath.waypoints[wpNum].coords = wp;
    return wp;
}


//--------------------------------------------------------
//                          Saving
//--------------------------------------------------------
QJsonDocument Mission::toJson() {
    QJsonObject obj;
    obj["id"] = QJsonValue(id);
    obj["active"] = QJsonValue(active);
    obj["home_pos"] = pointToPos(home_pos);
    obj["air_drop_pos"] = pointToPos(air_drop_pos);
    obj["off_axis_odlc_pos"] = pointToPos(off_axis_odlc_pos);
    obj["emergent_last_known_pos"] = pointToPos(emergent_last_known_pos);

    QList<Waypt> *waypoints = &(generatedPath.waypoints);
    QJsonArray meow;
    for (int i = 0; i < waypoints->length(); i++) {
        QJsonObject temp;
        Waypt pt = waypoints->at(i);
        QVector3D * coord = &(pt.coords);
        temp["x"] = QJsonValue(coord->x());
        temp["y"] = QJsonValue(coord->y());
        temp["z"] = QJsonValue(coord->z());
        temp["action"] = QJsonValue(pt.action);
        temp["speed"] = QJsonValue(pt.speed);
        temp["autocontinue"] = QJsonValue(pt.autocontinue);
        temp["param1"] = QJsonValue(pt.param1);
        temp["param2"] = QJsonValue(pt.param2);
        temp["param3"] = QJsonValue(pt.param3);
        temp["param4"] = QJsonValue(pt.param4);
        temp["order"] = QJsonValue(i+1);
        meow.append(temp);
    }
    obj["mission_waypoints"] = meow;

    QJsonArray meow2;
    for (int i=0; i<search_grid_points->size(); i++){
        QJsonObject temp;
        temp["latitude"] = QJsonValue(search_grid_points->at(i).x());
        temp["longitude"] = QJsonValue(search_grid_points->at(i).y());
        temp["altitude_msl"] = QJsonValue(search_grid_points->at(i).z());
        temp["order"] = QJsonValue(i+1);
    }
    obj["search_grid_points"] = meow2;

    QJsonArray meow3;
    for (int i = 0; i<fly_zones.length(); i++) {
        QJsonObject temp;
        FlyZone *zone = &fly_zones[i];
        temp["altitude_msl_max"]=zone->max_alt;
        temp["altitude_msl_min"]=zone->min_alt;
        QJsonArray temp2;
        for (int j=0; j<zone->boundary_points.length(); j++) {
            QJsonObject temp3;
            temp3["latitude"] = QJsonValue(zone->boundary_points[j].x());
            temp3["longitude"] = QJsonValue(zone->boundary_points[j].y());
            temp3["order"] = QJsonValue(j+1);
            temp2.append(temp3);
        }
        temp["boundary_pts"]=temp2;
        meow3.append(temp);
    }
    obj["fly_zones"] = meow3;

    QJsonDocument doc;
    doc.setObject(obj);
    return doc;
}

QJsonValue Mission::pointToPos(QVector2D point) {
    QJsonObject temp;
    temp["latitude"] = point.x();
    temp["longitude"] = point.y();
    return QJsonValue(temp);
}
