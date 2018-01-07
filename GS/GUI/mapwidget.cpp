#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) : QQuickWidget(parent) {
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setSource(QUrl("qrc:/res/map.qml"));
    map = this->rootObject()->findChild<QObject*>("map");
}

void MapWidget::drawPoint(QVector2D point, QColor color) {
    QMetaObject::invokeMethod(map, "drawPoint",
            Q_ARG(QVariant, point),
            Q_ARG(QVariant, color));
}

void MapWidget::drawPolyline(QVariantList points, QColor color){
    QMetaObject::invokeMethod(map, "drawPolyline",
            Q_ARG(QVariant, QVariant::fromValue(points)),
            Q_ARG(QVariant, color));
}

void MapWidget::drawPolygon(QVariantList points, QColor color) {
    QMetaObject::invokeMethod(map, "drawPolygon",
           Q_ARG(QVariant, QVariant::fromValue(points)),
           Q_ARG(QVariant, color));
}

void MapWidget::updateUAVPosition(mavlink_gps_raw_int_t gps) {
    if (gps.lat != currentUAVlat && gps.lon != currentUAVlon) {
        currentUAVlat = gps.lat; currentUAVlon = gps.lon;
        QString coords = QGeoCoordinate((float)gps.lat/10000000, (float)gps.lon/10000000).toString(QGeoCoordinate::DegreesWithHemisphere);

        this->rootObject()->setProperty("coords", QVariant(coords));
        QMetaObject::invokeMethod(this->rootObject()->findChild<QObject*>("uavPosition"), "updateUAVPosition",
               Q_ARG(QVariant, coords));
    }
}

void MapWidget::clearMap() {
    QMetaObject::invokeMethod(map, "clearMap");
}

void MapWidget::drawMission(Mission * mission) {
    clearMap();
    drawPoint(mission->home_pos, QColor(255, 0, 0));
    drawPoint(mission->air_drop_pos, QColor(0, 230, 230));
    drawPoint(mission->off_axis_odlc_pos, QColor(10,10, 200));
    drawPoint(mission->emergent_last_known_pos, QColor(0,0,0));
    drawPolyline(toQVariantList(mission->mission_waypoints.waypoints), QColor("blue"));
    drawPolygon(toQVariantList(mission->search_grid_points), QColor("yellow"));
    for (int i = 0; i < mission->fly_zones->size(); i++)
        drawPolygon(toQVariantList(mission->fly_zones->at(i).boundary_points), QColor(0, 255, 0, 50));

}
