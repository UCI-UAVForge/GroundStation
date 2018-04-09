#ifndef WAYPT_H
#define WAYPT_H

#include <QVector3D>
#include "waypoint.h"

class Waypt
{
public:
    Waypt(QVector3D coords);
    QVector3D coords;
    int action;
    double speed;
    uint8_t autocontinue;
    float param1;
    float param2;
    float param3;
    float param4;

    Waypoint::WP generateWP(uint16_t seq);
};

#endif // WAYPT_H
