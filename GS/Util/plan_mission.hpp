#ifndef PLANMISSION_HPP
#define PLANMISSION_HPP

#include <algorithm>
#include <memory>
#include <set>

#include <QPolygon>

#include "rrt.h"
#include "obstacles.h"
#include "point.hpp"

class PlanMission
{
    private:
        std::vector<Point> goal_points;
        Obstacles obstacles_z;
        std::vector<QPolygon> search_areas;

        std::vector<Point> pathfind(Point start, Point end, Obstacles obstacles);
    public:
        PlanMission();
        // too lazy to implement ordering for these objects
        void add_goal_point(Point p);
        void set_obstacles(Obstacles o);
        void add_serach_area(QPolygon poly);
        std::vector<Point> get_path(Point start_point);
};

#endif // PLANMISSION_HPP
