#include "obstacles.h"

Obstacles::Obstacles()
{

}

Obstacles::Obstacles(QJsonDocument document):
    jsonDoc(document)
{

    QJsonObject obj = jsonDoc.object();
    moving_obstacles = obj["moving_obstacles"].toArray();
    stationary_obstacles = obj["stationary_obstacles"].toArray();
}


QJsonArray Obstacles::get_moving_obstacles(){
    return moving_obstacles;
}

QJsonArray Obstacles::get_stationary_obstacles(){
    return stationary_obstacles;
}

void Obstacles::loadStationaryObjects(QQuickWidget * mapWidget){


    //-----------------------------------------------------Stationary Objects------------------------------------------------
    for(int i=0; i<stationary_obstacles.size();++i){

        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                Q_ARG(QVariant, ""),
                Q_ARG(QVariant, "images/red_circle"),
                Q_ARG(QVariant, stationary_obstacles[i].toObject()["latitude"].toVariant()),
                Q_ARG(QVariant, stationary_obstacles[i].toObject()["longitude"].toVariant()),
                Q_ARG(QVariant, "/2"),
                Q_ARG(QVariant, "/2"),
                Q_ARG(QVariant, "0"));
    }
}

void Obstacles::updateMovingObjects(QQuickWidget * mapWidget){

    //-----------------------------------------------------Moving Objects------------------------------------------------
    for(int i=0; i<moving_obstacles.size();++i){

        QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
                Q_ARG(QVariant, ""),
                Q_ARG(QVariant, "images/red_circle"),
                Q_ARG(QVariant, moving_obstacles[i].toObject()["latitude"].toVariant()),
                Q_ARG(QVariant, moving_obstacles[i].toObject()["longitude"].toVariant()),
                Q_ARG(QVariant, "/2"),
                Q_ARG(QVariant, "/2"),
                Q_ARG(QVariant, "0"));
    }
}
