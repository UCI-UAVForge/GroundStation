#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) : QQuickWidget(parent) {
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setSource(QUrl("qrc:/res/map.qml"));
    map = this->rootObject()->findChild<QObject*>("map");
    uavPath = new QList<QVector3D>();
    timer = new QTimer();
    timer->start(timeoutMS);
    connect(timer, &QTimer::timeout, this, &MapWidget::timeout);
}


void MapWidget::removeWaypoint(int wpNum, QVector3D coord) {
    QObject * wp = this->rootObject()->findChild<QObject*>(QString::number(wpNum));
    QMetaObject::invokeMethod(wp, "remove",
         Q_ARG(QVariant, coord));
}

void MapWidget::moveWaypoint(int wpNum, QVector3D newCoords) {
    QObject * wp = this->rootObject()->findChild<QObject*>(QString::number(wpNum));
    QMetaObject::invokeMethod(wp, "moveTo",
         Q_ARG(QVariant, newCoords));
}

void MapWidget::selectWaypoint(int wpNum) {
     QObject * wp = this->rootObject()->findChild<QObject*>(QString::number(wpNum));
     QMetaObject::invokeMethod(wp, "setActive");
}

void MapWidget::addWaypoint(QVector3D point, int wpNum, QColor color, int radius) {
    QMetaObject::invokeMethod(map, "addWaypoint",
            Q_ARG(QVariant, point),
            Q_ARG(QVariant, wpNum),
            Q_ARG(QVariant, color),
            Q_ARG(QVariant, radius));
}

void MapWidget::addMissionPath(QList<QVector3D> *missionPath) {
    QMetaObject::invokeMethod(map, "addMissionPath", Q_ARG(QVariant, toQVariantList(missionPath)));
    for (int i = 0; i < missionPath->size(); i++)
        addWaypoint(missionPath->at(i), i, QColor("#2980b9"), 20);
}

void MapWidget::changeEditMode(bool editing) {
    QMetaObject::invokeMethod(map, "changeEditMode", Q_ARG(QVariant, editing));
}

void MapWidget::drawPoint(QVector2D point, QString label, QColor color, int radius) {
    QMetaObject::invokeMethod(map, "drawPoint",
            Q_ARG(QVariant, point),
            Q_ARG(QVariant, label),
            Q_ARG(QVariant, color),
            Q_ARG(QVariant, radius));
}

void MapWidget::drawPolyline(QVariantList points, QColor color){
    QMetaObject::invokeMethod(map, "drawPolyline",
            Q_ARG(QVariant, QVariant::fromValue(points)),
            Q_ARG(QVariant, color));
}

void MapWidget::drawPolyline(QList<QVector3D> * points, QColor color) {
    drawPolyline(toQVariantList(points), color);
}

void MapWidget::drawPolygon(QVariantList points, QColor color, QString label) {
    QMetaObject::invokeMethod(map, "drawPolygon",
           Q_ARG(QVariant, QVariant::fromValue(points)),
           Q_ARG(QVariant, color),
           Q_ARG(QVariant, label));
}

void MapWidget::drawPolygonF(QPolygonF points, QColor color, QString label) {
    QVariantList newList;
    for(QPointF item: points.toList()) {
        newList << item;
    }
    drawPolygon(newList, color, label);
}

void MapWidget::updateArmState(bool state) {
    QMetaObject::invokeMethod(map, "updateArmState",
            Q_ARG(QVariant, state));
}

void MapWidget::timeout() {
    QMetaObject::invokeMethod(map, "removeUAV");
}

void MapWidget::clearMap() {
    QMetaObject::invokeMethod(map, "clearMap");
}
void MapWidget::drawWaypoints(QList<QVector2D> * waypoints) {
    /* Waypoints */
    clearMap();
    drawPolyline(toQVariantList(waypoints), QColor("blue"));
    for (int i = 0; i < waypoints->size(); i++)
        drawPoint(waypoints->at(i), QString::number(i),QColor(235,255,0), 30);
}

void MapWidget::drawMission(Mission *mission) {
    for (int i = 0; i < mission->fly_zones.size(); i++) {
        drawPolygon(toQVariantList(&(mission->fly_zones.at(i).boundary_points)),
                    QColor(0,255,0, 70), "Fly Zone #" + QString::number(i));
    }

    /* Search Grid Points */
    if (!mission->search_grid_points->empty()) {
        drawPolygon(toQVariantList(mission->search_grid_points), QColor(0,0,255, 70), "Search Grid");
    }

    /* Home position */
    drawPoint(mission->home_pos, "Home", QColor(166,240,84));

    /* Air Drop Point */
    drawPoint(mission->air_drop_pos, "Air Drop", QColor(102,194,255));

    /* Off Axis ODLC Position */
    drawPoint(mission->off_axis_odlc_pos, "Off Axis ODLC", QColor(255,127,0));

    /* Emergent hiker */
    drawPoint(mission->emergent_last_known_pos, "Emergent LK Pos", QColor(0,0,0));

    /* Waypoints */
    addMissionPath(mission->toList());
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


void MapWidget::updateUAV() {
    if (blinkUAV) {
        QTimer timer;
        QEventLoop loop;

        QMetaObject::invokeMethod(map, "removeUAV");

        drawUAV(uav_latitude, uav_longitude, uav_heading);

        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(50);
        loop.exec();

        QMetaObject::invokeMethod(map, "removeUAV");

        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(50);
        loop.exec();

        drawUAV(uav_latitude, uav_longitude, uav_heading);
    } else drawUAV(uav_latitude, uav_longitude, uav_heading);
}

void MapWidget::updateUAVPosition(mavlink_gps_raw_int_t gps) {
    timer->setInterval(timeoutMS);
    uav_latitude = (double)gps.lat/10000000;
    uav_longitude = (double)gps.lon/10000000;
    if (updateUAVConstant) {
        updateUAV();
    }
    if (updateCenterConstant) {
        updateCenter(uav_latitude, uav_longitude);
    }
}


void MapWidget::updateUAVHeading(mavlink_vfr_hud_t vfr) {
    uav_heading = vfr.heading;
}

QString MapWidget::headingToCompass(int heading) {
    QString compass = "Compass bearing: ";
    if ((heading<360 && heading>348.75) || (heading>=0 && heading<=11.25))
        return compass.append("N");
    if (heading>11.25 && heading<=33.75)
        return compass.append("NNE");
    if (heading>33.75 && heading<=56.25)
        return compass.append("NE");
    if (heading>56.25 && heading<=78.75)
        return compass.append("ENE");
    if (heading>78.75 && heading<=101.25)
        return compass.append("E");
    if (heading>101.25 && heading<=123.75)
        return compass.append("ESE");
    if (heading>123.75 && heading<=146.25)
        return compass.append("SE");
    if (heading>146.25 && heading<=168.75)
        return compass.append("SSE");
    if (heading>168.75 && heading<=191.25)
        return compass.append("S");
    if (heading>191.25 && heading<=213.75)
        return compass.append("SSW");
    if (heading>213.75 && heading<=236.25)
        return compass.append("SW");
    if (heading>236.25 && heading<=258.75)
        return compass.append("WSW");
    if (heading>258.75 && heading<=281.25)
        return compass.append("W");
    if (heading>281.25 && heading<=303.75)
        return compass.append("WNW");
    if (heading>303.75 && heading<=326.25)
        return compass.append("NW");
    if (heading>326.25 && heading<=348.75)
        return compass.append("NNW");
    return "MapWidget::headingToCompass - Greater than 359";
}
