#include "uav.h"
#include <qDebug>

UAV::UAV()
{}

void UAV::setWidget(QQuickWidget * map){
    mapWidget=map;
}

void UAV::updateUAV(float x, float y){
    qDebug() << "uav.cpp temp compiler error fix";
    int size = 0; // Temporary compiler error fix
    for (int i=0; i<size; ++i){
        if (mapWidget->rootObject()->childItems().back()->childItems()[i]->property("someNumber") == 2){
            delete mapWidget->rootObject()->childItems().back()->childItems()[i];
            --i;
            --size;
        }
    }
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/red_circle"),
            Q_ARG(QVariant, x),
            Q_ARG(QVariant, y),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "2"));
}
