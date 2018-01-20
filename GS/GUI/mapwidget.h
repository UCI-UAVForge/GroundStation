#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QQuickWidget>
#include "mission.h"
#include "QVector3D"
#include "QVariant"
#include <QGeoCoordinate>

#include <QTimer>
#include <QEventLoop>

class MapWidget : public QQuickWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget * parent = nullptr);
    QObject * map;
    void drawPoint(QVector2D point, QColor color);
    void drawPolyline(QVariantList points, QColor color);
    void drawPolygon(QVariantList points,QColor color = QColor(0,0,0,255));
//    void updateUAVvPosition(mavlink_gps_raw_int_t gps);
    void clearMap();
    void drawMission(Mission * mission);
    void drawUAV(double lat, double lon, double heading);
    void updateCenter(double lat, double lon);
    void updateUAV();
    inline void toggleUpdateCenterConstant() {
        updateCenterConstant = updateCenterConstant ? false : true;
    }
    inline void toggleUpdateUAVConstant() {
        updateUAVConstant = updateUAVConstant ? false : true;
    }
    inline void toggleBlinkUAV() {
        blinkUAV = blinkUAV ? false : true;
    }

    void testRemoveUAV();

private:
    template <typename T>
    QVariantList toQVariantList(const QList<T> * list ) {
        QVariantList newList;
        for(const T item: (*list)) {
            newList << item;
        }
        return newList;
    }
    QString headingToCompass(int heading);
    bool updateCenterConstant = false;
    bool updateUAVConstant = true;
    bool blinkUAV = false;
    double uav_latitude = 0;
    double uav_longitude = 0;
    int uav_heading = 0;

//signals:

public slots:
    void updateUAVPosition(mavlink_gps_raw_int_t gps);
    void updateUAVHeading(mavlink_vfr_hud_t vfr);
};

#endif // MAPWIDGET_H
