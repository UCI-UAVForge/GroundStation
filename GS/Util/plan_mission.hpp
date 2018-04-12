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
        std::vector<QPolygonF> search_areas;
        double meters_to_deg(double meters, double latitude)
        {
            return (meters / (111.32 * 1000 * cos(latitude * (M_PI / 180))));
        }
        std::vector<std::pair<double, double>> pathfind(double start_lat, double start_lon, double end_lat, double end_lon, QList<FlyZone> flyzones);
    public:
        PlanMission();
        // too lazy to implement ordering for these objects
        void add_goal_point(Point p);
        void set_obstacles(Obstacles o);
        QList<QPolygonF> get_obstacles() {
            QList<QPolygonF> polys;
            for (QJsonValueRef o : obstacles_z.get_stationary_obstacles()) {
                QJsonObject obstacle = o.toObject();
                double obs_lat = obstacle["latitude"].toDouble();
                double obs_lon = obstacle["longitude"].toDouble();
                double radius = obstacle["cylinder_radius"].toDouble();
                double delta = meters_to_deg(radius, obs_lat);

                QVector<QPointF> obstacle_footprint_points;
                for (double theta = 0; theta < 2*M_PI; theta += M_PI/360) {
                    obstacle_footprint_points << QPointF(obs_lat + (delta * cos(theta)), obs_lon + (delta * sin(theta)));
                }
                polys.append(QPolygonF(obstacle_footprint_points));
            }
            return polys;
        }
        void add_serach_area(QPolygonF poly);
        QList<QVector3D> * get_path(Point start_point, QList<FlyZone> flyzones);
        static bool poly_intersects(QPolygonF a, QPolygonF b) {
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
            QPainterPath subject; subject.addPolygon(a);
            QPainterPath clip; clip.addPolygon(b);
            return subject.intersects(clip);
#else
            // literally the same code as above why are we doing this
            return a.intersects(b);
#endif
        }
};

#endif // PLANMISSION_HPP
