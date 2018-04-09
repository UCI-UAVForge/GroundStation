#include "waypt.h"

Waypt::Waypt(QVector3D coords) {
    this->coords = coords;
    this->action = MAV_CMD_NAV_WAYPOINT;
    this->speed = 20; // TODO: IDK WUT VALUE
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
