#include "waypt.h"

Waypt::Waypt() {
}

Waypt::Waypt(QVector3D coords) {
    this->coords = coords;
    this->action = MAV_CMD_NAV_WAYPOINT;
    this->speed = 20;
    this->autocontinue = 1;
    this->param1 = 0;
    this->param2 = 15;
    this->param3 = 0;
    this->param4 = 0;
}

Waypt::Waypt(QVector2D coords) {
    this->coords = QVector3D(coords.x(), coords.y(), 30);
    this->action = MAV_CMD_NAV_WAYPOINT;
    this->speed = 20;
    this->autocontinue = 1;
    this->param1 = 0;
    this->param2 = 15;
    this->param3 = 0;
    this->param4 = 0;
}

Waypoint::WP Waypt::generateWP(uint16_t seq) {
    Waypoint::WP wp;
    wp.id = seq;
    wp.frame = 0;
    wp.command = action;
    wp.autocontinue = autocontinue;
    wp.param1 = param1;
    wp.param2 = param2;
    wp.param3 = param3;
    wp.param4 = param4;
    wp.x = coords.x();
    wp.y = coords.y();
    wp.z = coords.z();
    return wp;
}

Waypoint::WP Waypt::setSpeed(uint16_t seq) {
    Waypoint::WP wp;
    wp.id = seq;
    wp.frame = 0;
    wp.command = 178;
    wp.autocontinue = autocontinue;
    wp.param1 = 0;
    wp.param2 = speed;
    wp.param3 = -1;
    wp.param4 = 0;
    wp.x = 0;
    wp.y = 0;
    wp.z = 0;
    return wp;
}

void Waypt::setDefaultTakeoff(float alt, float pitchAngle, QVector2D home_pos) {
    this->coords = QVector3D(home_pos.x(), home_pos.y(), alt);
    this->action = MAV_CMD_NAV_TAKEOFF;
    this->speed = 0;
    this->autocontinue = 1;
    this->param1 = pitchAngle;
    this->param2 = 0;
    this->param3 = 0;
    this->param4 = 0;
}

void Waypt::setDefaultLanding(QVector2D landingPoint, float abortAlt) {
    this->coords = QVector3D(landingPoint);
    this->action = MAV_CMD_NAV_LAND;
    this->speed = 0;
    this->autocontinue = 1;
    this->param1 = abortAlt;
    this->param2 = 0;
    this->param3 = 0;
    this->param4 = 0;
}
