#ifndef MISSIONSTATESPACE_H
#define MISSIONSTATESPACE_H

#include <rrt/2dplane/GridStateSpace.hpp>
#include "mission.h"

class MissionStateSpace : public RRT::GridStateSpace
{
private:
    QPolygonF flyzone;
    std::vector<QPolygonF> obstacle_polys;
public:
    Eigen::Vector2d endpoints[2];
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
//    Eigen::Vector2d randomState() const {
////        double dist = rand()/(RAND_MAX + 1.0) * (endpoints[0] + endpoints[1]).norm();
////        double rads = rand()/(RAND_MAX + 1.0) * M_2_PI;

////        double x = sin(rads) * dist;
////        double y = cos(rads) * dist;

////        // return a simple point object
//////        qInfo() << (x + endpoints[0].x()) << " : " << (y + endpoints[0].y());
////        return Eigen::Vector2d(x + endpoints[0].x(), y + endpoints[0].y());
//        QRectF bounding = flyzone.boundingRect();
//        QPointF tl = bounding.topLeft();
//        QPointF br = bounding.bottomRight();
//        QPointF bl = bounding.bottomLeft();
//        double x_delta = br.x() - tl.x();
//        double y_delta = br.y() - tl.y();
//        double x = (rand()/(RAND_MAX + 1.0)) * x_delta;
//        double y= (rand()/(RAND_MAX + 1.0)) * y_delta;
////        qInfo() << ((x + bl.x()) * 1000) << " : " << ((y + bl.y()) * 1000);
//        return Eigen::Vector2d((x + bl.x()) * 1000, abs(y + bl.y()) * 1000);
//    }
    bool stateValid(const Eigen::Vector2d& pt) const {
        QPointF curr_point = QPointF(pt.x()/1000, -pt.y()/1000);
        if (!flyzone.containsPoint(curr_point, Qt::WindingFill)) {
            return false;
        }

        bool no_obstacles = true;
        for (QPolygonF o : obstacle_polys) {
            if (o.containsPoint(curr_point, Qt::WindingFill)) {
                no_obstacles = false;
                break;
            }
        }
        return no_obstacles;
    }
    bool transitionValid(const Eigen::Vector2d& from,
                         const Eigen::Vector2d& to) const {
        if (!stateValid(to)) return false;

        bool intersects = false;
        QPolygonF segment;
        segment.append(QPointF(from.x()/1000, -from.y()/1000));
        segment.append(QPointF(to.x()/1000, -to.y()/1000));
        for (QPolygonF obst_poly : obstacle_polys) {
            if (PlanMission::poly_intersects(obst_poly, segment)) {
                intersects = true;
                break;
            }
        }
        return !intersects;
    }
    void addObstacle(QPolygonF poly) {
        obstacle_polys.push_back(poly);
    }
};

#endif // MISSIONSTATESPACE_H
