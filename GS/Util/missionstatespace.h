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
        QPointF non_scaled_curr_point = QPointF(pt.x(), pt.y());
        QPointF curr_point = QPointF(pt.x()/1000, -pt.y()/1000);
        bool dd = flyzone.containsPoint(curr_point, Qt::WindingFill);
        bool no_obstacles = true;
        for (QPolygonF o : obstacle_polys) {
            if (o.containsPoint(curr_point, Qt::WindingFill)) {
                no_obstacles = false;
                break;
            }
        }
        return RRT::GridStateSpace::stateValid(pt) && dd && no_obstacles;
    }
    bool transitionValid(const Eigen::Vector2d& from,
                         const Eigen::Vector2d& to) const {
        bool intersects = false;
        QPolygonF segment;
        segment.append(QPointF(from.x()/1000, -from.y()/1000));
        segment.append(QPointF(to.x()/1000, -to.y()/1000));
//        qDebug() << segment;
        for (QPolygonF obst_poly : obstacle_polys) {
            if (PlanMission::poly_intersects(obst_poly, segment)) {
                intersects = true;
                break;
            }
        }
        return RRT::GridStateSpace::transitionValid(from, to) && !intersects;
    }
    void addObstacle(QPolygonF poly) {
        obstacle_polys.push_back(poly);
    }
};

#endif // MISSIONSTATESPACE_H
