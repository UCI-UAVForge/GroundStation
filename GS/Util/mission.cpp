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
    interopPath = setMissionPath(obj["mission_waypoints"].toArray());
    generatedPath = interopPath;
    search_grid_points = set3DPoints(obj["search_grid_points"].toArray());
    fly_zones = setFlyZones(obj["fly_zones"].toArray());
}

Mission::Mission(QJsonObject mission_obj, QJsonDocument obstacles_doc) {
    id = mission_obj["id"].toInt();
    active = mission_obj["active"].toBool();
    home_pos = posToPoint(mission_obj["home_pos"].toObject());
    air_drop_pos = posToPoint(mission_obj["air_drop_pos"].toObject());
    off_axis_odlc_pos = posToPoint(mission_obj["off_axis_odlc_pos"].toObject());
    emergent_last_known_pos = posToPoint(mission_obj["emergent_last_known_pos"].toObject());
    interopPath = setMissionPath(mission_obj["mission_waypoints"].toArray());
    generatedPath = interopPath;
    search_grid_points = set3DPoints(mission_obj["search_grid_points"].toArray());
    fly_zones = setFlyZones(mission_obj["fly_zones"].toArray());
    obstacles = Obstacles(obstacles_doc);
}

Mission::Mission(const Mission& mission) {
    /* I don't think we need a copy mission anymore */
    this->id = mission.id;
    this->active = mission.active;
    this->home_pos = mission.home_pos;
    this->air_drop_pos = mission.air_drop_pos;
    this->off_axis_odlc_pos = mission.off_axis_odlc_pos;
    this->emergent_last_known_pos = mission.emergent_last_known_pos;
    this->interopPath = mission.interopPath;
    this->generatedPath = mission.generatedPath;
    this->search_grid_points = new QList<QVector3D>();
    for (int i=0; i<mission.search_grid_points->size(); ++i) {
        this->search_grid_points->append(mission.search_grid_points->at(i));
    }
    QList<FlyZone> fly;
    for (int i=0; i<mission.fly_zones.size(); ++i) {
        FlyZone f;
        f.max_alt = mission.fly_zones.at(i).max_alt;
        f.min_alt = mission.fly_zones.at(i).min_alt;
        f.boundary_points;
        for (int j=0; j<mission.fly_zones.at(i).boundary_points.size(); ++j)
            f.boundary_points.append(mission.fly_zones.at(i).boundary_points.at(j));
        fly.append(f);
    }
    this->fly_zones = fly;
    this->obstacles = mission.obstacles;
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

QVector3D Mission::posTo3DPoint(QJsonObject obj) {
    return QVector3D(posToPoint(obj), obj["altitude_msl"].toDouble());
}

QVector2D Mission::posToPoint(QJsonObject obj) {
    return QVector2D(obj["latitude"].toDouble(), obj["longitude"].toDouble());
}

QJsonValue Mission::pointToPos(QVector2D point) {
    QJsonObject temp;
    temp["latitude"] = point.x();
    temp["longitude"] = point.y();
    return QJsonValue(temp);
}

QVector<Waypoint::WP> Mission::constructWaypoints(bool interop) {
    uint16_t len = generatedPath.length();
    QVector<Waypoint::WP> waypoints;

    waypoints.append(missionPrologue());
    waypoints.append(generateTakeoff());
    waypoints.append(generatedPath.generateWaypoints(2));

    // TODO: add Landing

    return waypoints;
}

uint16_t Mission::completeMissionLength(bool interop) {
    int missionPrologue = 1;
    int takeoff = 1;
    int waypoints = interop ? interopPath.length() : generatedPath.length();
    int landing = 0; // TODO landing
    return missionPrologue + takeoff + waypoints + landing;
}

Obstacles Mission::getObstacles() {
    return obstacles;
}

QJsonDocument Mission::toJson() {
    QJsonObject obj;
    obj["id"] = QJsonValue(id);
    obj["active"] = QJsonValue(active);
    obj["home_pos"] = pointToPos(home_pos);
    obj["air_drop_pos"] = pointToPos(air_drop_pos);
    obj["off_axis_odlc_pos"] = pointToPos(off_axis_odlc_pos);
    obj["emergent_last_known_pos"] = pointToPos(emergent_last_known_pos);
    QList<Waypt> *waypoints = &(interopPath.waypoints);
    QJsonArray meow;
    for (int i = 0; i < waypoints->length(); i++) {
        QJsonObject temp;
        QVector3D coord = waypoints->at(i).coords;
        temp["latitude"] = QJsonValue(coord.x());
        temp["longitude"] = QJsonValue(coord.y());
        temp["altitude_msl"] = QJsonValue(coord.z());
        temp["order"] = QJsonValue(i+1);
        meow.append(temp);
    }
    obj["mission_waypoints"] = QJsonValue(meow);
//    obj["search_grid_points"] = QJsonValue(search_grid_points);
    QJsonArray meow2;
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
    }
    QJsonDocument doc;
    doc.setObject(obj);
    return doc;
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

Waypoint::WP Mission::generateTakeoff() {
    Waypoint::WP wp = {1, 0, 22, 0, 1, takeoff.pitch, 0, 0, takeoff.yawAngle,
                      home_pos.x(), home_pos.y(), takeoff.altitude};
    return wp;
}
