#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QQuickWidget>
#include "mission.h"
#include "QVector3D"
#include "QVariant"

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
    void clearMap();
    void drawMission(Mission * mission);
    void drawUAV(double lat, double lon, double heading);
    void updateCenter(double lat, double lon);
    void updateUAV();
    inline void toggleUpdateConstant() {
        updateConstant = updateConstant ? false : true;
    }
    inline void toggleBlinkUAV() {
        blinkUAV = blinkUAV ? false : true;
    }

    void removeUAV();

private:
    template <typename T>
    QVariantList toQVariantList(const QList<T> * list ) {
        QVariantList newList;
        for(const T item: (*list)) {
            newList << item;
        }
        return newList;
    }
    bool updateConstant = true;
    double uav_latitude;
    double uav_longitude;
    double uav_heading;

    bool blinkUAV = false;

//signals:

public slots:
    void updateUAVPosition(mavlink_global_position_int_t gps_int);
};

#endif // MAPWIDGET_H
