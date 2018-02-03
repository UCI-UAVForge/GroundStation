#ifndef MISSIONSTATESPACE_H
#define MISSIONSTATESPACE_H

#include <rrt/2dplane/GridStateSpace.hpp>
#include "mission.h"

class MissionStateSpace : public RRT::GridStateSpace
{
private:
    QPolygonF flyzone;
public:
    MissionStateSpace(double width, double height, int discretizedWidth,
                      int discretizedHeight, FlyZone flyzone)
        : RRT::GridStateSpace(width, height, discretizedWidth, discretizedHeight)
    {
        QVector<QPointF> newList;
        for(const QVector2D item: *flyzone.boundary_points) {
            newList << item.toPointF();
        }
        this->flyzone = QPolygonF(newList);
    }
    bool stateValid(const Eigen::Vector2d& pt) const {
        bool dd = flyzone.containsPoint(QPointF(pt.x()/1000, -pt.y()/1000), Qt::WindingFill);
        return RRT::GridStateSpace::stateValid(pt) && dd;
    }
};

#endif // MISSIONSTATESPACE_H
