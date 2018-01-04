#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QQuickWidget>
#include "mission.h"
#include "QVector3D"
#include "QVariant"

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

private:
    template <typename T>
    QVariantList toQVariantList(const QList<T> * list ) {
        QVariantList newList;
        for(const T item: (*list)) {
            newList << item;
        }
        return newList;
    }

//signals:

//public slots:
};

#endif // MAPWIDGET_H
