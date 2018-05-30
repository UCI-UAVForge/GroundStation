#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QQuickWidget>
#include <QQuickItem>

#include "point.hpp"

class Obstacles
{
public:
    Obstacles();
    Obstacles(QJsonObject obj);

    void set_stationary_obstacles(QJsonArray arr);
//    QJsonArray get_moving_obstacles();
    QJsonArray get_stationary_obstacles();
    QJsonObject get_obj();
    bool segmentIntersectsObstacles(Point a, Point b);
private:
    QJsonArray moving_obstacles;
    QJsonArray stationary_obstacles;
};

#endif // OBSTACLES_H
