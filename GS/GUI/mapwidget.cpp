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

void MapWidget::drawUAV(double lat, double lon, double heading) {
    QMetaObject::invokeMethod(map, "drawUAV",
            Q_ARG(QVariant, lat),
            Q_ARG(QVariant, lon),
            Q_ARG(QVariant, heading));
}

void MapWidget::updateCenter(double lat, double lon) {
    QMetaObject::invokeMethod(map, "updateCenter",
            Q_ARG(QVariant, lat),
            Q_ARG(QVariant, lon));
}

void MapWidget::testRemoveUAV() {
    QMetaObject::invokeMethod(map, "removeUAV");
}

void MapWidget::updateUAV() {
    if (blinkUAV) {
        QTimer timer;
        QEventLoop loop;

        drawUAV(uav_latitude, uav_longitude, uav_heading);

        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(50);
        loop.exec();

        testRemoveUAV();

        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(50);
        loop.exec();

        drawUAV(uav_latitude, uav_longitude, uav_heading);
    } else drawUAV(uav_latitude, uav_longitude, uav_heading);
}

void MapWidget::updateUAVPosition(mavlink_global_position_int_t gps_int) {
    uav_latitude = gps_int.lat/10000000;
    uav_longitude = gps_int.lon/10000000;
    uav_heading = gps_int.hdg == UINT16_MAX ? 0 : gps_int.hdg/100;
    if (updateConstant) {
        updateCenter(uav_latitude, uav_longitude);
        updateUAV();
    }
}
