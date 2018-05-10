#ifndef WAYPT_H
#define WAYPT_H

#include <QVector3D>
#include <QVector2D>
#include "waypoint.h"

class Waypt
{
public:
    Waypt();
    Waypt(QVector3D coords);
    Waypt(QVector2D coords);
    QVector3D coords;
    int action;
    double speed;
    bool changeSpeed = false;
    uint8_t autocontinue;
    float param1;
    float param2;
    float param3;
    float param4;

    Waypoint::WP generateWP(uint16_t seq);
    Waypoint::WP setSpeed(uint16_t seq);
    void setDefaultTakeoff(float alt, float pitchAngle, QVector2D home_pos);
    void setDefaultLanding(QVector2D landingPoint, float abortAlt);
};

#endif // WAYPT_H
