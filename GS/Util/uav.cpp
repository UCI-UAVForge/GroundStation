#include "uav.h"

UAV::UAV()
{}

void UAV::setWidget(QQuickWidget * map){
    mapWidget=map;
}

void UAV::updateUAV(float x, float y){
    QMetaObject::invokeMethod(mapWidget->rootObject()->childItems().back(), "addMarker",
            Q_ARG(QVariant, ""),
            Q_ARG(QVariant, "images/red_circle"),
            Q_ARG(QVariant, x),
            Q_ARG(QVariant, y),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "/2"),
            Q_ARG(QVariant, "Mission"));
}
