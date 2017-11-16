#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QQuickWidget>
#include <QQuickItem>

class Obstacles
{
public:
    Obstacles();
    Obstacles(QJsonDocument document);


    QJsonArray get_moving_obstacles();
    QJsonArray get_stationary_obstacles();
    void loadStationaryObjects(QQuickWidget * mapWidget);
    void updateMovingObjects(QQuickWidget * mapWidget);
private:

    QJsonDocument jsonDoc;
    QJsonArray moving_obstacles;
    QJsonArray stationary_obstacles;
};

#endif // OBSTACLES_H
