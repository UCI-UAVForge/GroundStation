#include "plan_mission.hpp"
#include <stack>
#include <memory>
#include "missionstatespace.h"
#include <rrt/2dplane/2dplane.hpp>
#include <rrt/BiRRT.hpp>
#include <rrt/planning/Path.hpp>
#include <Eigen/src/Core/Matrix.h>
double SCALE_CONSTANT = 1000;
std::vector<std::pair<double, double>> PlanMission::pathfind(double start_lat, double start_lon, double end_lat, double end_lon, QList<FlyZone>* flyzones) {
    int dimensions = 2;

    Eigen::Vector2d size(90000,90000);
    std::vector<Eigen::Vector2d> _previousSolution;

    std::shared_ptr<MissionStateSpace> _stateSpace(new MissionStateSpace(size.x(), size.y(), 20, 20, FlyZone(flyzones->at(0))));
    std::shared_ptr<RRT::BiRRT<Eigen::Vector2d>> _biRRT = std::make_shared<RRT::BiRRT<Eigen::Vector2d>>(_stateSpace, RRT::hash, dimensions);

    auto _waypointCacheMaxSize = 15;

    Eigen::Vector2d _startPos = Eigen::Vector2d(start_lat*SCALE_CONSTANT, abs(start_lon)*SCALE_CONSTANT);
    Eigen::Vector2d _goalPos = Eigen::Vector2d(end_lat*SCALE_CONSTANT, abs(end_lon)*SCALE_CONSTANT);
//    Eigen::Vector2d _startPos = Eigen::Vector2d(1, 1);
//    Eigen::Vector2d _goalPos = Eigen::Vector2d(30, 30);
    qInfo() << _startPos.x() << " " << _startPos.y();
    qInfo() << _goalPos.x() << " " << _goalPos.y();
    //  setup birrt
    _biRRT->setStartState(_startPos);
    _biRRT->setGoalState(_goalPos);
    _biRRT->setMaxStepSize(100);
    _biRRT->setGoalMaxDist(.1);

    // set obstacles
    for (QPolygonF obst_poly : get_obstacles()) {
         _stateSpace->addObstacle(obst_poly);
    };

    std::vector<std::pair<double, double>> result;
    for (int i = 0; i < 1000; i++) {
        _biRRT->grow();
        if (_biRRT->startSolutionNode() != nullptr) {
            qInfo() << "we did it";
            auto _previousSolution = _biRRT->getPath();
            RRT::SmoothPath<Eigen::Vector2d>(_previousSolution, *_stateSpace);

            for (Eigen::Vector2d v : _previousSolution) {
                qInfo() << v.x() << " " << v.y();
                result.push_back(std::pair<double, double>(v.x(), v.y()));
            }
            break;
        }
    }
    return result;
}
PlanMission::PlanMission() {}
// too lazy to implement ordering for these objects
void PlanMission::add_goal_point(Point p) {
    goal_points.push_back(p);
}
void PlanMission::set_obstacles(Obstacles o) {
    obstacles_z = o;
}
void PlanMission::add_serach_area(QPolygonF poly) {
    search_areas.push_back(poly);
}

QList<QVector3D> * PlanMission::get_path(Point start_point, QList<FlyZone>* flyzones) {
    std::vector<Point> path;
//    path.push_back(start_point);
    std::vector<Point> prelim_path;
//    prelim_path.push_back(start_point);
    auto sort_func = [&](Point a, Point b) { return Point::euclidian_distance(prelim_path.back(), a) > Point::euclidian_distance(prelim_path.back(), b); };
    std::vector<Point> remaining_points(goal_points.begin(), goal_points.end());
    qInfo() << "start: " << start_point;
    // add search areas to remaining_points
    // generate rectangle
    // gen search path

    // generate prelim serach path
    std::vector<Point> pts = remaining_points;
    for (Point p : remaining_points) {
        // sort
        std::make_heap(pts.begin(), pts.end(),
                        sort_func);

        // pop
        std::pop_heap(pts.begin(), pts.end());
        Point next = pts.back();
        pts.pop_back();
        qInfo() << "prelim: " << next;
        prelim_path.push_back(p);
    }

    // pathfind around obstacles
    Point last_point = start_point;
    QList<QPolygonF> obstacle_polys = get_obstacles();

    for (Point p : remaining_points) {
        qInfo() << last_point.toGeodetic() << " -> " << p.toGeodetic();
        // if segment defined by <last_point, p> intersects cylinder o {
        bool intersects = false;
        QPolygonF segment;
        segment.append(QPointF(last_point.toGeodetic()[0], last_point.toGeodetic()[1]));
        segment.append(QPointF(p.toGeodetic()[0], p.toGeodetic()[1]));
        for (QPolygonF obst_poly : obstacle_polys) {
            if (PlanMission::poly_intersects(obst_poly, segment)) {
                intersects = true;
                break;
            }
        }
        if (intersects) {
//        if (obstacles_z.segmentIntersectsObstacles(last_point, p)) {
            qInfo() << "we borked; starting RRT";
            // pathfind around obstacles
            auto detour = pathfind(last_point.toGeodetic()[0], last_point.toGeodetic()[1], p.toGeodetic()[0], p.toGeodetic()[1], flyzones);
            if (detour.size() > 1) {
                for (auto it = detour.begin()+1; it != detour.end(); ++it) {
                    qInfo() << it->first/SCALE_CONSTANT << "/" << it->second/SCALE_CONSTANT;
                    qInfo() << Point::fromGeodetic(it->first/SCALE_CONSTANT, it->second/SCALE_CONSTANT, 0);
                    path.push_back(Point::fromGeodetic(it->first/SCALE_CONSTANT, it->second/SCALE_CONSTANT, 0));
                }
            }
            if (path.size() > 0) {
                last_point = path.back();
            } else {
                last_point = p;
            }
        } else {
            last_point = p;
            path.push_back(p);
        }
    }

    // inefficient but lets just do like this for now
    QList<QVector3D>* qlist_qvector3d = new QList<QVector3D>();
    qInfo() << "da path";
    for (Point p : path) {
        qInfo() << p.toGeodetic();
        //qlist_qvector3d->append(p.QVectorGeodetic());
        qlist_qvector3d->append(QVector3D(p.toGeodetic().at(0), p.toGeodetic().at(1) * -1, 0));
    }
    qInfo() << "done with path";
    return qlist_qvector3d;
}
