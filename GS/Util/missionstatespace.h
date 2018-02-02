#ifndef MISSIONSTATESPACE_H
#define MISSIONSTATESPACE_H

#include <rrt/2dplane/GridStateSpace.hpp>
#include "mission.h"

class MissionStateSpace : public RRT::GridStateSpace
{
private:
    QPolygon flyzone;
public:
    MissionStateSpace(double width, double height, int discretizedWidth,
                      int discretizedHeight, FlyZone flyzone)
        : RRT::GridStateSpace(width, height, discretizedWidth, discretizedHeight)
    {
        QVector<QPoint> newList;
        for(const QVector2D item: *flyzone.boundary_points) {
            newList << item.toPoint();
        }
        this->flyzone = QPolygon(newList);
    }
    bool stateValid(const Eigen::Vector2d& pt) const {
        return RRT::GridStateSpace::stateValid(pt) && flyzone.containsPoint(QPoint(pt.x(), pt.y()), Qt::OddEvenFill);
    }
};

#endif // MISSIONSTATESPACE_H
