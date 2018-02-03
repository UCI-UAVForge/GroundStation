#ifndef PLANMISSION_HPP
#define PLANMISSION_HPP

#include <algorithm>
#include <memory>
#include <set>
#include <stack>

#include <QPolygon>

#include "obstacles.h"
#include "point.hpp"
#include "mission.h"

class PlanMission
{
    private:
        std::vector<Point> goal_points;
        Obstacles obstacles_z;
        std::vector<QPolygon> search_areas;

        std::vector<std::pair<double, double>> pathfind(double start_lat, double start_lon, double end_lat, double end_lon, Obstacles obstacles, QList<FlyZone>* flyzones);
    public:
        PlanMission();
        // too lazy to implement ordering for these objects
        void add_goal_point(Point p);
        void set_obstacles(Obstacles o);
        void add_serach_area(QPolygon poly);
        QList<QVector3D> * get_path(Point start_point, QList<FlyZone>* flyzones);
};

#endif // PLANMISSION_HPP
