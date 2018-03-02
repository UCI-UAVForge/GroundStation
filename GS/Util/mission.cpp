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

Mission::Mission(QJsonObject mission_obj, QJsonDocument obstacles_doc) {
    id = mission_obj["id"].toInt();
    active = mission_obj["active"].toBool();
    home_pos = posToPoint(mission_obj["home_pos"].toObject());
    air_drop_pos = posToPoint(mission_obj["air_drop_pos"].toObject());
    off_axis_odlc_pos = posToPoint(mission_obj["off_axis_odlc_pos"].toObject());
    emergent_last_known_pos = posToPoint(mission_obj["emergent_last_known_pos"].toObject());
    mission_waypoints = setMissionWaypoints(mission_obj["mission_waypoints"].toArray());
    search_grid_points = set3DPoints(mission_obj["search_grid_points"].toArray());
    fly_zones = setFlyZones(mission_obj["fly_zones"].toArray());
    obstacles = Obstacles(obstacles_doc);
}

Mission::Mission(const Mission& mission) {
    this->id = mission.id;
    this->active = mission.active;
    this->home_pos = mission.home_pos;
    this->air_drop_pos = mission.air_drop_pos;
    this->off_axis_odlc_pos = mission.off_axis_odlc_pos;
    this->emergent_last_known_pos = mission.emergent_last_known_pos;
    MissionWaypoints wp = MissionWaypoints();
    wp.waypoints = new QList<QVector3D>();
    wp.actions = new QList<int>();
    *wp.waypoints = *(mission.mission_waypoints.waypoints);
    *wp.actions = *(mission.mission_waypoints.actions);
    this->mission_waypoints = wp;
    this->search_grid_points = new QList<QVector3D>();
    for (int i=0; i<mission.search_grid_points->size(); ++i) {
        this->search_grid_points->append(mission.search_grid_points->at(i));
    }
    QList<FlyZone>* fly = new QList<FlyZone>();
    for (int i=0; i<mission.fly_zones->size(); ++i) {
        FlyZone* f = new FlyZone();
        f->max_alt = mission.fly_zones->at(i).max_alt;
        f->min_alt = mission.fly_zones->at(i).min_alt;
        f->boundary_points = new QList<QVector2D>();
        for (int j=0; j<mission.fly_zones->at(i).boundary_points->size(); ++j)
            f->boundary_points->append(mission.fly_zones->at(i).boundary_points->at(j));
        fly->append(*f);
    }
    this->fly_zones = fly;
    this->obstacles = mission.obstacles;
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
        missionWaypoints.actions->append(MAV_CMD_NAV_WAYPOINT);
//        if (i == 0) {
//            missionWaypoints.actions->append(MAV_CMD_NAV_TAKEOFF);
//        }
//        else if (i == missionWaypoints.waypoints->size() -1) {
//            missionWaypoints.actions->append(MAV_CMD_NAV_LAND);
//        }
//        else {
//            missionWaypoints.actions->append(MAV_CMD_NAV_WAYPOINT);
//        }
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
    return QVector3D(posToPoint(obj), obj["altitude_msl"].toDouble());
}

QVector2D Mission::posToPoint(QJsonObject obj) {
    return QVector2D(obj["latitude"].toDouble(), obj["longitude"].toDouble());
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

QVector<Waypoint::WP> Mission::constructWaypoints() {
    uint16_t len = mission_waypoints.waypoints->length();
    QVector<Waypoint::WP> waypoints;

    // The first waypoint does not matter - thrown from mavlink
    /* Home Position WP */
    Waypoint::WP wp;
    wp.id = 0;
    wp.command = 16;
    wp.autocontinue = 1;
    wp.current = 0;
    wp.param1 = 0;
    wp.param2 = 0;
    wp.param3 = 0;
    wp.x = 0;
    wp.y = 0;
    wp.z = 0;
    waypoints.append(wp);

    wp.id = 1;
    wp.command = 22;
    wp.autocontinue = 1;
    wp.current = 0;
    wp.param1 = 45;
    wp.param2 = 0;
    wp.param3 = 0;
    wp.x = this->home_pos.x();
    wp.y = this->home_pos.y();
    wp.z = 75;
    waypoints.append(wp);
    // Takeoff from home position to 75 altitude

    for (uint16_t i = 2; i <= len + 1; i++) {
        Waypoint::WP wp;
        wp.id = i;
        wp.command = mission_waypoints.actions->at(i-2);
        wp.autocontinue = 1;
        wp.current = 0;
        wp.param1 = 0;
        wp.param2 = 30;
        wp.param3 = 0;
        wp.x = mission_waypoints.waypoints->at(i-2).x();
        wp.y = mission_waypoints.waypoints->at(i-2).y();
        wp.z = mission_waypoints.waypoints->at(i-2).z();
        waypoints.append(wp);
    }

    qDebug() << "Mission::constructWaypoints set last point as home_pos w/ land";
    // Return to home position
    // CHANGE TO LOITER CENTER
    wp.id = len + 2;
    wp.command = 17;
    wp.autocontinue = 1;
    wp.current = 0;
    wp.param1 = 0;
    wp.param2 = 0; // 1 = opportunistic precision landing
    wp.param3 = 40; // loiter radius
    wp.x = 33.771945;
    wp.y = -117.694765;
    wp.z = 65;
    waypoints.append(wp);

    return waypoints;
}

uint16_t Mission::waypointLength() {
    return mission_waypoints.waypoints->length() + 3;
}

void Mission::setActions_wp() {
    mission_waypoints.actions = new QList<int>();
    for (uint16_t i = 0; i < this->waypointLength(); i++) {
        mission_waypoints.actions->append(16);
    }
}

Obstacles Mission::getObstacles() {
    return obstacles;
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
